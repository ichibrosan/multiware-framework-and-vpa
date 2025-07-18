#include "password-hash.h"
#include <algorithm>
#include <chrono>
#include <cctype>

// SHA-256 implementation
void PasswordHash::sha256_transform(SHA256Context& ctx, const uint8_t* data) {
    uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
    
    for (i = 0, j = 0; i < 16; ++i, j += 4) {
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    }
    
    for (; i < 64; ++i) {
        m[i] = ((m[i - 2] >> 17) | (m[i - 2] << 15)) ^ ((m[i - 2] >> 19) | (m[i - 2] << 13)) ^ (m[i - 2] >> 10);
        m[i] += m[i - 7];
        m[i] += ((m[i - 15] >> 7) | (m[i - 15] << 25)) ^ ((m[i - 15] >> 18) | (m[i - 15] << 14)) ^ (m[i - 15] >> 3);
        m[i] += m[i - 16];
    }
    
    a = ctx.state[0];
    b = ctx.state[1];
    c = ctx.state[2];
    d = ctx.state[3];
    e = ctx.state[4];
    f = ctx.state[5];
    g = ctx.state[6];
    h = ctx.state[7];
    
    for (i = 0; i < 64; ++i) {
        t1 = h + (((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7))) + ((e & f) ^ (~e & g)) + K[i] + m[i];
        t2 = (((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10))) + ((a & b) ^ (a & c) ^ (b & c));
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    
    ctx.state[0] += a;
    ctx.state[1] += b;
    ctx.state[2] += c;
    ctx.state[3] += d;
    ctx.state[4] += e;
    ctx.state[5] += f;
    ctx.state[6] += g;
    ctx.state[7] += h;
}

void PasswordHash::sha256_init(SHA256Context& ctx) {
    ctx.datalen = 0;
    ctx.bitlen = 0;
    ctx.state[0] = 0x6a09e667;
    ctx.state[1] = 0xbb67ae85;
    ctx.state[2] = 0x3c6ef372;
    ctx.state[3] = 0xa54ff53a;
    ctx.state[4] = 0x510e527f;
    ctx.state[5] = 0x9b05688c;
    ctx.state[6] = 0x1f83d9ab;
    ctx.state[7] = 0x5be0cd19;
}

void PasswordHash::sha256_update(SHA256Context& ctx, const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        ctx.buffer[ctx.datalen] = data[i];
        ctx.datalen++;
        if (ctx.datalen == 64) {
            sha256_transform(ctx, ctx.buffer.data());
            ctx.bitlen += 512;
            ctx.datalen = 0;
        }
    }
}

void PasswordHash::sha256_final(SHA256Context& ctx, uint8_t* hash) {
    uint32_t i = ctx.datalen;
    
    if (ctx.datalen < 56) {
        ctx.buffer[i++] = 0x80;
        while (i < 56) {
            ctx.buffer[i++] = 0x00;
        }
    } else {
        ctx.buffer[i++] = 0x80;
        while (i < 64) {
            ctx.buffer[i++] = 0x00;
        }
        sha256_transform(ctx, ctx.buffer.data());
        std::fill(ctx.buffer.begin(), ctx.buffer.begin() + 56, 0);
    }
    
    ctx.bitlen += ctx.datalen * 8;
    ctx.buffer[63] = ctx.bitlen;
    ctx.buffer[62] = ctx.bitlen >> 8;
    ctx.buffer[61] = ctx.bitlen >> 16;
    ctx.buffer[60] = ctx.bitlen >> 24;
    ctx.buffer[59] = ctx.bitlen >> 32;
    ctx.buffer[58] = ctx.bitlen >> 40;
    ctx.buffer[57] = ctx.bitlen >> 48;
    ctx.buffer[56] = ctx.bitlen >> 56;
    sha256_transform(ctx, ctx.buffer.data());
    
    for (i = 0; i < 4; ++i) {
        hash[i]      = (ctx.state[0] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 4]  = (ctx.state[1] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 8]  = (ctx.state[2] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 12] = (ctx.state[3] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 16] = (ctx.state[4] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 20] = (ctx.state[5] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 24] = (ctx.state[6] >> (24 - i * 8)) & 0x000000ff;
        hash[i + 28] = (ctx.state[7] >> (24 - i * 8)) & 0x000000ff;
    }
}

std::vector<uint8_t> PasswordHash::generateSalt() {
    std::vector<uint8_t> salt(SALT_LENGTH);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);
    
    for (size_t i = 0; i < SALT_LENGTH; ++i) {
        salt[i] = dis(gen);
    }
    
    return salt;
}

