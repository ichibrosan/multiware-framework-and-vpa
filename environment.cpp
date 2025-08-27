////////////////////////////////////////////////////////////////////
// ~/public_html/fw/environment.cpp 2025-07-15 18:16 dwg -        //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

#define GET_HOSTNAME_AND_PROTOCOL
#define GET_INTERFACE
#define GET_IP
#define GET_ROOTS
#define GET_REMOTE_USER

/**
 * @brief Holds information about a user, including a user's specific data as a string.
 *
 * This structure is used to encapsulate user-related information for processing or storage.
 * It allows the representation of user-specific data using a character pointer.
 *
 * @struct gszUser
 */
char gszUser[32];


/**
 * @class gssUser
 * @brief Represents a user within the system.
 *
 * This class is responsible for managing user-related details and
 * functionalities, including authentication and profile handling.
 *
 * It provides methods to interact with details of a user and perform
 * operations like updating information and validating credentials.
 *
 * The class ensures encapsulation of user-related data and provides
 * controlled access with various public and private member functions.
 */
std::string gssUser;


/**
 * @class Environment
 * @brief Determines the environment in which the MultiWare FrameWork is
 * running and sets many of the variables in the shared region that are
 * referenced by transient programs, command-line, CGI, and xinetd invoked.
 */
environment::environment()
{
	char szTemp[128];

	/**
	 * The first responsibility of the environment constructor is to
	 * establish addressability to the shared region.
	 */
	gpSh = new shared();

	/**
	 * Now that we have access to the shared memory structure, we can
	 * begin collecting the project data. The location of the development
	 * directory can be derived from the fully qualified filespec of this
	 * source file, because the project's c++ source files exist at the
	 * root level of the development tree.
	 * __FILE __ could be /home/doug/public_html/fw/environment.cpp
	 *	gpSh->m_pShMemng->szDevoDir = /home/doug/public_html/fw/
	 */
	std::string ssDevoDir = __FILE__;
	ssDevoDir = std::filesystem::path(ssDevoDir).remove_filename();
	strcpy(gpSh->m_pShMemng->szDevoDir, ssDevoDir.c_str());

	std::string ssBuildFQDS = ssDevoDir;
	ssBuildFQDS.append("build/");
	strcpy(gpSh->m_pShMemng->szBuildFQDS, ssBuildFQDS.c_str());

	std::string ssCgiBinFQDS = ssDevoDir;
	ssCgiBinFQDS.append("cgi-bin/");
	strcpy(gpSh->m_pShMemng->szCgiBinFQDS, ssCgiBinFQDS.c_str());

	std::string ssLogFQDS = ssDevoDir;
	ssLogFQDS.append("log/");
	strcpy(gpSh->m_pShMemng->szLogFQDS, ssLogFQDS.c_str());
	std::string ssLogCmd = "mkdir -p ";
	ssLogCmd.append(ssLogFQDS);
	system(ssLogCmd.c_str());

	std::string ssTempFQDS = ssDevoDir;
	ssTempFQDS.append("tmp/");
	strcpy(gpSh->m_pShMemng->szTempFQDS, ssTempFQDS.c_str());
	std::string ssTempCmd = "mkdir -p ";
	ssTempCmd.append(ssTempFQDS);
	system(ssTempCmd.c_str());

	/********************************************************************
	 * Determine the username under which this application is running
	 * and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szUser))
	{
		extract_username();
	}

	/********************************************************************
	 * Determine the home directory of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szHome))
	{
		construct_szHome();
	}

	/********************************************************************
	 * Determine the Userdir of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szUserFQDS))
	{
		construct_szUserFQDS();
	}

	/********************************************************************
	 * Determine the Sourcedir of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szSourceFQDS))
	{
		construct_szSourceFQDS();
	}

	/********************************************************************
	 * Determine the LogFQDS of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szLogFQDS))
	{
		construct_szLogFQDS();
	}


	/********************************************************************
	 * Determine the config root of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szConfigFQDS))
	{
		construct_szConfigFQDS();
	}

	/********************************************************************
	 * Determine the config filename for the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szConfigFQFS))
	{
		construct_szConfigFQFS();
	}

	/********************************************************************
	 * Determine the log root of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szLogFQDS))
	{
		construct_szLogFQDS();
	}


	/********************************************************************
	 * Determine whether the curl utility is installed on the system
	 * and set a local boolean reflecting that question.
     ***********************************************************************/
	//    m_bCurlPresent = check_curl_installed();

	/********************************************************************
	 * Determine the name of the primary network interface in use and
	 * save it in the shared segment.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIface))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szIface");
		get_interface(false);
	}

	/********************************************************************
	 * Determine the hostname of the system on which this software is running.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szHostname))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szHostname");
		set_hostname(false);
	}

	/********************************************************************
	 * Determine the protocol supported by Apache2 on the current system and
	 * save to the shared system. It would be https:// or http://
     ***********************************************************************/
	if (0 == strcmp("http://", gpSh->m_pShMemng->szProtocol) ||
		0 == strcmp("https://", gpSh->m_pShMemng->szProtocol))
	{
		//m_pSysLog->loginfo("environment::environment: valid szProtocol already set");
	}
	else
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szProtocol");
		set_protocol(false);
	}


	/********************************************************************
	 * Determine the script name
	 */
	get_scriptname();

	/********************************************************************
	 * Determine the local IPv4 number of the host system and save in the
	 * shared memory segment. The parameter is a boolean indicating whether
	 * debug information should be generated.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIP))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szIP");
		get_ip(false);
	}

	/********************************************************************
	 * Determine the publically visible IPv4 number of the host system
	 * and save in the shared segment.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szPublicIP))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szPublicIP");
		set_public_ip();
	}

	/********************************************************************
	 * Create the base URL for calling our CGIs
	 * for instance: "http://172.20.10.4/cgi-bin/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szCgiRoot))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szCgiRoot");
		set_cgi_root(false);
	}

	/********************************************************************
	 * Create the base URL for accessing images
	 * for instance: "http://172.20.10.4/~doug/fw/images/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szImgRoot))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szImgRoot");
		set_img_root(false);
	}

	/********************************************************************
	 * Create the base URL for accessing styles
	 * for instance: "http://172.20.10.4/~doug/fw/styles/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szStylesRoot))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szStylesRoot");
		set_styles_root(false);
	}

	/********************************************************************
	 * Create the base filesystem root for filesystem access to styles
	 * for instance: "/home/monk/public_html/fw/styles/"
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szStylesFileRoot))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szStylesFileRoot");
		set_styles_file_root(false);
	}

	// /********************************************************************
	//  * Create the base path for accessing Journal files
	//  * for instance: "/home/devo/Documents/Fw_Notes/"
 //     ***********************************************************************/
	// if (0 == strlen(gpSh->m_pShMemng->szJournalRoot))
	// {
	// 	//m_pSysLog->loginfo("environment::environment: Extracting szJournalRoot");
	// 	set_journal_root(false);
	// }

	/********************************************************************
	 * Create the base path for temp files
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szTmpRoot))
	{
		//m_pSysLog->loginfo("environment::environment: Extracting szTmpRoot");
		set_tmp_root(false);
	}
}


/*****************************************************************************
 * @brief Extracts the username from the current file path.
 *
 * This method retrieves the username by parsing the file path stored in the
 * macro `__FILE__`. It trims the first 6 characters from the file path,
 * extracts the substring up to the first '/' character, and updates the shared
 * memory `szUser` with the result. The extracted username is then returned
 * as a string.
 *
 * @return The extracted username as a std::string.
 ****************************************************************************/
