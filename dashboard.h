//#################################################################
//# /home/devo/public_html/fw/dashboard.h 2025-02-19              #
//# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. #
//#################################################################

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "mwfw2.h"

enum {
    JOURNAL = 1<<0,
    LOGOUT  = 1<<1,
    MENU    = 1<<2,
	PREFS   = 1<<3,
    NUM_DASHBOARD_BUTTONS = 4
};

/**
 * @class dashboard
 *
 * @brief Provides functionalities for managing the web interface dashboard components,
 * including authentication, navigation bar handling, and toggle processing.
 *
 * The dashboard class interacts with CGI bindings and system logging to manage
 * user authentication and dynamically create or respond to user interface events.
 */
class dashboard {
	/**
	 * A pointer to a `cgibind` object, used to manage and interact with CGI-related data.
	 *
	 * This member is typically utilized to handle CGI input and output variables,
	 * as well as to process HTTP request metadata such as referrer information.
	 */
	cgibind * m_pCgiBind;
	/**
	 * A pointer to the system log instance used for logging system-related activities.
	 *
	 * This variable holds an instance of the `CSysLog` class, which provides methods
	 * for sending log messages to the system log. It is primarily used within the
	 * `dashboard` class to log informational or debugging messages related to system
	 * operations or application behavior.
	 *
	 * The `m_pSysLog` variable is intended to facilitate centralized logging and assist
	 * in monitoring application performance, errors, or system-level events. The logging
	 * performed through this object is compliant with the syslog service.
	 */
	CSysLog * m_pSysLog;

	/**
	 * Stores the authenticated username for the current session or user.
	 *
	 * This member variable is populated during the authentication process
	 * by copying the username from a shared memory structure to ensure it
	 * is accessible within the dashboard functionality. It is primarily
	 * used to display or manage user-related information in the dashboard
	 * interface.
	 *
	 * The size of the character array is determined by the constant
	 * `UT_NAMESIZE`, which defines the maximum allowed length of the
	 * username including the null-terminator.
	 */
	char m_szAuthUserName[UT_NAMESIZE];
	/**
	 * Stores the authenticated user's first name.
	 *
	 * This character array is populated upon successful authentication
	 * of the user, using the credentials associated with the provided
	 * handle. It is later used for displaying the authenticated user's
	 * information in the dashboard interface.
	 *
	 * Size of the array is determined by the constant UT_NAMESIZE.
	 */
	char m_szAuthFirstName[UT_NAMESIZE];
	/**
	 * Stores the last name of the authenticated user.
	 *
	 * This variable is part of the user authentication credentials and is populated
	 * during the dashboard initialization process. The value is retrieved from the
	 * shared memory associated with the provided authentication handle and is
	 * used for display purposes in the dashboard (e.g., showing the user's full name).
	 *
	 * The size of the array is defined by the constant `UT_NAMESIZE`.
	 */
	char m_szAuthLastName[UT_NAMESIZE];
	/**
	 * @brief Stores the authentication level of the user.
	 *
	 * This member represents the privilege or authorization level of the user
	 * currently authenticated and interacting with the dashboard. Its value
	 * is used in various parts of the dashboard functionality to determine
	 * the user's access rights and privileges.
	 *
	 * The value for this member is retrieved from the shared memory credentials
	 * during the initialization of the dashboard and can separate users with
	 * different roles, such as "admin" or "devo". It is later utilized for
	 * rendering UI elements (e.g., Privilege Level in the dashboard) and
	 * access control decisions within dashboard functions.
	 *
	 * @note The size of the array is determined by the constant `UT_NAMESIZE`.
	 */
	char m_szAuthLevel[UT_NAMESIZE];
	/**
	 * Holds the universally unique identifier (UUID) of the authenticated user.
	 *
	 * This member is used to store and reference the UUID that identifies the authenticated
	 * user's session or credentials in the system. It is typically set during the user's
	 * login process, based on the credentials retrieved from shared memory.
	 *
	 * This UUID plays a critical role in associating actions or data to a specific authenticated
	 * user within the "dashboard" class.
	 *
	 * Size is defined by the constant `UUID_SIZE` to ensure compatibility and consistency
	 * throughout the system.
	 */
	char m_szAuthUUID[UUID_SIZE];

