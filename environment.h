//////////////////////////////////////////////////////////////////////////
// daphe.goodall.com:/home/doug/public_html/fw/environment.h 2025/01/10 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_ENVIRONMENT_H
#define MULTIWARE_ENVIRONMENT_H

#include "std.h"
#include "fw-limits.h"
#include "osIface.h"
/**
 * Represents the operating system used in the current application environment.
 *
 * This variable is utilized for determining or adapting functionality based on
 * the specific operating system being executed.
 */
extern osIface *gpOS;
#include "CLog.hpp"
/**
 * Represents the global logging instance used for recording application logs.
 *
 * This object is utilized throughout the application to maintain standardized
 * and centralized logging functionality, facilitating debugging and auditing
 * processes.
 */
extern CLog   *gpLog;
#include "shared.h"
/**
 * Pointer to a shared resource or object within the application.
 *
 * This variable is used to reference a globally accessible shared resource
 * or handler. Its purpose may vary depending on the implementation context,
 * such as managing application-wide settings, accessing shared functionality,
 * or tracking global states.
 */
extern shared *gpSh;

/**
 * Represents the environment in which the application is executed.
 *
 * This class encapsulates information and methods that pertain to the state
 * and configuration of the runtime environment, such as system properties,
 * dependencies, and platform-specific information. It provides functionality
 * to check and manipulate these attributes as needed.
 */
class environment {
	/**
	 * Pointer to the system log instance used for logging application events.
	 *
	 * This member is utilized to record log messages for debugging, auditing,
	 * or monitoring purposes, depending on the application's requirements.
	 */
	CSysLog * m_pSysLog;

	/**
	 * Indicates whether the Cgicc library is present in the current environment.
	 *
	 * This boolean variable is set during the initialization process to determine
	 * if the Cgicc library is available and can be utilized for CGI scripting.
	 */
	bool m_bCgiccPresent;
	/**
	 * Indicates whether the cURL library is present in the environment.
	 *
	 * This boolean variable is set during runtime to reflect the availability
	 * of the cURL library, which is required for certain network operations.
	 */
	bool m_bCurlPresent;
	/**
	 * Indicates whether the MWCGI component is present in the system.
	 *
	 * This boolean variable is used to determine if the MWCGI component
	 * has been detected and is available for use within the application.
	 */
	bool m_bMwcgiPresent;

	/**
	 * Holds the configuration path or identifier for the MWCgi component.
	 *
	 * This variable is used to store pertinent data related to the Middleware CGI
	 * (MWCgi) integration or functionality within the application.
	 */
	char m_szMwcgi[BUFSIZ];
	/**
	 * Stores the version string of the cURL library being used.
	 *
	 * This character array is populated when the environment checks if cURL
	 * is installed using `check_curl_installed()`. Upon a successful check,
	 * the version string of the cURL library is read from the system and
	 * stored in this variable. It can be accessed later using the
	 * `get_curl_version()` method.
	 *
	 * The size of the array is determined by the macro `BUFSIZ`, ensuring
	 * it can accommodate a typical cURL version string.
	 */
	char m_szCurlVersion[BUFSIZ];
	/**
	 * Holds the log name used for identifying logs within the application.
	 *
	 * This character pointer is intended to store the name or identifier
	 * for a specific logging context, typically initialized and managed
	 * during the application's runtime to assist in log categorization.
	 */
	char *m_pszLogname;
	/**
	 * Holds the name of the log file used for storing application logs.
	 *
	 * This variable is initialized and updated based on the logging configuration
	 * provided by the application to keep track of log outputs.
	 */
	char m_szLogname[FILENAME_MAX];
	/**
	 * Stores the name of the log file used for logging purposes.
	 *
	 * This string is assigned to specify the log file intended for capturing
	 * logs generated during application runtime.
	 */
	std::string m_ssLogname;

	/**
	 * Pointer to a null-terminated string representing the remote user's identifier.
	 *
	 * This variable is typically used to store the username or credentials of a
	 * remote user during authentication or session management processes.
	 */
	char *m_pszRemoteUser;
	/**
	 * Holds the username for a remote user in the system.
	 *
	 * This variable is used to store the identifier of a remote user
	 * during authentication or communication processes.
	 */
	char m_szRemoteUser[UT_NAMESIZE];
	/**
	 * Holds the username of a remote user.
	 *
	 * This string is used to identify and authenticate a user
	 * accessing the system from a remote location.
	 */
	std::string m_ssRemoteUser;