std::string environment::extract_username()
{
	std::string ssTemp = __FILE__;
	ssTemp = ssTemp.substr(6, ssTemp.length());
	int offset = ssTemp.find('/');
	ssTemp = ssTemp.substr(0, offset);
	strcpy(gpSh->m_pShMemng->szUser, ssTemp.c_str());
	return ssTemp;
}


/**
 * @brief Constructs the home directory path for the current user.
 *
 * This function creates a home directory path string by appending the user's name,
 * held in shared memory, to a predefined base directory path. The constructed path
 * is stored in shared memory and also returned as a `std::string`.
 *
 * @return A `std::string` containing the constructed home directory path.
 */
std::string environment::construct_szHome()
{
	std::string ssTemp = "/home/";
	ssTemp.append(gpSh->m_pShMemng->szUser);
	ssTemp.append("/");
	strcpy(gpSh->m_pShMemng->szHome, ssTemp.c_str());
	return ssTemp;
}

std::string environment::construct_szUserFQDS()
{
	std::string ssUserFQDS = gpSh->m_pShMemng->szHome;
	ssUserFQDS.append("public_html/");
	strcpy(gpSh->m_pShMemng->szUserFQDS, ssUserFQDS.c_str());
	return ssUserFQDS;
}

std::string environment::construct_szSourceFQDS()
{
	std::string ssSourceFQDS = gpSh->m_pShMemng->szUserFQDS;
	ssSourceFQDS.append("fw/");
	strcpy(gpSh->m_pShMemng->szSourceFQDS, ssSourceFQDS.c_str());
	return ssSourceFQDS;
}