std::vector<uint8_t> PasswordHash::pbkdf2(const std::string& password, 
                                          const std::vector<uint8_t>& salt, 
                                          int iterations) {
    std::vector<uint8_t> dk(HASH_LENGTH);
    std::vector<uint8_t> u(HASH_LENGTH);
    std::vector<uint8_t> t(HASH_LENGTH);
    
    // PBKDF2 implementation
    for (int i = 1; i <= 1; ++i) {  // We only need one block for 32-byte output
        // First iteration: HMAC-SHA256(password, salt || i)
        std::vector<uint8_t> input = salt;
        input.push_back((i >> 24) & 0xff);
        input.push_back((i >> 16) & 0xff);
        input.push_back((i >> 8) & 0xff);
        input.push_back(i & 0xff);
        
        // HMAC-SHA256
        std::vector<uint8_t> key = std::vector<uint8_t>(password.begin(), password.end());
        if (key.size() > 64) {
            SHA256Context ctx;
            sha256_init(ctx);
            sha256_update(ctx, key.data(), key.size());
            uint8_t hash[32];
            sha256_final(ctx, hash);
            key = std::vector<uint8_t>(hash, hash + 32);
        }
        
        if (key.size() < 64) {
            key.resize(64, 0);
        }
        
        std::vector<uint8_t> ipad(64), opad(64);
        for (int j = 0; j < 64; ++j) {
            ipad[j] = key[j] ^ 0x36;
            opad[j] = key[j] ^ 0x5c;
        }
        
        SHA256Context ctx;
        sha256_init(ctx);
        sha256_update(ctx, ipad.data(), 64);
        sha256_update(ctx, input.data(), input.size());
        sha256_final(ctx, u.data());
        
        sha256_init(ctx);
        sha256_update(ctx, opad.data(), 64);
        sha256_update(ctx, u.data(), 32);
        sha256_final(ctx, u.data());
        
        t = u;
        
        // Remaining iterations
        for (int j = 1; j < iterations; ++j) {
            sha256_init(ctx);
            sha256_update(ctx, ipad.data(), 64);
            sha256_update(ctx, u.data(), 32);
            sha256_final(ctx, u.data());
            
            sha256_init(ctx);
            sha256_update(ctx, opad.data(), 64);
            sha256_update(ctx, u.data(), 32);
            sha256_final(ctx, u.data());
            
            for (int k = 0; k < 32; ++k) {
                t[k] ^= u[k];
            }
        }
        
        dk = t;
    }
    
    return dk;
}

std::string PasswordHash::bytesToHex(const std::vector<uint8_t>& bytes) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (uint8_t byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}

std::vector<uint8_t> PasswordHash::hexToBytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

std::string PasswordHash::hashPassword(const std::string& password, int iterations) {
    std::vector<uint8_t> salt = generateSalt();
    std::vector<uint8_t> hash = pbkdf2(password, salt, iterations);
    
    // Format: iterations:salt:hash (all in hex)
    std::stringstream ss;
    ss << iterations << ":" << bytesToHex(salt) << ":" << bytesToHex(hash);
    return ss.str();
}

bool PasswordHash::verifyPassword(const std::string& password, const std::string& storedHash) {
    try {
        // Parse stored hash: iterations:salt:hash
        size_t pos1 = storedHash.find(':');
        size_t pos2 = storedHash.find(':', pos1 + 1);
        
        if (pos1 == std::string::npos || pos2 == std::string::npos) {
            return false;
        }
        
        int iterations = std::stoi(storedHash.substr(0, pos1));
        std::string saltHex = storedHash.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string hashHex = storedHash.substr(pos2 + 1);
        
        std::vector<uint8_t> salt = hexToBytes(saltHex);
        std::vector<uint8_t> expectedHash = hexToBytes(hashHex);
        
        std::vector<uint8_t> computedHash = pbkdf2(password, salt, iterations);
        
        // Constant-time comparison
        bool match = true;
        if (computedHash.size() != expectedHash.size()) {
            match = false;
        }
        
        for (size_t i = 0; i < std::min(computedHash.size(), expectedHash.size()); ++i) {
            if (computedHash[i] != expectedHash[i]) {
                match = false;
            }
        }
        
        return match;
    } catch (...) {
        return false;
    }
}

std::vector<uint8_t> PasswordHash::generateRandomSalt() {
    return generateSalt();
}

bool PasswordHash::isPasswordStrong(const std::string& password) {
    if (password.length() < 8) return false;
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    
    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        else if (std::islower(c)) hasLower = true;
        else if (std::isdigit(c)) hasDigit = true;
        else if (std::ispunct(c)) hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int PasswordHash::getPasswordStrength(const std::string& password) {
    int score = 0;
    
    // Length scoring
    if (password.length() >= 8) score += 25;
    if (password.length() >= 12) score += 15;
    if (password.length() >= 16) score += 10;
    
    // Character variety
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (std::isupper(c)) hasUpper = true;
        else if (std::islower(c)) hasLower = true;
        else if (std::isdigit(c)) hasDigit = true;
        else if (std::ispunct(c)) hasSpecial = true;
    }
    
    if (hasUpper) score += 15;
    if (hasLower) score += 15;
    if (hasDigit) score += 15;
    if (hasSpecial) score += 15;
    
    return std::min(score, 100);
}
