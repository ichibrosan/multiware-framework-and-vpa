////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cliLogin.h 2025-07-16 08:08 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#ifndef cliLogin_H
#define cliLogin_H

#include "cfgini.h"
// Forward declaration instead of including password.h
class password;

// Remove the LOGIN_TIMEOUT_SECONDS definition - let it use the one from fw-limits.h

/**
 * @brief A class that provides command-line login functionality for VPA applications.
 * 
 * This class handles user authentication through command-line interfaces, including
 * secure password input, session timeout management, and credential storage using
 * configuration files.
 */
class cliLogin
{
private:
    static const time_t LOGIN_TIMEOUT = LOGIN_TIMEOUT_SECONDS;

public:
    // ... rest of the class remains the same
    static bool isLoginExpired(const std::string& lastLoginStr);
    static std::string getPassword();
    static void queryUserForLogin(cfgini& config);
    static void checkPreviousLogin();
};

#endif // cliLogin_H