std::string environment::construct_szLogFQDS()
{
	std::string ssLogFQDS = gpSh->m_pShMemng->szSourceFQDS;
	ssLogFQDS.append("log/");
	strcpy(gpSh->m_pShMemng->szLogFQDS, ssLogFQDS.c_str());
	return ssLogFQDS;
}

/***************************************************************************
 * @brief Configures and sets the root directory for user-specific settings.
 * This function constructs the configuration root path for a user by
 * appending the username and predefined directory structure to the base
 * path "/home/". The resulting path is stored in a shared memory structure
 * to be utilized by other components of the system for user-specific
 * configurations.
 * @note The function relies on shared memory to fetch user information
 *       and to store the constructed configuration path.
 ***************************************************************************/
void environment::construct_szConfigFQDS()
{
	std::string ssConfigFQDS = gpSh->m_pShMemng->szHome;
	ssConfigFQDS.append(".config/multiware/");
	strcpy(gpSh->m_pShMemng->szConfigFQDS, ssConfigFQDS.c_str());
}

void environment::construct_szConfigFQFS()
{
	std::string ssConfigFQFS = gpSh->m_pShMemng->szConfigFQDS;
	ssConfigFQFS.append("config.ini");
	strcpy(gpSh->m_pShMemng->szConfigFQFS, ssConfigFQFS.c_str());
}


/**
 * Sets the startup script for the VPAD (Virtual PAD) system.
 *
 * This function initializes the VPAD with the specified startup script,
 * allowing for configuration or setup tasks to be executed during the system's startup process.
 * The provided script should contain the necessary commands in a format
 * understood by the VPAD system.
 *
 * @param script A string containing the startup script to be executed by the VPAD.
 *               The script must be properly formatted and valid for the VPAD system.
 * @return A boolean value indicating the success or failure of setting the startup script.
 *         Returns true if the script was set successfully, or false if an error occurred.
 */
void environment::set_vpad_startup_script()
{
	char szTempFQFS[] = {"/home/%s/public_html/fw/scripts/start-vpad.sh"};
	char szFileFQFS[FILENAME_MAX];
	char szCommand[80];

	sprintf(szFileFQFS, szTempFQFS, gpSh->m_pShMemng->szUser);
	FILE* fp = fopen(szFileFQFS, "w");
	fprintf(fp, "#!/bin/sh\n");
	fprintf(fp, "/home/%s/public_html/fw/scripts/start-vpad.sh &\n",
	        gpSh->m_pShMemng->szUser);
	fclose(fp);
	sprintf(szCommand, "chmod +x %s", szFileFQFS);
	system(szCommand);
}

/**
 * @brief Sets or updates the public IP address of a resource or component.
 *
 * This function configures the public-facing IP address for the entity
 * it is applied to. It typically modifies a given object's network
 * configuration or handles the assignment of a public IP.
 *
 * @param ip_address The new public IP address to be assigned.
 *                   It must be a valid IPv4 or IPv6 address.
 * @return void
 *
 * @throws std::invalid_argument if the provided ip_address is invalid.
 * @throws std::runtime_error if the operation fails due to external factors,
 * such as conflicts with existing network configurations or resource limitations.
 *
 * @note Ensure that the IP address provided is not already in use or
 * conflicts with existing allocations.
 */
void environment::set_public_ip()
{
	char szPublicIP[IPV4_ADDR_SIZE_MAX];
	char szTempFQFS[FILENAME_MAX];
	char szCommand[FILENAME_MAX];
	std::string ssMyIp;

	// s/b: /home/devo/public_html/fw/tmp/myv4ip.txt
	strcpy(szTempFQFS,
	       gpOS->genTempFQFS("myv4ip.txt", false).c_str());

	sprintf(szCommand, "curl ip.me >%s 2> /dev/null", szTempFQFS);
	system(szCommand);
	std::ifstream ifs(szTempFQFS);
	ifs >> ssMyIp;
	strcpy(szPublicIP, ssMyIp.c_str());
	strcpy(gpSh->m_pShMemng->szPublicIP, szPublicIP);
}

