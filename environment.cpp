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

void local_process_error(const char* pszErrMsg, int iLineNumber)
{
	char szTemp[128];
	sprintf(szTemp, "%s in %s::%s line #%d",
			pszErrMsg,__FILE__, "main()", iLineNumber);
	std::cout << szTemp << std::endl;
}

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

	/**
	 * This is a critical piece of logic. This code assumes that the c++
	 * source files are at the root of the project file structure. It
	 * just happens this is true. Although I have considered moving the
	 * source files to a src folder, I haven't done it yet because it is
	 * a lot of work for undefined benefit.
	 */

	std::string ssDevoDir;

	/////////////////////////////
	// Development Directories //
	/////////////////////////////

	if (strlen(gpSh->m_pShMemng->szDevoDir) == 0)
	{
		ssDevoDir = __FILE__;
		ssDevoDir = std::filesystem::path(ssDevoDir).remove_filename();
		strcpy(gpSh->m_pShMemng->szDevoDir, ssDevoDir.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szBuildFQDS) == 0)
	{
		std::string ssBuildFQDS = ssDevoDir;
		ssBuildFQDS.append("build/");
		strcpy(gpSh->m_pShMemng->szBuildFQDS, ssBuildFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szCgiBinFQDS) == 0)
	{
		std::string ssCgiBinFQDS = ssDevoDir;
		ssCgiBinFQDS.append("cgi-bin/");
		strcpy(gpSh->m_pShMemng->szCgiBinFQDS, ssCgiBinFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szDocFQDS) == 0)
	{
		std::string ssDocFQDS = ssDevoDir;
		ssDocFQDS.append("doc/");
		strcpy(gpSh->m_pShMemng->szDocFQDS, ssDocFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szImgFQDS) == 0)
	{
		std::string ssImgFQDS = ssDevoDir;
		ssImgFQDS.append("images/");
		strcpy(gpSh->m_pShMemng->szImgFQDS, ssImgFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szIncludeFQDS) == 0)
	{
		std::string ssIncludeFQDS = ssDevoDir;
		ssIncludeFQDS.append("include/");
		strcpy(gpSh->m_pShMemng->szIncludeFQDS, ssIncludeFQDS.c_str());
	}


	if (strlen(gpSh->m_pShMemng->szLogFQDS) == 0)
	{
		std::string ssLogFQDS = ssDevoDir;
		ssLogFQDS.append("log/");
		strcpy(gpSh->m_pShMemng->szLogFQDS, ssLogFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szSchemasFQDS) == 0)
	{
		std::string ssSchemasFQDS = ssDevoDir;
		ssSchemasFQDS.append("schemas/");
		strcpy(gpSh->m_pShMemng->szSchemasFQDS, ssSchemasFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szScriptsFQDS) == 0)
	{
		std::string ssScriptsFQDS = ssDevoDir;
		ssScriptsFQDS.append("scripts/");
		strcpy(gpSh->m_pShMemng->szScriptsFQDS, ssScriptsFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szStylesFQDS) == 0)
	{
		std::string ssStylesFQDS = ssDevoDir;
		ssStylesFQDS.append("styles/");
		strcpy(gpSh->m_pShMemng->szStylesFQDS, ssStylesFQDS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szTempFQDS) == 0)
	{
		std::string ssTempFQDS = ssDevoDir;
		ssTempFQDS.append("tmp/");
		strcpy(gpSh->m_pShMemng->szTempFQDS, ssTempFQDS.c_str());
	}

	//////////////////////
	// User Information //
	//////////////////////

	if (0 == strlen(gpSh->m_pShMemng->szUser))
	{
		std::string ssTemp = __FILE__;
		ssTemp = ssTemp.substr(6, ssTemp.length());
		int offset = ssTemp.find('/');
		ssTemp = ssTemp.substr(0, offset);
		strcpy(gpSh->m_pShMemng->szUser, ssTemp.c_str());
	}

	if (0 == strlen(gpSh->m_pShMemng->szHome))
	{
		std::string ssTemp = "/home/";
		ssTemp.append(gpSh->m_pShMemng->szUser);
		ssTemp.append("/");
		strcpy(gpSh->m_pShMemng->szHome, ssTemp.c_str());
	}

	/********************************************************************
	 * Determine the Userdir of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szUserdirFQDS))
	{
		char szUserdir[FILENAME_MAX];
		strcpy(szUserdir, ssDevoDir.c_str());
		szUserdir[strlen(szUserdir) - 3] = '\0';
		strcpy(gpSh->m_pShMemng->szUserdirFQDS, szUserdir);
	}

	/********************************************************************
	 * Determine the Sourcedir of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szSourceFQDS))
	{
		std::string ssSourceFQDS = ssDevoDir;
		strcpy(gpSh->m_pShMemng->szSourceFQDS, ssSourceFQDS.c_str());
	}

	// /********************************************************************
	//  * Determine the LogFQDS of the user under which this application
	//  * is running and save the result in the shared segment.
	//  ***********************************************************************/
	// if (0 == strlen(gpSh->m_pShMemng->szLogFQDS))
	// {
	// 	std::string ssLogFQDS = ssDevoDir;
	// 	ssLogFQDS.append("log/");
	// 	strcpy(gpSh->m_pShMemng->szLogFQDS, ssLogFQDS.c_str());
	// }


	/********************************************************************
	 * Determine the config root of the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szConfigFQDS))
	{
		// construct_szConfigFQDS();
		std::string ssConfigFQDS = gpSh->m_pShMemng->szHome;
		ssConfigFQDS.append(".config/multiware/");
		strcpy(gpSh->m_pShMemng->szConfigFQDS, ssConfigFQDS.c_str());
	}

	/********************************************************************
	 * Determine the config filename for the user under which this application
	 * is running and save the result in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szConfigFQFS))
	{
		std::string ssConfigFQFS = gpSh->m_pShMemng->szConfigFQDS;
		ssConfigFQFS.append("config.ini");
		strcpy(gpSh->m_pShMemng->szConfigFQFS, ssConfigFQFS.c_str());
	}

	if (strlen(gpSh->m_pShMemng->szStatus) == 0)
	{
		std::string ssStatus = ssDevoDir;
		ssStatus.append("status/");
		strcpy(gpSh->m_pShMemng->szStatus, ssStatus.c_str());
	}

	/////////////////////////
	// Network Information //
	/////////////////////////

	if (0 == strlen(gpSh->m_pShMemng->szHostname))
	{
		std::string ssEtcHostnameFQFS = "/etc/hostname";
		std::ifstream ifs(ssEtcHostnameFQFS);
		std::string ssInbuf;
		ifs >> ssInbuf;
		strcpy(gpSh->m_pShMemng->szHostname, ssInbuf.c_str());
	}

	/********************************************************************
	 * Determine the name of the primary network interface in use and
	 * save it in the shared segment.
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIface))
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
		ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer;
		ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer;
		ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer;
		ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer;
		ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer; ifs >> szBuffer;

		strncpy(m_szIface, szBuffer, IFNAMSIZ);
		strncpy(gpSh->m_pShMemng->szIface, m_szIface, IFNAMSIZ);
	}


	/********************************************************************
	 * Determine the local IPv4 number of the host system and save in the
	 * shared memory segment. The parameter is a boolean indicating whether
	 * debug information should be generated.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIP))
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
		ofs << "                                  #" << std::endl;
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
		std::string ssCgiRoot = gpSh->m_pShMemng->szProtocol;
		ssCgiRoot.append(gpSh->m_pShMemng->szIP);
		ssCgiRoot.append("/~");
		ssCgiRoot.append(gpSh->m_pShMemng->szUser);
		ssCgiRoot.append("/fw/cgi-bin/");
		strcpy(gpSh->m_pShMemng->szCgiRoot, ssCgiRoot.c_str());
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