	/**
	 * Holds the hostname of the server or client system.
	 *
	 * This character array is used to store the network hostname, which is typically
	 * determined during initialization or retrieved via system calls for network operations.
	 */
	char m_szHostName[DNS_FQDN_SIZE_MAX];
	/**
	 * Holds the name of the network interface being utilized.
	 *
	 * This string is used to identify and manage the specific interface
	 * for communication or data transmission purposes in the application.
	 */
	char m_szIface[IFNAMSIZ];

	/**
	 * Stores the IP address as a string.
	 *
	 * This variable is used to hold the network IP address, typically in IPv4 or IPv6 format,
	 * and is set during network initialization or configuration processes.
	 */
	char m_szIP[DNS_FQDN_SIZE_MAX];
	/**
	 * Represents the IP address as a string.
	 *
	 * This variable is used to store the IP address associated with a specific
	 * connection or configuration in string format.
	 */
	std::string m_ssIP;

	/**
	 * Holds the name of the script currently being executed.
	 *
	 * This pointer is used to store the name of the script for reference
	 * during the program's execution. It is typically assigned at runtime
	 * based on the context of the script invocation.
	 */
	char *m_pszScriptName;
	/**
	 * Represents the runtime environment for the application.
	 *
	 * This object is used to manage and store information regarding
	 * the application's operating context, including configurations,
	 * dependencies, and environment-specific settings.
	 *
	 * @return Provides access to environment-related metadata and functionality.
	 */
public:
    environment();

	/**
	 * Retrieves the public IP address of the system.
	 *
	 * This function is used to obtain the public IP address currently assigned
	 * to the system, which may be useful for networking or remote access purposes.
	 *
	 * @return A pointer to a character array containing the public IP address as a string.
	 *         The caller is responsible for handling the memory if the implementation dictates so.
	 */
	char * get_public_ip();

	/**
	 * Updates and stores the system's public IP address in shared memory.
	 *
	 * This method retrieves the current public IP address of the system through an
	 * external API (`ip.me`) and updates the shared memory with the obtained IP.
	 * It uses an intermediate local file to temporarily store the IP data and reads
	 * it for further processing.
	 */
	void set_public_ip();

	/**
	 * Checks if the cURL library is installed in the current environment.
	 *
	 * This method performs a system-level check to determine whether the
	 * cURL library is available and can be used.
	 *
	 * @return A boolean value indicating whether the cURL library is installed.
	 */
	bool check_curl_installed();

	/**
	 * Retrieves the hostname of the current machine.
	 *
	 * This function queries the system to obtain the hostname of the
	 * machine where the program is being executed.
	 *
	 * @param buffer A character array where the hostname will be stored.
	 * @param size The size of the buffer to ensure the hostname fits within bounds.
	 * @return Returns 0 on success or a non-zero value if an error occurs, such as
	 * if the buffer size is insufficient or the hostname cannot be retrieved.
	 */
	std::string get_hostname(bool bDebug);
	/**
	 * Sets the hostname for a network connection or service.
	 *
	 * This function assigns a specified hostname to be used for configuration
	 * or connection purposes in the associated service or network operations.
	 *
	 * @param hostname A string representing the hostname to be set.
	 */
	void        set_hostname(bool bDebug);
	/**
	 * Retrieves the interface object that is currently in use or configured.
	 *
	 * This method provides access to the interface instance, allowing interaction
	 * or inspection of its implementation details.
	 *
	 * @param interface_name The name of the interface to retrieve.
	 * @return A pointer to the interface object if found, or nullptr if not available.
	 */
	std::string get_interface(bool bDebug);
	/**
	 * Retrieves the IP address associated with the local machine or a specific interface.
	 *
	 * This function is used to obtain the IP address information which might be
	 * required for network-related operations such as establishing connections
	 * or configuring settings.
	 *
	 * @param interface_name The name of the network interface for which the IP address is requested.
	 *                       If null or empty, the function retrieves the default IP address.
	 * @return A string representing the IP address. Returns an empty string if the IP address
	 *         cannot be determined.
	 */
	std::string get_ip(bool bDebug);
	/**
	 * Retrieves the current protocol being used by the system or application.
	 *
	 * This method returns the string representation of the protocol,
	 * typically used for communication or data transfer, such as HTTP, FTP, etc.
	 *
	 * @return A string representing the current protocol in use.
	 */
	std::string get_protocol(bool bDebug);
	/**
	 * Sets the protocol to be used for communication.
	 *
	 * This method allows the specification of the desired protocol for subsequent
	 * operations, ensuring compatibility and proper communication setup.
	 *
	 * @param protocol A string representing the protocol type (e.g., "HTTP", "FTP").
	 */
	void        set_protocol(bool bDebug);

