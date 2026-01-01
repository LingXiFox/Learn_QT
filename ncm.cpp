#include "ncm.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// AES backend selection: CommonCrypto on Apple, OpenSSL elsewhere if available.
#if defined(__APPLE__) || defined(HAXI_USE_COMMONCRYPTO)
#include <CommonCrypto/CommonCryptor.h>
#elif defined(HAXI_USE_OPENSSL)
#include <openssl/aes.h>
#else
#include <openssl/aes.h>
#endif

namespace ncm {

namespace fs = std::filesystem;

// 硬编码的密钥
const std::string CORE_KEY_HEX = "687A4852416D736F356B496E62617857";
const std::string META_KEY_HEX = "2331346C6A6B5F215C5D2630553C2728";

// 辅助工具：十六进制转二进制
std::vector<unsigned char> hex2bin(const std::string& hex) {
    std::vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char)strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// 辅助工具：PKCS7 去除填充
std::vector<unsigned char> unpad(const std::vector<unsigned char>& data) {
    if (data.empty()) return data;
    unsigned char padding_len = data.back();
    if (padding_len > data.size()) return data; 
    return std::vector<unsigned char>(data.begin(), data.end() - padding_len);
}

// 辅助工具：Base64 解码 (简化版)
static const std::string base64_chars = 
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

std::vector<unsigned char> base64_decode(std::string const& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0, j = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::vector<unsigned char> ret;

    while (in_len-- && ( encoded_string[in_] != '=') && (isalnum(encoded_string[in_]) || (encoded_string[in_] == '+') || (encoded_string[in_] == '/'))) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i = 0; (i < 3); i++) ret.push_back(char_array_3[i]);
            i = 0;
        }
    }
    if (i) {
        for (j = i; j <4; j++) char_array_4[j] = 0;
        for (j = 0; j <4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
    }
    return ret;
}

// AES ECB 解密
std::vector<unsigned char> aes_decrypt(const std::vector<unsigned char>& data, const std::vector<unsigned char>& key) {
#if defined(__APPLE__) || defined(HAXI_USE_COMMONCRYPTO)
    std::vector<unsigned char> out(data.size());
    size_t out_len = 0;
    CCCryptorStatus status = CCCrypt(kCCDecrypt,
                                     kCCAlgorithmAES128,
                                     kCCOptionECBMode,
                                     key.data(),
                                     key.size(),
                                     nullptr,
                                     data.data(),
                                     data.size(),
                                     out.data(),
                                     out.size(),
                                     &out_len);
    if (status != kCCSuccess) return {};
    out.resize(out_len);
    return out;
#else
    AES_KEY aes_key;
    if (AES_set_decrypt_key(key.data(), 128, &aes_key) < 0) return {};

    std::vector<unsigned char> out(data.size());
    for (size_t i = 0; i < data.size(); i += AES_BLOCK_SIZE) {
        AES_decrypt(data.data() + i, out.data() + i, &aes_key);
    }
    return out;
#endif
}

// 简单的 JSON 值提取器 (为了避免引入复杂的 JSON 库)
std::string get_json_string_value(const std::string& json, const std::string& key) {
    std::string search_key = "\"" + key + "\":\"";
    size_t start_pos = json.find(search_key);
    if (start_pos == std::string::npos) return "";
    start_pos += search_key.length();
    size_t end_pos = json.find("\"", start_pos);
    if (end_pos == std::string::npos) return "";
    return json.substr(start_pos, end_pos - start_pos);
}