/**
 * Standard getter for the public IP address of the host.
 *
 * This function attempts to determine the public IP address of the machine
 * by making a network request to a third-party service or API that can
 * return the externally visible IP. The returned IP address is typically in
 * IPv4 format.
 *
 * @return A string containing the public IP address if successfully retrieved,
 *         or an empty string if the operation fails.
 *
 * @throws std::runtime_error If the network request to retrieve the public
 *         IP address encounters an error or the service is unavailable.
 */
char* environment::get_public_ip()
{
	return gpSh->m_pShMemng->szPublicIP;
}


/**
 * @brief Checks if cURL is installed and available on the system.
 *
 * This function verifies the availability of the cURL command-line tool
 * by executing a simple command to determine if cURL is installed.
 * It is often used in scripts or applications to ensure that dependencies
 * are met before proceeding with operations that require cURL.
 *
 * @return True if cURL is installed, false otherwise.
 */
bool environment::check_curl_installed()
{
	char szTemp[128];
	bool bRetVar;

	m_bCurlPresent = false;

	std::string ssCurlStdout = gpOS->genTempFQFS("curl.stdout", false);
	std::string ssCurlStderr = gpOS->genTempFQFS("curl.stderr", false);
	sprintf(szTemp, "curl --version >%s 2>%s",
	        ssCurlStdout.c_str(), ssCurlStderr.c_str());

	int retval = system(szTemp);
	if (0 == retval)
	{
		FILE* fd = fopen(ssCurlStdout.c_str(), "r");
		char szCurlVersion[BUFSIZ];
		fgets(szCurlVersion, sizeof(szCurlVersion), fd);
		strcpy(m_szCurlVersion, szCurlVersion);
		bRetVar = true;
	}
	else
	{
		bRetVar = false;
	}
	return bRetVar;
}


/**
 * Retrieves the root directory path for CGI (Common Gateway Interface) scripts.
 *
 * This function is commonly used in server configurations to determine the
 * base directory where CGI scripts are located. The returned path may be used
 * for executing scripts, setting up routing, or managing access permissions.
 *
 * @return A string representing the absolute or relative path to the CGI root
 * directory. The format or value of the string might depend on the server
 * configuration or environment settings.
 */
std::string environment::get_cgi_root(bool bDebug)
{
	std::string ssCgiRoot = gpSh->m_pShMemng->szCgiRoot;
	return ssCgiRoot;
}

/**
 * Retrieves the CGI root as a null-terminated string (C-style string).
 *
 * This function is used to obtain the root directory configured for
 * Common Gateway Interface (CGI) scripts. The returned string represents
 * the directory path where CGI scripts are stored or executed from.
 *
 * @return A constant character pointer representing the CGI root directory.
 *         The caller should ensure that this pointer is used in a read-only
 *         manner and does not attempt to modify or free the memory it points to.
 */
char* environment::get_cgi_root_as_sz(bool bDebug)
{
	return gpSh->m_pShMemng->szCgiRoot;
}

/**
 * @brief Sets the directory path for the CGI (Common Gateway Interface) root.
 *
 * This function allows configuring the base directory used for executing CGI scripts.
 * It is typically used in web server setups where dynamic content is provided
 * through CGI programs. The path provided will be used to locate the CGI binaries
 * or scripts relative to the server's working directory.
 *
 * @param path A string specifying the path to the CGI root directory.
 *             It should be a valid directory path accessible to the server.
 */
void environment::set_cgi_root(bool bDebug)
{
	std::string ssCgiRoot = gpSh->m_pShMemng->szProtocol;
	ssCgiRoot.append(gpSh->m_pShMemng->szIP);
	ssCgiRoot.append("/~");
	ssCgiRoot.append(gpSh->m_pShMemng->szUser);
	ssCgiRoot.append("/fw/cgi-bin/");
	strcpy(gpSh->m_pShMemng->szCgiRoot, ssCgiRoot.c_str());
}

/**
 * @brief Retrieves the version information for the installed cURL library.
 *
 * This function returns a string containing the version of cURL
 * that is currently installed and available on the system.
 * It may include version number, release date, and additional information
 * related to the cURL build and environment.
 *
 * @return const char* A string representing the cURL version information.
 */
