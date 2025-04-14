#ifndef DES_H
#define DES_H

#include <string>

std::string des_encrypt(const std::string& plainText, const std::string& key);
std::string des_decrypt(const std::string& cipherText, const std::string& key);

#endif
