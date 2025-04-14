#include "des.h"
#include <bitset>
#include <string>
#include <vector>
#include <iostream>

int initial_permutation[] = {
     58, 50, 42, 34, 26, 18, 10, 2,
     60, 52, 44, 36, 28, 20, 12, 4,
     62, 54, 46, 38, 30, 22, 14, 6,
     64, 56, 48, 40, 32, 24, 16, 8,
     57, 49, 41, 33, 25, 17,  9, 1,
     59, 51, 43, 35, 27, 19, 11, 3,
     61, 53, 45, 37, 29, 21, 13, 5,
     63, 55, 47, 39, 31, 23, 15, 7
};

int final_permutation[] = {
     40, 8, 48, 16, 56, 24, 64, 32,
     39, 7, 47, 15, 55, 23, 63, 31,
     38, 6, 46, 14, 54, 22, 62, 30,
     37, 5, 45, 13, 53, 21, 61, 29,
     36, 4, 44, 12, 52, 20, 60, 28,
     35, 3, 43, 11, 51, 19, 59, 27,
     34, 2, 42, 10, 50, 18, 58, 26,
     33, 1, 41,  9, 49, 17, 57, 25
};

std::bitset<64> string_to_bitset(const std::string& str) {
    std::bitset<64> bits;
    for (int i = 0; i < str.size(); ++i) {
        std::bitset<8> b(str[i]);
        for (int j = 0; j < 8; ++j) {
            bits[i * 8 + j] = b[7 - j];
        }
    }
    return bits;
}

std::string bitset_to_string(const std::bitset<64>& bits) {
    std::string result;
    for (int i = 0; i < 8; ++i) {
        std::bitset<8> b;
        for (int j = 0; j < 8; ++j) {
            b[7 - j] = bits[i * 8 + j];
        }
        result += static_cast<char>(b.to_ulong());
    }
    return result;
}

std::bitset<64> permute(const std::bitset<64>& in, const int* table) {
    std::bitset<64> out;
    for (int i = 0; i < 64; ++i) {
        out[i] = in[table[i] - 1];
    }
    return out;
}

std::bitset<64> des_block_encrypt(const std::bitset<64>& block, const std::bitset<64>& key) {
    std::bitset<64> permuted = permute(block, initial_permutation);
    std::bitset<64> encrypted = permuted ^ key;
    return permute(encrypted, final_permutation);
}

std::bitset<64> des_block_decrypt(const std::bitset<64>& block, const std::bitset<64>& key) {
    std::bitset<64> permuted = permute(block, initial_permutation);
    std::bitset<64> decrypted = permuted ^ key;
    return permute(decrypted, final_permutation);
}

std::string des_encrypt(const std::string& plainText, const std::string& key) {
    std::string result;
    std::bitset<64> k = string_to_bitset(key.substr(0, 8));
    for (size_t i = 0; i < plainText.size(); i += 8) {
        std::string block = plainText.substr(i, 8);
        while (block.size() < 8) block += ' ';
        std::bitset<64> bits = string_to_bitset(block);
        std::bitset<64> enc = des_block_encrypt(bits, k);
        result += bitset_to_string(enc);
    }
    return result;
}

std::string des_decrypt(const std::string& cipherText, const std::string& key) {
    std::string result;
    std::bitset<64> k = string_to_bitset(key.substr(0, 8));
    for (size_t i = 0; i < cipherText.size(); i += 8) {
        std::string block = cipherText.substr(i, 8);
        std::bitset<64> bits = string_to_bitset(block);
        std::bitset<64> dec = des_block_decrypt(bits, k);
        result += bitset_to_string(dec);
    }
    return result;
}