char* environment::get_curl_version()
{
	return m_szCurlVersion;
}


/**
 * Retrieves the hostname of the current machine.
 *
 * This function attempts to obtain the name of the host machine using
 * system-provided methods. The hostname is typically used for network
 * identification and can be useful in various networking and system
 * configuration contexts.
 *
 * @return A standard string containing the hostname of the current machine.
 *         If the hostname cannot be retrieved, an empty string or an
 *         appropriate error may be returned based on implementation.
 *
 * @throws std::runtime_error If the system fails to fetch the hostname
 *         due to unavailable resources or restricted permissions.
 */
std::string environment::get_hostname(bool bDebug)
{
	std::string ssEtcHostnameFQFS = "/etc/hostname";
	std::ifstream ifs(ssEtcHostnameFQFS);
	std::string ssInbuf;
	ifs >> ssInbuf;
	return ssInbuf;
}

/**
 * Sets the hostname of the system or device.
 *
 * This function updates the system's hostname in the shared region.
 */
void environment::set_hostname(bool bDebug)
{
	std::string ssEtcHostnameFQFS = "/etc/hostname";
	std::ifstream ifs(ssEtcHostnameFQFS);
	std::string ssInbuf;
	ifs >> ssInbuf;
	strcpy(gpSh->m_pShMemng->szHostname, ssInbuf.c_str());
}


/**
 * This is a standard getter for the image root.
 *
 * This function returns the root directory used for accessing,
 * storing, or retrieving image files. The path returned by this
 * function typically serves as the base directory for performing
 * operations related to image file management.
 *
 * @return A string representing the path to the image root directory.
 */
std::string environment::get_img_root(bool bDebug)
{
	std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
	return ssImgRoot;
}

/**
 * Determines the root directory for image storage or retrieval
 * and updates the shared region string.
 *
 * @param bDebug A boolean controlling debug output.
 */
void environment::set_img_root(bool bDebug)
{
	std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
	ssImgRoot.append(gpSh->m_pShMemng->szIP);
	ssImgRoot.append("/~");
	ssImgRoot.append(gpSh->m_pShMemng->szUser);
	ssImgRoot.append("/fw/images/");
	strcpy(gpSh->m_pShMemng->szImgRoot, ssImgRoot.c_str());
}

/**
 * @brief Retrieves the root directory path for styles.
 *
 * This function is used to fetch the base directory where style-related files
 * are stored. This is commonly used to resolve paths for styles and themes in
 * an application.
 *
 * @return A string representing the root directory path for styles.
 */
std::string environment::get_styles_root(bool bDebug)
{
	std::string ssStylesRoot = gpSh->m_pShMemng->szStylesRoot;
	return ssStylesRoot;
}

/**
 * Sets the root path for style files used within the application.
 *
 * This function updates the root directory where the application's style files
 * are located. The specified path is used as a base for resolving style-related
 * resources. It is the caller's responsibility to ensure that the path is valid
 * and accessible.
 *
 * @param path A string representing the root path for style files.
 *
 * @note Ensure that the provided path is properly formatted and accessible
 *       to prevent any resource loading issues in the application.
 */
void environment::set_styles_root(bool bDebug)
{
	std::string ssStylesRoot = gpSh->m_pShMemng->szProtocol;
	ssStylesRoot.append(gpSh->m_pShMemng->szIP);
	ssStylesRoot.append("/~");
	ssStylesRoot.append(gpSh->m_pShMemng->szUser);
	ssStylesRoot.append("/fw/styles/");
	strcpy(gpSh->m_pShMemng->szStylesRoot, ssStylesRoot.c_str());
}

/**
 * Retrieves the root directory for the styles file.
 *
 * This function is typically used to fetch the file path or directory
 * where style or theme-related files are located. It ensures that
 * the application has consistent access to styling resources.
 *
 * @return A string representing the root path of the styles file.
 */
std::string environment::get_styles_file_root(bool bDebug)
{
	std::string ssStylesRoot = gpSh->m_pShMemng->szStylesFileRoot;
	return ssStylesRoot;
}

/**
 * @brief Sets the root directory for the styles file.
 *
 * This function specifies the root path where the styles file is located. It can be used
 * to define a consistent file path for styling resources within an application.
 *
 * @param path The root directory where the styles file resides.
 *
 * @throws FileNotFoundError If the provided path does not exist or is invalid.
 * @throws ValueError If the input path is empty or null.
 */