	/**
	 * Constructs a dashboard object with the specified parameters.
	 *
	 * @param handle An integer representing the authentication handle. Used to validate if the user is authenticated.
	 * @param buttons An integer indicating the initial number of buttons to display on the dashboard.
	 * @param pszFile A constant character pointer specifying the file path for the dashboard configuration or request.
	 * @param ssUsername A string representing the username provided for authentication purposes.
	 * @param ssPassword A string representing the password provided for authentication purposes.
	 * @return None. This is a constructor and does not return any value.
	 */
public:
    dashboard(
        int handle,
        int buttons,
        const char *pszFile,
        std::string ssUsername,
        std::string ssPassword);

	/**
	 * Generates a CGI URL with a specified name and handle.
	 *
	 * This method constructs a URL for a CGI script by appending a query parameter
	 * with the provided `handle` to the base URL generated using the provided `pszName`.
	 * The constructed URL is intended for use within the application.
	 *
	 * @param pszName The name of the CGI script for which the URL is being generated.
	 * @param handle An integer value used as a query parameter to uniquely identify the session or context.
	 * @return A string containing the fully constructed CGI URL.
	 */
	static std::string form_cgi(
        const char *pszName,
        int handle);

	/**
	 * Establishes a connection to the virtual pad (vpad) server and sends a wake-up message to activate it.
	 * This method sets up a client socket, resolves the server information, and communicates with the server
	 * using predefined configuration parameters. It is triggered by the presence of specific CGI parameters.
	 *
	 * Functionality includes:
	 * - Resolving the server hostname to fetch network address information.
	 * - Establishing a socket-based connection to the vpad server.
	 * - Sending a predefined wake-up message to trigger server-side behavior.
	 * - Handling errors related to socket creation, connection, and message transmission.
	 *
	 * Steps:
	 * - Resolves "localhost" as the server's hostname.
	 * - Configures server structure with address family, port, and IP.
	 * - Creates a stream socket for communication.
	 * - Initiates the connection to the server.
	 * - Sends a "Hello World!!" message to interact and wake the target server process.
	 * - Cleans up resources by closing the socket after communication.
	 *
	 * This function is primarily used as part of process_toggles to respond to
	 * specific CGI form inputs enabling the vpad feature.
	 *
	 * Precondition:
	 * - The server must be operational and reachable at the predefined port (VPA_PORT).
	 * - The network environment must support TCP/IP communication.
	 *
	 * Postcondition:
	 * - The vpad server is notified and activated after the message is sent.
	 *
	 * Errors:
	 * - If socket creation fails, an error message is displayed and the application exits.
	 * - If connection to the server cannot be established, an error message is displayed and the application exits.
	 * - If the message cannot be sent successfully, an error message is displayed and the application exits.
	 */
	void start_vpad();

	/**
	 * Generates the navigation bar for the dashboard and handles toggle options,
	 * authentication levels, and the creation of buttons based on user permissions.
	 *
	 * @param handle An integer representing the user's session or process handle.
	 * @param buttons An integer bitmask specifying which buttons to display (e.g., JOURNAL, LOGOUT).
	 * @param ssCgiName A string containing the name of the CGI script to be used for actions.
	 * @param ssUsername A string representing the username for the session.
	 * @param ssPassword A string representing the password for the session.
	 */
	void navbar(
        int handle,
        int buttons,
        std::string ssCgiName,
        std::string ssUsername,
        std::string ssPassword);


	/**
	 * Adjusts and processes toggle values based on the current user's authentication level
	 * and submitted form variables. If the user has sufficient authorization, it modifies
	 * shared memory variables and performs required actions based on CGI form input.
	 *
	 * @param ssCgiName The name of the CGI script being executed.
	 * @param ssUsername The username of the authenticated user.
	 * @param ssPassword The password of the authenticated user.
	 * @param handle The handle object used for managing CGI sessions.
	 */
	void process_toggles(
        std::string ssCgiName,
        std::string ssUsername,
        std::string ssPassword,
        int handle);

};

#endif //DASHBOARD_H
