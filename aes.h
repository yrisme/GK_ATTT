// aes.h
#ifndef AES_H
#define AES_H

#include <vector>
#include <cstdint>
#include <array>

constexpr int Nb = 4;  //Số cột của State
constexpr int Nk = 4;  //Số từ khóa (AES-128)
constexpr int Nr = 10; //Số vòng lặp (AES-128)

using State = std::array<std::array<uint8_t, 4>, 4>;

extern const uint8_t sbox[256];
extern const uint8_t inv_sbox[256];
extern const uint8_t Rcon[11];

//Key expansion
void KeyExpansion(const std::vector<uint8_t>& key, std::vector<std::vector<uint8_t>>& roundKeys);

//Vòng mã hoá
void SubBytes(State& state);
void ShiftRows(State& state);
void MixColumns(State& state);
void AddRoundKey(State& state, const std::vector<uint8_t>& roundKey);

//Vòng giải mã
void InvSubBytes(State& state);
void InvShiftRows(State& state);
void InvMixColumns(State& state);

void EncryptBlock(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key, std::vector<uint8_t>& output);
void DecryptBlock(const std::vector<uint8_t>& input, const std::vector<uint8_t>& key, std::vector<uint8_t>& output);

#endif