void environment::set_styles_file_root(bool bDebug)
{
	std::string ssStylesFileRoot = "/home/";
	ssStylesFileRoot.append(gpSh->m_pShMemng->szUser);
	ssStylesFileRoot.append("/public_html/fw/styles/");
	strcpy(gpSh->m_pShMemng->szStylesFileRoot, ssStylesFileRoot.c_str());
}


// /**
//  * @brief Sets the root directory or path for the journal storage.
//  *
//  * This function accepts a path string as input and assigns it as the root
//  * directory where journal files or related data will be stored. It ensures
//  * that the system knows the base directory for managing journal-related
//  * operations.
//  *
//  * @param path A string representing the root directory for the journal.
//  *
//  * @note Ensure that the specified path is accessible and valid for the
//  * application to avoid errors during journal operations.
//  */
// void environment::set_journal_root(bool bDebug)
// {
// 	std::string ssJournalRoot = "/home/";
// 	ssJournalRoot.append(gpSh->m_pShMemng->szUser);
// 	ssJournalRoot.append("/Documents/Fw_Notes/");
// 	strcpy(gpSh->m_pShMemng->szJournalRoot, ssJournalRoot.c_str());
// } /* TODO: access into system call to check whether this dir exists, and to make
// 	 it if not */


/**
 * @brief Sets the temporary root directory path.
 *
 * This function initializes or updates the path used as the temporary
 * root directory for file operations. It ensures that all temporary
 * files or subdirectories are managed under the specified root directory.
 *
 * @param path A string containing the file path to set as the temporary root directory.
 * @throws std::invalid_argument If the provided path is empty or invalid.
 * @throws std::runtime_error If the operation fails due to insufficient permissions
 *         or inability to set the path correctly.
 */
void environment::set_tmp_root(bool bDebug)
{
	std::string ssTmpRoot = "/home/";
	ssTmpRoot.append(gpSh->m_pShMemng->szUser);
	ssTmpRoot.append("/public_html/fw/tmp/");
	strcpy(gpSh->m_pShMemng->szTmpRoot, ssTmpRoot.c_str());
}

/**
 * Retrieves the interface for the given input.
 *
 * This method is commonly used to extract or return a specific interface
 * based on the provided input. The input could be of various types, and
 * the method should determine and return the relevant interface accordingly.
 *
 * @param input An object or parameter from which the interface is to be retrieved.
 * @return The interface associated with the provided input, or null if no interface is found.
 * @throws NullPointerException if the input is null and the method does not handle that case.
 * @throws IllegalArgumentException if the input type is invalid or unsupported.
 */
std::string environment::get_interface(bool bDebug)
{
	std::string ssUser = gpSh->m_pShMemng->szUser;
	gpXinetd->trigger(VPA_NETSTAT_PORT);

	char szNetstatStdoutFQFS[128];
	strcpy(szNetstatStdoutFQFS,
	       ("/home/"
		       + ssUser
		       + "/public_html/fw/tmp/netstat.stdout").c_str());

	gpSysLog->loginfo(szNetstatStdoutFQFS);
	sleep(2);
	gpSysLog->loginfo(szNetstatStdoutFQFS);

	char szBuffer[BUFSIZ];
	std::ifstream ifs(szNetstatStdoutFQFS);
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;
	ifs >> szBuffer;

	strncpy(m_szIface, szBuffer, IFNAMSIZ);
	strncpy(gpSh->m_pShMemng->szIface, m_szIface, IFNAMSIZ);
	std::string ssRetVal = m_szIface;

	sprintf(szBuffer, "%s::%s#%d: szIface is %s",
	        __FILE__, __FUNCTION__,__LINE__, gpSh->m_pShMemng->szIface);


	return ssRetVal;
}


/**
 * @brief Retrieves the IP address of the local machine.
 *
 * This function fetches the IP address of the machine it is executed on. It typically
 * uses network interfaces or system APIs to determine the primary IP address.
 *
 * @return A string containing the IP address in standard IPv4 or IPv6 format.
 *         Returns an empty string if the IP address could not be determined.
 *
 * @throws std::runtime_error If an issue occurs while retrieving the IP address.
 */
