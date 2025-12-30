// haxi.h
//#define HAXI_ALLOW_WEAK_HASHES
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace haxi {

enum class HashType {
    SHA256,
    // Weak; requires HAXI_ALLOW_WEAK_HASHES to enable at runtime.
    MD5,
    FNV1A64
};

// 生成随机盐（字节数 = salt_size_bytes）
std::vector<uint8_t> make_salt(std::size_t salt_size_bytes);

// 对 data 做哈希：digest = HASH( salt || data )
// 返回 digest 的十六进制字符串；salt_hex_out 返回盐的十六进制（可空）
std::string hash_with_new_salt_hex(
    const std::string& data,
    HashType type,
    std::size_t salt_size_bytes,
    std::string* salt_hex_out = nullptr
);

// 使用外部提供的盐（十六进制字符串）
// digest = HASH( salt || data )
std::string hash_with_salt_hex(
    const std::string& data,
    HashType type,
    const std::string& salt_hex
);

// 便捷：把结果打包成 "TYPE:saltHex:digestHex"
std::string pack_result(
    HashType type,
    const std::string& salt_hex,
    const std::string& digest_hex
);

// 工具：HashType <-> string
const char* to_string(HashType t);
bool from_string(const std::string& s, HashType& out);

// 工具：hex 编解码
std::string bytes_to_hex(const uint8_t* data, std::size_t n);
std::vector<uint8_t> hex_to_bytes(const std::string& hex);

} // namespace haxi
