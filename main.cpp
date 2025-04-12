#include "aes.h"
#include <fstream>
#include <iostream>
#include <vector>

std::vector<uint8_t> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    return data;
}

void writeFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

std::vector<uint8_t> padData(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> padded = data;
    size_t pad_len = 16 - (data.size() % 16);
    padded.insert(padded.end(), pad_len, static_cast<uint8_t>(pad_len));
    return padded;
}

std::vector<uint8_t> unpadData(const std::vector<uint8_t>& data) {
    if (data.empty()) return {};
    uint8_t pad_len = data.back();
    return std::vector<uint8_t>(data.begin(), data.end() - pad_len);
}

int main() {
    std::vector<uint8_t> key = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88,
        0x09, 0xcf, 0x4f, 0x3c
    };

    //Đọc dữ liệu từ file
    std::vector<uint8_t> plain = readFile("input.txt");
    std::vector<uint8_t> paddedPlain = padData(plain);
    std::vector<uint8_t> encrypted;

    //Mã hoá từng khối
    for (size_t i = 0; i < paddedPlain.size(); i += 16) {
        std::vector<uint8_t> block(16), encBlock;
        std::copy(paddedPlain.begin() + i, paddedPlain.begin() + i + 16, block.begin());
        EncryptBlock(block, key, encBlock);
        encrypted.insert(encrypted.end(), encBlock.begin(), encBlock.end());
    }

    writeFile("encrypted.txt", encrypted);

    //Giải mã từng khối
    std::vector<uint8_t> decrypted;
    for (size_t i = 0; i < encrypted.size(); i += 16) {
        std::vector<uint8_t> block(16), decBlock;
        std::copy(encrypted.begin() + i, encrypted.begin() + i + 16, block.begin());
        DecryptBlock(block, key, decBlock);
        decrypted.insert(decrypted.end(), decBlock.begin(), decBlock.end());
    }

    std::vector<uint8_t> original = unpadData(decrypted);
    writeFile("output.txt", original);

    return 0;
}