std::string environment::get_ip(bool bDebug)
{
	// define a buffer for reading lines from the
	// /tmp/ip.out file.
	char szBuffer[BUFSIZ];
	std::string ssUser = gpSh->m_pShMemng->szUser;
	gpSysLog->loginfo(ssUser.c_str());

	std::ofstream ofs("/home/"
	                  + ssUser
	                  + "/public_html/fw/scripts/inetd-ip-redirect.sh",
	                  std::ios::out);

	ofs << "#!/bin/bash" << std::endl;
	ofs << "###############################################################"
		"##############################" << std::endl;
	ofs << "# daphne.goodall.com:/home/devo/public_html/fw/scripts/inetd-ip"
		"-redirect.sh 2025-02-17      #" << std::endl;
	ofs << "# ";
	ofs << RCOPR;
	ofs << 	"                                  #" << std::endl;
	ofs << "###############################################################"
		"##############################" << std::endl;
	ofs << "ip addr show "
		<< m_szIface
		<< " > /home/devo/public_html/fw/tmp/ip.stdout" << std::endl;

	ofs.close();
	system(("chmod +x /home/"
		+ ssUser
		+ "/public_html/fw/scripts/inetd-ip-redirect.sh").c_str());
	gpXinetd->trigger(VPA_IP_PORT);
	sleep(1);
	// Open the read for input
	FILE* ipfd = fopen(("/home/"
		                   + ssUser
		                   + "/public_html/fw/tmp/ip.stdout").c_str(),
	                   "r");
	// define a buffer to hold our interface
	// name with a postpended colon.
	char szIfaceColon[BUFSIZ];

	// copy in the interfdace name  found previously
	strncpy(szIfaceColon, m_szIface, BUFSIZ);

	// append the colon
	strcat(szIfaceColon, ":");

	// convert the interface name with colon to a standard string
	std::string ssIfaceColon = szIfaceColon;

	// read a line from the file into a zero terminated string
	fgets(szBuffer, sizeof(szBuffer), ipfd);
	gpSysLog->loginfo(szBuffer);
	// convcert the zero terminated string to a standard string
	std::string ssBuffer = szBuffer;

	// while waiting to see the string with our interface in it...
	while (std::string::npos == ssBuffer.find(ssIfaceColon))
	{
		// get another line
		fgets(szBuffer, sizeof(szBuffer), ipfd);
		gpSysLog->loginfo(szBuffer);

		// convert to a std::string
		ssBuffer = szBuffer;
	} // rinse and repeat...

	// scan for the line with the inet address in it
	fgets(szBuffer, sizeof(szBuffer), ipfd);
	while (0 != strncmp("inet", &szBuffer[4], 4))
	{
		fgets(szBuffer, sizeof(szBuffer), ipfd);
	}

	// clear the result string to all zeroes
	memset(m_szIP, 0, sizeof(m_szIP));

	int index = 9; // offset of IP address in line (fixed)
	int destindex = 0; // starting offset in the destn string

	// copy until we find a slash
	while (szBuffer[index] != '/')
	{
		m_szIP[destindex++] = szBuffer[index++];
	}

	strncpy(gpSh->m_pShMemng->szIP, m_szIP, DNS_FQDN_SIZE_MAX);

	// convert the zero terminated IP to std::string
	std::string ssRetVal = gpSh->m_pShMemng->szIP;
	gpSysLog->loginfo(m_szIP);
	// return the std::string  version of the IP number
	return ssRetVal;
}


/**
 * @brief Logs and outputs an error message, including file and line details.
 *
 * This function formats an error message for debugging or logging purposes.
 * It includes the error description, the file where the error occurred,
 * the function name, and the line number to provide detailed context about the error.
 *
 * @param pszErrMsg The error message to be formatted and displayed.
 * @param iLineNumber The line number where the error occurred.
 */
void local_process_error(const char* pszErrMsg, int iLineNumber)
{
	char szTemp[128];
	sprintf(szTemp, "%s in %s::%s line #%d",
	        pszErrMsg,__FILE__, "main()", iLineNumber);
	std::cout << szTemp << std::endl;
}

/**
 * @brief Determines and sets the appropriate protocol (HTTP or HTTPS) for
 *			the environment.
 *
 * This method attempts to configure either HTTPS or HTTP as the
 * communication protocol based on the availability of their
 * respective descriptors (e.g., files or output streams).
 * It utilizes temporary files and checks their sizes to determine
 * if each protocol is operational and sets the protocol accordingly.
 * If neither protocol can be set, the method terminates execution
 * with an error.
 *
 * @param bDebug Indicates whether debug mode is enabled, which could
 * influence internal operations.
 */
