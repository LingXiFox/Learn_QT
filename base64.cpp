#include "base64.h"
#include <cctype>

static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c)
{
    return std::isalnum(c) || c == '+' || c == '/';
}

std::string base64_encode(const unsigned char* data, size_t len)
{
    std::string out;
    unsigned char a3[3];
    unsigned char a4[4];
    size_t i = 0;

    while (len--) {
        a3[i++] = *(data++);
        if (i == 3) {
            a4[0] = (a3[0] & 0xfc) >> 2;
            a4[1] = ((a3[0] & 0x03) << 4) | ((a3[1] & 0xf0) >> 4);
            a4[2] = ((a3[1] & 0x0f) << 2) | ((a3[2] & 0xc0) >> 6);
            a4[3] = a3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                out += base64_chars[a4[i]];
            i = 0;
        }
    }

    if (i) {
        for (size_t j = i; j < 3; j++)
            a3[j] = 0;

        a4[0] = (a3[0] & 0xfc) >> 2;
        a4[1] = ((a3[0] & 0x03) << 4) | ((a3[1] & 0xf0) >> 4);
        a4[2] = ((a3[1] & 0x0f) << 2) | ((a3[2] & 0xc0) >> 6);
        a4[3] = a3[2] & 0x3f;

        for (size_t j = 0; j < i + 1; j++)
            out += base64_chars[a4[j]];

        while (i++ < 3)
            out += '=';
    }

    return out;
}

std::vector<unsigned char> base64_decode(const std::string& input)
{
    size_t len = input.size();
    size_t i = 0;
    unsigned char a3[3];
    unsigned char a4[4];
    std::vector<unsigned char> out;

    size_t pos = 0;
    while (len-- && input[pos] != '=' && is_base64(input[pos])) {
        a4[i++] = input[pos++];
        if (i == 4) {
            for (i = 0; i < 4; i++)
                a4[i] = base64_chars.find(a4[i]);

            a3[0] = (a4[0] << 2) | ((a4[1] & 0x30) >> 4);
            a3[1] = ((a4[1] & 0x0f) << 4) | ((a4[2] & 0x3c) >> 2);
            a3[2] = ((a4[2] & 0x03) << 6) | a4[3];

            for (i = 0; i < 3; i++)
                out.push_back(a3[i]);
            i = 0;
        }
    }

    if (i) {
        for (size_t j = i; j < 4; j++)
            a4[j] = 0;

        for (size_t j = 0; j < 4; j++)
            a4[j] = base64_chars.find(a4[j]);

        a3[0] = (a4[0] << 2) | ((a4[1] & 0x30) >> 4);
        a3[1] = ((a4[1] & 0x0f) << 4) | ((a4[2] & 0x3c) >> 2);
        a3[2] = ((a4[2] & 0x03) << 6) | a4[3];

        for (size_t j = 0; j < i - 1; j++)
            out.push_back(a3[j]);
    }

    return out;
}