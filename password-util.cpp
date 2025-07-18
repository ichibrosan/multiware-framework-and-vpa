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
