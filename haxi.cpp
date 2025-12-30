// haxi.cpp
#include "haxi.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <random>
#include <sstream>
#include <stdexcept>

#if defined(HAXI_USE_COMMONCRYPTO)
#include <CommonCrypto/CommonDigest.h>
#elif defined(HAXI_USE_OPENSSL)
#include <openssl/sha.h>
#if defined(HAXI_ALLOW_WEAK_HASHES)
#include <openssl/md5.h>
#endif
#else
#error "No supported crypto backend found (CommonCrypto or OpenSSL)."
#endif

namespace haxi {

static uint64_t fnv1a_64_bytes(const uint8_t* p, std::size_t n) {
    uint64_t h = 14695981039346656037ull;
    for (std::size_t i = 0; i < n; ++i) {
        h ^= static_cast<uint64_t>(p[i]);
        h *= 1099511628211ull;
    }
    return h;
}

std::string bytes_to_hex(const uint8_t* data, std::size_t n) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (std::size_t i = 0; i < n; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

static int hex_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
    if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
    return -1;
}

std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
    if (hex.size() % 2 != 0) throw std::runtime_error("salt_hex length must be even");
    std::vector<uint8_t> out;
    out.reserve(hex.size() / 2);
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        int hi = hex_val(hex[i]);
        int lo = hex_val(hex[i + 1]);
        if (hi < 0 || lo < 0) throw std::runtime_error("salt_hex contains non-hex char");
        out.push_back(static_cast<uint8_t>((hi << 4) | lo));
    }
    return out;
}

std::vector<uint8_t> make_salt(std::size_t salt_size_bytes) {
    std::vector<uint8_t> salt(salt_size_bytes);
    std::random_device rd;
    for (std::size_t i = 0; i < salt_size_bytes; ++i) {
        salt[i] = static_cast<uint8_t>(rd());
    }
    return salt;
}

const char* to_string(HashType t) {
    switch (t) {
        case HashType::SHA256:  return "SHA256";
        case HashType::MD5:     return "MD5";
        case HashType::FNV1A64: return "FNV1A64";
        default:                return "UNKNOWN";
    }
}

bool from_string(const std::string& s, HashType& out) {
    if (s == "SHA256" || s == "sha256") { out = HashType::SHA256; return true; }
#if defined(HAXI_ALLOW_WEAK_HASHES)
    if (s == "MD5"    || s == "md5")    { out = HashType::MD5; return true; }
#endif
    if (s == "FNV1A64"|| s == "fnv1a64") { out = HashType::FNV1A64; return true; }
    return false;
}

static std::string digest_hex(HashType type, const uint8_t* salt, std::size_t salt_n,
                              const uint8_t* data, std::size_t data_n) {
    if (type == HashType::SHA256) {
#if defined(HAXI_USE_COMMONCRYPTO)
        CC_SHA256_CTX ctx;
        CC_SHA256_Init(&ctx);
        CC_SHA256_Update(&ctx, salt, static_cast<CC_LONG>(salt_n));
        CC_SHA256_Update(&ctx, data, static_cast<CC_LONG>(data_n));
        std::array<uint8_t, CC_SHA256_DIGEST_LENGTH> out{};
        CC_SHA256_Final(out.data(), &ctx);
        return bytes_to_hex(out.data(), out.size());
#elif defined(HAXI_USE_OPENSSL)
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, salt, salt_n);
        SHA256_Update(&ctx, data, data_n);
        std::array<uint8_t, SHA256_DIGEST_LENGTH> out{};
        SHA256_Final(out.data(), &ctx);
        return bytes_to_hex(out.data(), out.size());
#else
        throw std::runtime_error("SHA256 backend not available");
#endif
    }

    if (type == HashType::MD5) {
#if defined(HAXI_ALLOW_WEAK_HASHES)
#if defined(HAXI_USE_COMMONCRYPTO)
        CC_MD5_CTX ctx;
        CC_MD5_Init(&ctx);
        CC_MD5_Update(&ctx, salt, static_cast<CC_LONG>(salt_n));
        CC_MD5_Update(&ctx, data, static_cast<CC_LONG>(data_n));
        std::array<uint8_t, CC_MD5_DIGEST_LENGTH> out{};
        CC_MD5_Final(out.data(), &ctx);
        return bytes_to_hex(out.data(), out.size());
#elif defined(HAXI_USE_OPENSSL)
        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, salt, salt_n);
        MD5_Update(&ctx, data, data_n);
        std::array<uint8_t, MD5_DIGEST_LENGTH> out{};
        MD5_Final(out.data(), &ctx);
        return bytes_to_hex(out.data(), out.size());
#else
        throw std::runtime_error("MD5 backend not available");
#endif
#else
        throw std::runtime_error("MD5 disabled; use SHA256");
#endif
    }

    if (type == HashType::FNV1A64) {
        uint64_t h = fnv1a_64_bytes(salt, salt_n);
        // 把 data 继续喂进去：等价于 FNV1a(salt||data)
        // 这里复用同一个函数：先对 data 做一次逐字节更新
        // 直接实现：对 data 更新 h
        for (std::size_t i = 0; i < data_n; ++i) {
            h ^= static_cast<uint64_t>(data[i]);
            h *= 1099511628211ull;
        }
        std::array<uint8_t, 8> out{};
        for (int i = 7; i >= 0; --i) {
            out[static_cast<std::size_t>(i)] = static_cast<uint8_t>(h & 0xFFu);
            h >>= 8;
        }
        return bytes_to_hex(out.data(), out.size());
    }

    throw std::runtime_error("unsupported hash type");
}

std::string hash_with_new_salt_hex(const std::string& data, HashType type,
                                   std::size_t salt_size_bytes, std::string* salt_hex_out) {
    auto salt = make_salt(salt_size_bytes);
    std::string salt_hex = bytes_to_hex(salt.data(), salt.size());
    if (salt_hex_out) *salt_hex_out = salt_hex;

    return digest_hex(type,
                      salt.data(), salt.size(),
                      reinterpret_cast<const uint8_t*>(data.data()), data.size());
}

std::string hash_with_salt_hex(const std::string& data, HashType type, const std::string& salt_hex) {
    auto salt = hex_to_bytes(salt_hex);
    return digest_hex(type,
                      salt.data(), salt.size(),
                      reinterpret_cast<const uint8_t*>(data.data()), data.size());
}

std::string pack_result(HashType type, const std::string& salt_hex, const std::string& digest_hex_str) {
    std::ostringstream oss;
    oss << to_string(type) << ":" << salt_hex << ":" << digest_hex_str;
    return oss.str();
}

} // namespace haxi
