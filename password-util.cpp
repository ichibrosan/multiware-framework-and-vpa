////////////////////////////////////////////////////////////////////
// ~/public_html/fw/password-util.cpp 2025-07-15 18:16 dwg -      //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
#include "password-hash.h"
#include <iostream>

int main() {
    // Hash a password
    std::string password = "mySecurePassword123!";
    std::string hashedPassword = PasswordHash::hashPassword(password);
    std::cout << "Hashed password: " << hashedPassword << std::endl;
    
    // Verify password
    bool isValid = PasswordHash::verifyPassword(password, hashedPassword);
    std::cout << "Password verification: " << (isValid ? "SUCCESS" : "FAILED") << std::endl;
    
    // Check password strength
    int strength = PasswordHash::getPasswordStrength(password);
    std::cout << "Password strength: " << strength << "/100" << std::endl;
    
    bool isStrong = PasswordHash::isPasswordStrong(password);
    std::cout << "Password is strong: " << (isStrong ? "YES" : "NO") << std::endl;
    
    return 0;
}