	/**
	 * Retrieves the root directory path for CGI scripts.
	 *
	 * This function determines and returns the directory path where
	 * CGI scripts are located and executed from.
	 *
	 * @param server_config Specifies the server configuration object
	 *                      containing necessary settings to locate the CGI root.
	 * @return Returns a string representing the CGI root directory path.
	 */
	std::string get_cgi_root(bool bDebug);
	/**
	 * Retrieves the CGI root directory path as a null-terminated C-style string.
	 *
	 * This function is used to obtain the root directory for CGI scripts in the
	 * current environment. It fetches the directory path configured for script execution.
	 *
	 * @param none This function takes no parameters.
	 * @return A pointer to a null-terminated string containing the CGI root directory path.
	 */
	char *      get_cgi_root_as_sz(bool bDebug);
	/**
	 * Sets the root directory for CGI scripts.
	 *
	 * This function defines the base directory from which CGI scripts
	 * will be executed by the application.
	 *
	 * @param cgi_root The path to be set as the CGI root directory.
	 */
	void        set_cgi_root(bool bDebug);

	/**
	 * Retrieves the root directory or path where image assets are stored in the application.
	 *
	 * This method is tasked with providing the base location for image-related resources,
	 * which might be used for loading, processing, or displaying images.
	 *
	 * @param none This method does not take any parameters.
	 * @return A string representing the root directory or path for image resources.
	 */
	std::string get_img_root(bool bDebug);
	/**
	 * Sets the root directory path for image storage.
	 *
	 * This method updates the root directory where image files are stored or retrieved
	 * for further processing.
	 *
	 * @param path The file system path to the root directory for image storage.
	 */
	void        set_img_root(bool bDebug);

	/**
	 * Retrieves the root directory path where style files are stored.
	 *
	 * This method is typically used to obtain the base path for styles that
	 * can be used in various components of an application.
	 *
	 * @return A string representing the root directory path for styles.
	 */
	std::string get_styles_root(bool bDebug);
	/**
	 * Sets the root directory for fetching style files.
	 *
	 * This method defines the base directory path from where style-related resources
	 * can be accessed.
	 *
	 * @param stylesRoot A string representing the root directory of styles.
	 */
	void        set_styles_root(bool bDebug);

	/**
	 * Retrieves the root directory of the journal system.
	 *
	 * This function provides the base directory path for storing or accessing
	 * journal data within the system.
	 *
	 * @param systemPath The path to the system's file hierarchy where the journal resides.
	 * @param identifier A unique identifier to locate the specific journal.
	 * @return A string containing the full path to the journal's root directory.
	 */
	std::string get_journal_root(bool bDebug);
	/**
	 * Sets the root path of the journal used for storing and retrieving data.
	 *
	 * This function defines the base directory where the journal files
	 * will be located. The specified path must be valid and accessible to
	 * ensure proper operation.
	 *
	 * @param path The file path to set as the journal's root directory.
	 */
	void        set_journal_root(bool bDebug);

	/**
	 * Extracts the username from a given input string.
	 *
	 * This function processes the provided input, interprets its structure, and
	 * retrieves the username component.
	 *
	 * @return The extracted username as a string.
	 */
	std::string extract_username();

	/**
	 * Checks whether the cURL library is present and available in the system environment.
	 *
	 * This method verifies the existence of the cURL library to ensure HTTP request
	 * functionality can be utilized within the software.
	 *
	 * @return Returns true if cURL is present, otherwise false.
	 */
	bool is_curl_present();
	/**
	 * Indicates whether the 'netstat' command-line utility is available in the environment.
	 *
	 * This function checks the system's capabilities to determine if the 'netstat'
	 * utility exists and can be executed for network-related operations.
	 *
	 * @return True if the 'netstat' utility is present, false otherwise.
	 */
	bool is_netstat_present();

	/**
	 * Retrieves the version string of the cURL library being used.
	 *
	 * This method queries the cURL library to obtain its version information,
	 * returning it as a string.
	 *
	 * @return A string containing the version of the cURL library.
	 */
	char *get_curl_version();


	/**
	 * Retrieves the logname associated with the current environment or session.
	 *
	 * The function fetches the value used to identify log entries or sessions,
	 * which can be utilized for debugging, auditing, or tracking purposes.
	 *
	 * @return A constant character pointer representing the logname.
	 */
	char *get_szLogname();

	/**
	 * Retrieves the log name associated with the current session.
	 *
	 * This function determines the log name based on session-specific
	 * parameters or configurations.
	 *
	 * @return The log name as a string for the current session.
	 */
	std::string get_ssLogname();

	/**
	 * Retrieves the name of the currently executing script.
	 *
	 * This method determines and returns the filename or identifier
	 * of the script that is currently being executed by the application.
	 *
	 * @return The name of the currently executing script as a string.
	 */
	char *get_scriptname();

};

#endif //MULTIWARE_ENVIRONMENT_H
