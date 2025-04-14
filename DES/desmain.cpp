#include <iostream>
#include <fstream>
#include <string>
#include "des.h"

int main() {
    std::ifstream inputFile("input.txt");
    std::string plainText;
    if (inputFile) {
        std::getline(inputFile, plainText);
        inputFile.close();
    } else {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }

    std::string key = "12345678";  
    std::string cipherText = des_encrypt(plainText, key);

    std::ofstream encryptedFile("encrypted.txt");
    if (encryptedFile) {
        encryptedFile << cipherText;
        encryptedFile.close();
    } else {
        std::cerr << "Failed to write to encrypted.txt" << std::endl;
        return 1;
    }

    std::string decryptedText = des_decrypt(cipherText, key);

    std::ofstream outputFile("output.txt");
    if (outputFile) {
        outputFile << decryptedText;
        outputFile.close();
    } else {
        std::cerr << "Failed to write to output.txt" << std::endl;
        return 1;
    }

    std::cout << "Encryption and Decryption completed successfully!" << std::endl;

    return 0;
}
