/////////////////////////////////////////////////////////////////////////
// checkAuth.h - Authentication checker using cfgini                   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <ctime>
#include "cfgini.h"

/**
 * @class checkAuth
 * @brief A class for checking user authentication based on login time and lifetime
 *
 * This class uses the cfgini class to read configuration files and check
 * if a user's last login time is within the specified login lifetime.
 */
class checkAuth
{
private:
    /**
     * The cfgini instance for reading configuration
     */
    cfgini m_config;

    /**
     * Login lifetime in minutes
     */
    int m_loginLifetimeMinutes;

    /**
     * Configuration file path
     */
    std::string m_configFilePath;

public:
    /**
     * Constructor with config file path and login lifetime
     * @param configFilePath Path to the configuration file
     * @param loginLifetimeMinutes Login lifetime in minutes (default: 60)
     */
    checkAuth(const std::string& configFilePath, int loginLifetimeMinutes = 60);

    /**
     * Destructor
     */
    ~checkAuth();

    /**
     * Sets the login lifetime in minutes
     * @param minutes Login lifetime in minutes
     */
    void setLoginLifetime(int minutes);

    /**
     * Gets the current login lifetime in minutes
     * @return Login lifetime in minutes
     */
    int getLoginLifetime() const;

    /**
     * Checks if the user's authentication is still valid
     * @param username Username to check (optional, uses "Credentials" section if empty)
     * @return True if authentication is valid, false otherwise
     */
    bool isAuthValid(const std::string& username = "");

    /**
     * Gets the last login time from the configuration
     * @param username Username to check (optional, uses "Credentials" section if empty)
     * @return Last login time as time_t, or 0 if not found
     */
    time_t getLastLoginTime(const std::string& username = "");

    /**
     * Checks if the last login time is within the specified lifetime
     * @param lastLoginTime The last login time to check
     * @return True if within lifetime, false otherwise
     */
    bool isWithinLifetime(time_t lastLoginTime);

    /**
     * Gets the current time
     * @return Current time as time_t
     */
    time_t getCurrentTime();

    /**
     * Reloads the configuration from file
     * @return True if successful, false otherwise
     */
    bool reloadConfig();
};

////////////////////////
// eof - checkAuth.h //
////////////////////////
