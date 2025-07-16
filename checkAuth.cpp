////////////////////////////////////////////////////////////////////
// ~/public_html/fw/checkAuth.cpp 2025-07-15 18:16 dwg -          //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "checkAuth.h"
#include <iostream>
#include <sstream>

/**
 * Constructor for the checkAuth class.
 *
 * Initializes a `checkAuth` object by setting the configuration file path
 * and login lifetime in minutes. The constructor also attempts to load
 * the configuration file. If the file cannot be loaded, a warning is printed
 * to the standard error.
 *
 * @param configFilePath The path to the configuration file.
 * @param loginLifetimeMinutes The lifetime of a login in minutes.
 */
checkAuth::checkAuth(const std::string& configFilePath,
                     int loginLifetimeMinutes)
    : m_configFilePath(configFilePath),
      m_loginLifetimeMinutes(loginLifetimeMinutes)
{
    m_config.setFilename(configFilePath);
    if (!m_config.load())
    {
        std::cerr << "Warning: Could not load config file: " << configFilePath
            << std::endl;
    }
}

/**
 * Destructor for the checkAuth class.
 *
 * Cleans up any resources used by the object. This implementation does not
 * perform any specific cleanup as no dynamically allocated resources or
 * custom cleanup logic are required.
 */
checkAuth::~checkAuth()
{
    // Nothing special needed for cleanup
}

/**
 * Sets the login lifetime in minutes.
 *
 * This method updates the duration for which a user's session is
 * considered valid by specifying the login lifetime in minutes.
 *
 * @param minutes Login lifetime in minutes
 */
void checkAuth::setLoginLifetime(int minutes)
{
    m_loginLifetimeMinutes = minutes;
}

/**
 * Retrieves the current login lifetime in minutes.
 * @return The login lifetime in minutes.
 */
int checkAuth::getLoginLifetime() const
{
    return m_loginLifetimeMinutes;
}

/**
 * Checks if the user's authentication is valid based on their last login time.
 *
 * This method retrieves the last login time for the specified username and
 * determines if it is within the allowed login lifetime period. If no login
 * time is found or the login time exceeds the allowed lifetime, the authentication
 * is considered invalid.
 *
 * @param username The username to validate. If empty, the "Credentials" section
 *                 is used by default.
 * @return True if the authentication is valid, false otherwise.
 */
bool checkAuth::isAuthValid(const std::string& username)
{
    time_t lastLoginTime = getLastLoginTime(username);
    if (lastLoginTime == 0)
    {
        return false; // No login time found
    }

    return isWithinLifetime(lastLoginTime);
}

/**
 * Retrieves the last login time for the specified username from the configuration.
 *
 * The function attempts to fetch the value of the "last_login" field for the given username
 * from the internal configuration object. If the username is empty, it defaults to using the
 * "Credentials" section. In case the "last_login" value is not found, is invalid, or is set
 * to "0", the function returns 0. If an exception occurs during parsing, an error message is
 * printed to standard error and 0 is returned.
 *
 * @param username The username for which to retrieve the last login time. If empty, uses
 *                 the "Credentials" section by default.
 * @return The last login time as time_t. Returns 0 if no valid time is found or in case of
 *         an error.
 */
time_t checkAuth::getLastLoginTime(const std::string& username)
{
    std::string sectionName = username.empty() ? "Credentials" : username;

    // Try to get the last_login value from the specified section
    std::string lastLoginStr = m_config.getVariable(
        sectionName, "last_login", "0");

    if (lastLoginStr == "0" || lastLoginStr.empty())
    {
        return 0; // No valid login time found
    }

    try
    {
        return static_cast<time_t>(std::stoll(lastLoginStr));
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error parsing last_login time: " << e.what() << std::endl;
        return 0;
    }
}

/**
 * Checks if the last login time is within the allowed login lifetime.
 *
 * This function calculates the difference between the current time
 * and the provided last login time. If the difference is less than
 * or equal to the allowed login lifetime (converted to seconds), it
 * returns true. Otherwise, it returns false.
 *
 * @param lastLoginTime The last login time to check, represented as time_t.
 * @return True if the last login time is within the allowed lifetime, false otherwise.
 */
bool checkAuth::isWithinLifetime(time_t lastLoginTime)
{
    time_t currentTime = getCurrentTime();
    time_t lifetimeSeconds = m_loginLifetimeMinutes * 60;
    // Convert minutes to seconds

    // Check if the difference between current time and last login is within lifetime
    return (currentTime - lastLoginTime) <= lifetimeSeconds;
}

/**
 * Retrieves the current system time.
 *
 * @return Current time as a time_t object.
 */
time_t checkAuth::getCurrentTime()
{
    return time(nullptr);
}

/**
 * Reloads the configuration from the file.
 *
 * @return True if the configuration is successfully reloaded, false otherwise.
 */
bool checkAuth::reloadConfig()
{
    return m_config.load();
}

//////////////////////////
// eof - checkAuth.cpp //
//////////////////////////
