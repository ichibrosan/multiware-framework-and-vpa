////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cliLogin.cpp 2025-07-15 18:16 dwg -           //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

bool cliLogin::isLoginExpired(const std::string& lastLoginStr)
{
    if (lastLoginStr.empty())
    {
        printf("DEBUG: No last login timestamp found\n");
        return true;
    }

    try
    {
        // Convert string to time_t
        time_t lastLogin = static_cast<time_t>(std::stoll(lastLoginStr));
        time_t currentTime = time(nullptr);

#ifdef DEBUG_CLI_LOGIN
        printf("DEBUG: Last login timestamp: %ld\n", lastLogin);
        printf("DEBUG: Current timestamp: %ld\n", currentTime);
        printf("DEBUG: Time difference: %ld seconds\n",
               currentTime - lastLogin);
        printf("DEBUG: Timeout threshold: %ld seconds\n", LOGIN_TIMEOUT);
#endif

        // Check if current time minus last login exceeds timeout
        bool expired = (currentTime - lastLogin) > LOGIN_TIMEOUT;
#ifdef DEBUG_CLI_LOGIN
        printf("DEBUG: Login expired: %s\n", expired ? "YES" : "NO");
#endif
        return expired;
    }
    catch (const std::exception& e)
    {
        printf("ERROR: Failed to parse last login timestamp: %s\n", e.what());
        return true; // Treat parsing errors as expired
    }
}

std::string cliLogin::getPassword()
{
    std::string password;
    printf("Password: ");
    std::flush(std::cout);

    // Turn off echo for password input
    struct termios old_term, new_term;
    if (tcgetattr(STDIN_FILENO, &old_term) != 0)
    {
        printf("ERROR: Failed to get terminal attributes\n");
        std::getline(std::cin, password);
        return password;
    }

    new_term = old_term;
    new_term.c_lflag &= ~(ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) != 0)
    {
        printf("ERROR: Failed to set terminal attributes\n");
        std::getline(std::cin, password);
        return password;
    }

    std::getline(std::cin, password);

    // Restore echo
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    printf("\n");
    return password;
}


void cliLogin::queryUserForLogin(cfgini& config)
{
    printf("\n=== VPA Login Required ===\n");

    // Get username
    std::string username;
    printf("Username: ");
    std::flush(std::cout);
    std::getline(std::cin, username);

    if (username.empty())
    {
        printf("Username cannot be empty. Exiting.\n");
        return;
    }

    // Get password
    std::string userPassword = getPassword();

    if (userPassword.empty())
    {
        printf("Password cannot be empty. Exiting.\n");
        return;
    }

    // Use the existing password lookup function
    password passwordObj;
    int handle = passwordObj.lookup_username_password(username, userPassword);

    if (handle <= 0)
    {
        printf("Authentication failed. Invalid username or password.\n");
        return;
    }

    printf("Authentication successful. Handle: %d\n", handle);

    // // Create or update the config
    // config.addSection("Credentials");
    // config.setVariable("Credentials", "authusername", username);
    //
    // // Set current time as last_login
    // time_t currentTime = time(nullptr);
    // std::string timeStr = std::to_string(currentTime);
    // config.setVariable("Credentials", "last_login", timeStr);
    //
    // printf("DEBUG: Setting last_login to: %s\n", timeStr.c_str());
    //
    // // Set the actual handle from password lookup
    // config.setVariable("Credentials", "handle", std::to_string(handle));
    //
    //     // Save the configuration
    // if (config.save())
    // {
    //     printf("Login credentials saved successfully.\n");
    // }
    // else
    // {
    //     printf("ERROR: Failed to save login credentials.\n");
    // }
}

void cliLogin::checkPreviousLogin(const std::string& configPath)
{
    cfgini config(configPath);

    // Try to load existing config
    if (!config.load())
    {
        printf("No previous login configuration found.\n");
        queryUserForLogin(config);
        return;
    }

    // Check for credentials section and credentials
    std::string username = config.
        getVariable("Credentials", "authusername", "");
    std::string lastLogin = config.getVariable("Credentials", "last_login", "");
    std::string authHandle = config.getVariable("Credentials", "handle", "");

    if (!username.empty())
    {
        printf("=== Previous VPA Login Information ===\n");
        printf("Username: %s\n", username.c_str());

        if (!lastLogin.empty())
        {
            printf("Last Login: %s\n", lastLogin.c_str());

            // Check if login has timed out
            if (isLoginExpired(lastLogin))
            {
                printf("Login has expired. Please re-authenticate.\n");
                queryUserForLogin(config);
                return;
            }
        }
        else
        {
            printf("No last login timestamp found. Please re-authenticate.\n");
            queryUserForLogin(config);
            return;
        }

        if (!authHandle.empty())
        {
            printf("Auth Handle: %s\n", authHandle.c_str());
        }

        printf("======================================\n");
        printf("Login is still valid.\n");
    }
    else
    {
        printf("No previous login credentials found in config.\n");
        queryUserForLogin(config);
    }
}
