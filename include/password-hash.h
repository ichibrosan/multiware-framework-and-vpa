////////////////////////////////////////////////////////////////////
// ~/public_html/fw/password-hash.cpp 2025-07-15 18:16 dwg -      //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#ifndef PASSWORD_HASH_H
#define PASSWORD_HASH_H

#include <string>
#include <vector>
#include <cstdint>
#include <random>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <array>

/**
 * @class PasswordHash
 * @brief A secure password hashing class using SHA-256 with salt and key stretching
 * 
 * This class provides secure password hashing without requiring external libraries
 * like bcrypt or OpenSSL. It uses SHA-256 with salting and key stretching (PBKDF2-style)
 * to create secure password hashes.
 */
class PasswordHash {
private:
    static constexpr size_t SALT_LENGTH = 32;  // 32 bytes salt
    static constexpr size_t HASH_LENGTH = 32;  // 32 bytes hash (SHA-256)
    static constexpr int DEFAULT_ITERATIONS = 10000;  // PBKDF2 iterations
    
    // SHA-256 implementation
    struct SHA256Context {
        std::array<uint32_t, 8> state;
        std::array<uint8_t, 64> buffer;
        uint64_t bitlen;
        uint32_t datalen;
    };
    
    static void sha256_transform(SHA256Context& ctx, const uint8_t* data);
    static void sha256_init(SHA256Context& ctx);
    static void sha256_update(SHA256Context& ctx, const uint8_t* data, size_t len);
    static void sha256_final(SHA256Context& ctx, uint8_t* hash);
    
    // Utility functions
    static std::vector<uint8_t> generateSalt();
    static std::vector<uint8_t> pbkdf2(const std::string& password, 
                                       const std::vector<uint8_t>& salt, 
                                       int iterations);
    static std::string bytesToHex(const std::vector<uint8_t>& bytes);
    static std::vector<uint8_t> hexToBytes(const std::string& hex);
    
    // SHA-256 constants
    static constexpr std::array<uint32_t, 64> K = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    
public:
    /**
     * @brief Hash a password with automatic salt generation
     * @param password The plain text password to hash
     * @param iterations Number of PBKDF2 iterations (default: 10000)
     * @return Base64-encoded hash string containing salt and hash
     */
    static std::string hashPassword(const std::string& password, int iterations = DEFAULT_ITERATIONS);
    
    /**
     * @brief Verify a password against a stored hash
     * @param password The plain text password to verify
     * @param storedHash The stored hash string (from hashPassword)
     * @return true if password matches, false otherwise
     */
    static bool verifyPassword(const std::string& password, const std::string& storedHash);
    
    /**
     * @brief Generate a random salt
     * @return Vector of random bytes for use as salt
     */
    static std::vector<uint8_t> generateRandomSalt();
    
    /**
     * @brief Check if a password meets complexity requirements
     * @param password The password to check
     * @return true if password meets requirements, false otherwise
     */
    static bool isPasswordStrong(const std::string& password);
    
    /**
     * @brief Get password strength score (0-100)
     * @param password The password to evaluate
     * @return Strength score from 0 (very weak) to 100 (very strong)
     */
    static int getPasswordStrength(const std::string& password);
};

#endif // PASSWORD_HASH_H