bool process_ncm_file(const fs::path& file_path, std::string* out_message) {
    std::ifstream f(file_path, std::ios::binary);
    if (!f.is_open()) {
        if (out_message) *out_message = "无法打开文件: " + file_path.string();
        return false;
    }

    // 1. Header Check
    unsigned char header[8];
    f.read((char*)header, 8);
    // 0x4354454e4644414d = "CTENFDAM"
    if (memcmp(header, "CTENFDAM", 8) != 0) {
        if (out_message) *out_message = "不是有效的 NCM 文件: " + file_path.string();
        return false;
    }

    f.seekg(2, std::ios::cur); // 跳过 2 字节

    // 2. Key Processing
    uint32_t key_len;
    f.read((char*)&key_len, 4);
    // Python struct '<I' 是小端序，x86 默认小端，这里直接读取
    
    std::vector<unsigned char> key_data(key_len);
    f.read((char*)key_data.data(), key_len);

    for (size_t i = 0; i < key_len; ++i) {
        key_data[i] ^= 0x64;
    }

    std::vector<unsigned char> core_key = hex2bin(CORE_KEY_HEX);
    std::vector<unsigned char> decrypted_key = unpad(aes_decrypt(key_data, core_key));
    
    // key_data = unpad(...)[17:]
    if (decrypted_key.size() <= 17) {
        if (out_message) *out_message = "密钥解密失败: " + file_path.string();
        return false;
    }
    std::vector<unsigned char> final_key(decrypted_key.begin() + 17, decrypted_key.end());

    // 3. RC4 Key Scheduling Algorithm (KSA)
    unsigned char key_box[256];
    for(int i=0; i<256; ++i) key_box[i] = (unsigned char)i;
    
    unsigned char last_byte = 0;
    unsigned char key_offset = 0;
    unsigned char c = 0;
    
    for (int i = 0; i < 256; ++i) {
        unsigned char swap = key_box[i];
        c = (swap + last_byte + final_key[key_offset]) & 0xff;
        key_offset++;
        if (key_offset >= final_key.size()) key_offset = 0;
        
        key_box[i] = key_box[c];
        key_box[c] = swap;
        last_byte = c;
    }

    // 4. Meta Data Processing
    uint32_t meta_len;
    f.read((char*)&meta_len, 4);
    
    std::vector<unsigned char> meta_data_raw(meta_len);
    f.read((char*)meta_data_raw.data(), meta_len);
    
    for (size_t i = 0; i < meta_len; ++i) {
        meta_data_raw[i] ^= 0x63;
    }

    // Python: meta_data[22:] -> Skip "163 key(Don't modify):"
    std::string meta_str_clean;
    if (meta_data_raw.size() > 22) {
         // Copy everything after 22nd byte to a string for base64 decoding
         meta_str_clean.assign(meta_data_raw.begin() + 22, meta_data_raw.end());
    }

    std::vector<unsigned char> meta_b64 = base64_decode(meta_str_clean);
    std::vector<unsigned char> meta_key = hex2bin(META_KEY_HEX);
    std::vector<unsigned char> decrypted_meta = unpad(aes_decrypt(meta_b64, meta_key));
    
    // Python: decode('utf-8')[6:] -> Skip "music:"
    std::string meta_json_str;
    if (decrypted_meta.size() > 6) {
        meta_json_str.assign(decrypted_meta.begin() + 6, decrypted_meta.end());
    }

    std::string music_name = get_json_string_value(meta_json_str, "musicName");
    std::string format = get_json_string_value(meta_json_str, "format");
    
    if (format.empty()) format = "mp3"; // Fallback

    // 5. CRC & Image
    uint32_t crc32;
    f.read((char*)&crc32, 4);
    f.seekg(5, std::ios::cur);
    uint32_t image_size;
    f.read((char*)&image_size, 4);
    f.seekg(image_size, std::ios::cur); // Skip image data

    // 6. Audio Decryption & Output
    fs::path output_path = file_path.parent_path() / (music_name + "." + format);
    std::ofstream out_file(output_path, std::ios::binary);
    
    if (!out_file.is_open()) {
        if (out_message) *out_message = "无法创建输出文件: " + output_path.string();
        return false;
    }

    if (out_message) *out_message = "正在处理: " + music_name + "." + format;

    const int CHUNK_SIZE = 0x8000;
    std::vector<char> chunk(CHUNK_SIZE);

    while (f) {
        f.read(chunk.data(), CHUNK_SIZE);
        std::streamsize bytes_read = f.gcount();
        if (bytes_read <= 0) break;

        // PRGA logic from Python script
        for (int i = 1; i <= bytes_read; ++i) {
            int j = i & 0xff;
            // 注意: chunk[i-1] 对应 Python 中的 chunk[i-1]
            // key_box 索引逻辑完全复刻 Python
            unsigned char byte = (unsigned char)chunk[i-1];
            unsigned char k = key_box[(key_box[j] + key_box[(key_box[j] + j) & 0xff]) & 0xff];
            chunk[i-1] = (char)(byte ^ k);
        }

        out_file.write(chunk.data(), bytes_read);
    }

    out_file.close();
    f.close();
    return true;
}

bool process_ncm_folder(const fs::path& folder_path, std::string* out_message) {
    if (!fs::exists(folder_path)) {
        if (out_message) *out_message = "路径不存在: " + folder_path.string();
        return false;
    }
    if (!fs::is_directory(folder_path)) {
        if (out_message) *out_message = "不是文件夹: " + folder_path.string();
        return false;
    }

    std::vector<fs::path> ncm_files;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(folder_path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".ncm") {
                ncm_files.push_back(entry.path());
            }
        }
    } catch (const std::exception& e) {
        if (out_message) *out_message = std::string("扫描文件出错: ") + e.what();
        return false;
    }

    if (out_message) {
        *out_message = "找到 " + std::to_string(ncm_files.size()) + " 个 ncm 文件。";
    }

    bool all_ok = true;
    for (const auto& file : ncm_files) {
        std::string msg;
        bool ok = process_ncm_file(file, &msg);
        if (!ok) all_ok = false;
    }
    return all_ok;
}

} // namespace ncm