void environment::set_protocol(bool bDebug)
{
	gpXinetd->trigger(VPA_HTTPS_PORT);
	sleep(1);

	std::string ssHttpsFQFS = gpOS->genTempFQFS("https.stdout", false);
	FILE* fpHttps = fopen(ssHttpsFQFS.c_str(), "r");
	if (nullptr == fpHttps)
	{
		local_process_error("fopen failed",__LINE__);
		exit(EXIT_FAILURE);
	}

	int iFseekRetcode = fseek(fpHttps, 0,SEEK_END);
	if (-1 == iFseekRetcode)
	{
		char szFseek[80];
		sprintf(szFseek, "fseek failed (errno=%d)",errno);
		local_process_error(szFseek,__LINE__ - 5);
		exit(EXIT_FAILURE);
	}

	long l_fSize = ftell(fpHttps);
	if (-1 == l_fSize)
	{
		char szFtell[80];
		sprintf(szFtell, "ftell failed (errno=%d)",errno);
		local_process_error(szFtell,__LINE__ - 3);
		exit(EXIT_FAILURE);
	}

	if (0l != l_fSize)
	{
		strcpy(gpSh->m_pShMemng->szProtocol, "https://");
	}
	else
	{
		gpXinetd->trigger(VPA_HTTP_PORT);
		sleep(1);

		std::string ssHttpsFQFS = gpOS->genTempFQFS("http.stdout", false);
		FILE* fpHttp = fopen(ssHttpsFQFS.c_str(), "r");
		if (nullptr == fpHttp)
		{
			local_process_error("fopen failed",__LINE__);
			exit(EXIT_FAILURE);
		}

		int iFseekRetcode = fseek(fpHttp, 0,SEEK_END);
		if (-1 == iFseekRetcode)
		{
			char szFseek[80];
			sprintf(szFseek, "fseek failed (errno=%d)",errno);
			local_process_error(szFseek,__LINE__ - 5);
			exit(EXIT_FAILURE);
		}

		long l_fSize = ftell(fpHttp);
		if (-1 == l_fSize)
		{
			char szFtell[80];
			sprintf(szFtell, "ftell failed (errno=%d)",errno);
			local_process_error(szFtell,__LINE__ - 3);
			exit(EXIT_FAILURE);
		}

		if (0l != l_fSize)
		{
			strcpy(gpSh->m_pShMemng->szProtocol, "http://");
		}
		else
		{
			local_process_error("Unable to determine protocol",__LINE__);
			exit(EXIT_FAILURE);
		}
	}
}


/**
 * Retrieves the current log name used by the system.
 *
 * @return A constant character pointer representing the log name.
 */
char* environment::get_szLogname()
{
	return m_szLogname;
}

/**
 * @brief Retrieves the system-specific log name.
 *
 * This function is responsible for returning the log name used
 * to identify system-specific logs. It is typically used in
 * scenarios where logs need to be categorized or distinguished
 * according to a system-specific identifier.
 *
 * @return A string representing the system-specific log name.
 */
std::string environment::get_ssLogname()
{
	return m_ssLogname;
}

/**
 * @brief Retrieves the name of the currently executing script or program.
 *
 * This function is typically used to obtain the filename of the script or program
 * being executed. It may parse the command-line arguments or utilize system calls
 * to determine the script name.
 *
 * @return A string representing the name of the current script.
 */
char* environment::get_scriptname()
{
	return m_pszScriptName;
}


/**
 * Checks if the cURL library is available and can be used.
 *
 * This method verifies if the cURL library is present on the system
 * and properly initialized. It is typically used to ensure that
 * HTTP requests can be performed using cURL.
 *
 * @return True if the cURL library is available; otherwise, false.
 */
bool environment::is_curl_present()
{
	return m_bCurlPresent;
}


/**
 * @brief Checks if the netstat utility is present on the system.
 *
 * This method verifies the presence of the netstat executable
 * at its expected location in the filesystem.
 *
 * @return True if the netstat utility is found, otherwise false.
 */
bool environment::is_netstat_present()
{
	std::string ssFQFS = "/usr/bin/netstat";
	if (0 == access(ssFQFS.c_str(),F_OK))
	{
		return true;
	}
	else
	{
		return false;
	};
}


///////////////////////////
// eof - environment.cpp //
///////////////////////////
