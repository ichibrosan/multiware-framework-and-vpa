/////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/environment.cpp 2025/01/10 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.      //
/////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"
#include "shared.h"

#define GET_HOSTNAME_AND_PROTOCOL
#define GET_INTERFACE
#define GET_IP
#define GET_ROOTS
#define GET_REMOTE_USER

/***********************************************************************
 * @brief Global variable to store the username.
 *
 * gszUser is a character array with a fixed length of 32, used to store
 * the username in the program. It is defined as a global variable
 * to enable accessibility across multiple parts of the codebase.
 *
 * Note: The length of 32 includes space for the null-terminator.
 ***********************************************************************/
char gszUser[32];


/***********************************************************************
 * @brief Represents the GSS (Generic Security Service) username.
 *
 * This variable stores the username associated with the
 * GSS authentication mechanism. It is typically used in
 * secure communication protocols to identify the user
 * within a GSS-enabled session or environment.
 *
 * This variable is defined globally and intended for use
 * in scenarios where the GSS context relies on a
 * centralized username value.
 ***********************************************************************/
std::string gssUser;


/*******************************************************************
 * Constructor for the environment class. Initializes various system
 * properties and resources including logging, user information,
 * network details, and server roots.
 *
 * @return An initialized instance of the environment class with all
 *			required resources and configurations set up.
 *******************************************************************/
environment::environment() {
	here;
  char szTemp[128];

	/********************************************************************
	 * Enable syslog logging within thew scope of the environment class
	 * by instantiating the CSysLog class via a pointer in member data.
     ***********************************************************************/
    m_pSysLog = new CSysLog();
	here;

	/********************************************************************
	 * Determine the username under which this application is running
	 * and save the result in the shared segment.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szUser)) {
		m_pSysLog->loginfo("environment::environment: Extracting szUser");
		extract_username();
	}
	here;

	/********************************************************************
	 * Determine whether the curl utility is installed on the system
	 * and set a local boolean reflecting that question.
     ***********************************************************************/
    m_bCurlPresent = check_curl_installed();
	here;

	/********************************************************************
	 * Determine the name of the primary network interface in use and
	 * save it in the shared segment.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIface)) {
		m_pSysLog->loginfo("environment::environment: Extracting szIface");
		get_interface(false);
	}
	here;

	/********************************************************************
	 * Determine the hostname of the system on which this software is running.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szHostname)) {
		m_pSysLog->loginfo("environment::environment: Extracting szHostname");
		set_hostname(false);
	}
	here;

	/********************************************************************
	 * Determine the protocol supported by Apache2 on the current system and
	 * save to the shared system. It would be https:// or http://
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szProtocol)) {
		m_pSysLog->loginfo("environment::environment: Extracting szProtocol");
		set_protocol(false);
	}
	here;

    /********************************************************************
     * Determine the script name
     */
    get_scriptname();
	here;

	/********************************************************************
	 * Determine the local IPv4 number of the host system and save in the
	 * shared memory segment. The parameter is a boolean indicating whether
	 * debug information should be generated.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szIP)) {
		m_pSysLog->loginfo("environment::environment: Extracting szIP");
		get_ip(false);
	}
	here;

	/********************************************************************
	 * Determine the publically visible IPv4 number of the host system
	 * and save in the shared segment.
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szPublicIP)) {
		m_pSysLog->loginfo("environment::environment: Extracting szPublicIP");
		set_public_ip();
	}
	here;

	/********************************************************************
	 * Create the base URL for calling our CGIs
	 * for instance: "http://172.20.10.4/cgi-bin/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szCgiRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szCgiRoot");
		set_cgi_root(false);
	}
	here;

	/********************************************************************
	 * Create the base URL for accessing images
	 * for instance: "http://172.20.10.4/~doug/fw/images/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szImgRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szImgRoot");
		set_img_root(false);
	}
	here;

	/********************************************************************
	 * Create the base URL for accessing styles
	 * for instance: "http://172.20.10.4/~doug/fw/styles/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szStylesRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szStylesRoot");
		set_styles_root(false);
	}
	here;

	/********************************************************************
	 * Create the base filesystem root for filesystem access to styles
	 * for instance: "/home/monk/public_html/fw/styles/"
	 ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szStylesFileRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szStylesFileRoot");
		set_styles_file_root(false);
	}
	here;

	/********************************************************************
	 * Create the base path for accessing Journal files
	 * for instance: "/home/doug/Documents/Fw_Notes/"
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szJournalRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szJournalRoot");
		set_journal_root(false);
	}
	here;

    /********************************************************************
     * Create the base path for temp files
     ***********************************************************************/
	if (0 == strlen(gpSh->m_pShMemng->szTmpRoot)) {
		m_pSysLog->loginfo("environment::environment: Extracting szTmpRoot");
		set_tmp_root(false);
	}
	here;

	/********************************************************************
	 * Create the initialization script that runs the Virtual Protocol Adapter.
	 * The file should generate as:
	 * "/home/$USER/public_html/fw/scripts/start-vpad.sh"
     ***********************************************************************/

	std::string ssStartScriptFQFS = gpOS->genScriptFQFS("start-vpad.sh",false);
	if (0 != access(ssStartScriptFQFS.c_str(),F_OK)) {
		m_pSysLog->loginfo("environment::environment: Generating start-vpad.sh");
		gen_vpad_script();
	}
	here;

}

/***********************************************************************
 * @brief Configures and creates a startup script for the vpad application.
 *
 * The set_vpad_startup_script function dynamically generates a startup script
 * for the vpad application specific to the user. It utilizes a predefined
 * file path template to create the file, writes the necessary script commands,
 * and adjusts file permissions to make it executable.
 *
 * Steps performed by the function:
 * - Constructs the file path using the user's username.
 * - Writes the script content into the file.
 * - Applies executable permissions to the created script.
 *
 * Note: This function assumes the presence of a global structure containing
 * user-related information (gpSh->m_pShMemng->szUser). Proper validation or
 * error handling for file operations is not implemented and should be added
 * to prevent potential failures.
 ***********************************************************************/
void environment::set_vpad_startup_script() {
    char szTempFQFS[] = { "/home/%s/public_html/fw/scripts/start-vpad.sh"};
    char szFileFQFS[FILENAME_MAX];
    char szCommand[80];

    sprintf(szFileFQFS,szTempFQFS,gpSh->m_pShMemng->szUser);
    FILE * fp = fopen(szFileFQFS,"w");
    fprintf(fp,"#!/bin/sh\n");
    fprintf(fp,"/home/%s/public_html/fw/scripts/start-vpad.sh &\n",
               gpSh->m_pShMemng->szUser);
    fclose(fp);
    sprintf(szCommand,"chmod +x %s",szFileFQFS);
    system(szCommand);
}

/***********************************************************************
 * @brief Sets the public IP address of the system.
 *
 * This method retrieves the public IPv4 address of the system by using
 * the external service ip.me. It sends a curl command to fetch the IP
 * address, saves the output to a temporary file, and then reads it into
 * a local string variable. The retrieved public IP address is then
 * stored in a global shared memory structure for use by other parts of
 * the program.
 *
 * Note: This method uses system commands and file I/O operations, which
 * could pose security and reliability concerns in certain environments.
 * TODO: re-write to use xinetd script instead of system
 ***********************************************************************/
void environment::set_public_ip()
{
	char szPublicIP[IPV4_ADDR_SIZE_MAX];
	char szTempFQFS[] = { "/tmp/myv4ip.txt"};
	char szCommand[80];
	std::string ssMyIp;

	sprintf(szCommand,"curl ip.me >%s",szTempFQFS);
	system(szCommand);
	std::ifstream ifs(szTempFQFS);
	ifs >> ssMyIp;
	strcpy(szPublicIP,ssMyIp.c_str());
	strcpy(gpSh->m_pShMemng->szPublicIP,szPublicIP);
}

/********************************************************************
 * Retrieves the public IP address stored in shared memory.
 *
 * @return A pointer to a character array containing the public IP address.
 ***********************************************************************/
char * environment::get_public_ip()
{
	return gpSh->m_pShMemng->szPublicIP;
}

/***********************************************************************
 * @brief Generates a script file for launching the VPAD application.
 *
 * This method creates a shell script located in the user's public_html
 * directory. The script is automatically generated with necessary content
 * to execute the VPAD application. It performs the following steps:
 *
 * - Construct the full file path based on the user's public_html directory.
 * - Attempt to open the script file for writing.
 * - Handle error cases where the file could not be opened by logging
 *   a warning message and exiting the operation.
 * - Write the content of the script if the file is successfully opened,
 *   including a shebang (`#!/bin/sh`) and commands to launch VPAD.
 * - Change the permissions of the generated script to make it executable.
 *
 * Note: The `szUser` is retrieved from the shared memory to build the
 *       file path dynamically based on the specific user's environment.
 ***********************************************************************/
 void environment::gen_vpad_script()
{
	/**
	 *	Generates the FQFS for the script location.
	 *
	 */

	std::string ssVpadLauncher = "/home/";
	ssVpadLauncher.append(gpSh->m_pShMemng->szUser);
	ssVpadLauncher.append("/public_html/fw/scripts/x.sh");

	/**
	 *	Attempts to load the file and checks whether or not it actually did
	 *	get loaded.
	 *
	 */

	FILE * fp = fopen(ssVpadLauncher.c_str(),"w");
	if (nullptr == fp)
	{
		/**
		 *	If it did not get loaded, we print to the standard output and
		 *	close the file.
		 *
		 */

		std::cout << "can't open file" << ssVpadLauncher
				  << "and couldn't create initialization script"
				  << std::endl;
		fclose(fp);
	}
	else
	{
		/**
		 *	If it did get loaded, we write out the script contents to the
		 *	file and then close it.
		 *
		 */

		fprintf(fp,"#!/bin/sh\n");
		fprintf(fp,"###############################################################"
						 "##############################\n");
		fprintf(fp,"# daphne.goodall.com:/home/doug/public_html/fw/scripts/inetd-ne"
						 "tstat-redirect.sh 2025-02-17 #\n");
		fprintf(fp,"# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.""                             #\n");
		fprintf(fp,"###############################################################"
						 "##############################\n");

	    fprintf(fp,"# Automatically generated, Do Not Edit!!\n");
	    fprintf(fp,"/home/%s/public_html/fw/cmake-build-debug/vpad &\n",
	        gpSh->m_pShMemng->szUser);
		fclose(fp);
	}

    // 2025-02-11 11:25 dwg - assure +x
    char szCommand[128];
    sprintf(szCommand,"chmod +x %s",ssVpadLauncher.c_str());
    system(szCommand);
}


/***************************************************************************
 * Extracts the username from the file path stored in the predefined macro
 * __FILE__ and saves it in the shared memory system.
 *
 * @return A string representing the extracted username based on the file path.
 ***********************************************************************/
std::string environment::extract_username() {
    std::string ssTemp = __FILE__;
    ssTemp = ssTemp.substr(6,ssTemp.length());
    int offset = ssTemp.find('/');
    ssTemp = ssTemp.substr(0,offset);
    strcpy(gpSh->m_pShMemng->szUser,ssTemp.c_str());
    return ssTemp;
}

/***************************************************************************
 * Checks whether the curl command-line tool is installed and available on
 * the system. This method attempts to run the `curl --version` command and
 * verifies its successful execution. If the command executes successfully,
 * it reads the curl version into an internal variable and returns true.
 *
 * @return true if curl is installed and detected successfully; false otherwise.
 ***********************************************************************/
bool environment::check_curl_installed() {
    char szTemp[128];
    bool bRetVar;

    m_bCurlPresent = false;

    int retval = system(
        "curl --version >/tmp/curl_version.txt 2>/tmp/curl.err");
    if (0 == retval) {
        FILE *fd = fopen("/tmp/curl_version.txt", "r");
        char szCurlVersion[BUFSIZ];
        fgets(szCurlVersion, sizeof(szCurlVersion), fd);
        strcpy(m_szCurlVersion, szCurlVersion);
        bRetVar = true;
    } else {
        bRetVar = false;
    }
    return bRetVar;
}


/***************************************************************************
 * Retrieves the CGI root directory path.
 *
 * @param bDebug A boolean flag that may be used for debug-specific behavior.
 *               Currently, it does not impact the method's functionality.
 * @return The CGI root directory path as a string.
 ***********************************************************************/
std::string environment::get_cgi_root(bool bDebug)
{
  std::string ssCgiRoot = gpSh->m_pShMemng->szCgiRoot;
  return ssCgiRoot;
}

/***************************************************************************
 * Retrieves the CGI root as a null-terminated string.
 *
 * @param bDebug A boolean flag to potentially control debug behavior. Its
 *               usage is not implemented in this method.
 * @return A pointer to a null-terminated string representing the CGI root.
 ***********************************************************************/
char * environment::get_cgi_root_as_sz(bool bDebug)
{
  return gpSh->m_pShMemng->szCgiRoot;
}

/***************************************************************************
 * @brief Sets the CGI root directory path for the environment configuration.
 *
 * This method constructs the CGI root path using the protocol, IP address,
 * and base path "/cgi-bin/" and updates the shared memory configuration.
 *
 * @param bDebug Indicates whether the operation is in debug mode.
 ***********************************************************************/
void environment::set_cgi_root(bool bDebug)
{
  std::string ssCgiRoot = gpSh->m_pShMemng->szProtocol;
  ssCgiRoot.append(gpSh->m_pShMemng->szIP);
  ssCgiRoot.append("/cgi-bin/");
  strcpy(gpSh->m_pShMemng->szCgiRoot,ssCgiRoot.c_str());
}

/***************************************************************************
 * Retrieves the version string of the cURL library used in the environment.
 *
 * @return A pointer to the string containing the cURL version.
 ***********************************************************************/
char *environment::get_curl_version() {
    return m_szCurlVersion;
}


/***************************************************************************
 * Retrieves the hostname of the system from the /etc/hostname file.
 *
 * @param bDebug A boolean flag to enable or disable debug mode. This parameter
 *               is currently unused in this implementation.
 * @return A string containing the hostname of the system. If the /etc/hostname
 *         file cannot be read, the behavior is undefined.
 ***********************************************************************/
std::string environment::get_hostname(bool bDebug)
{
  std::string ssEtcHostnameFQFS = "/etc/hostname";
  std::ifstream ifs(ssEtcHostnameFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  return ssInbuf;
}

/***************************************************************************
 * Sets the hostname by reading the value from the file located at /etc/hostname
 * and storing it in the shared memory structure.
 *
 * @param bDebug A boolean flag that indicates whether debugging is enabled.
 *               Currently, this parameter is not utilized in the function
 *               implementation.
 ***********************************************************************/
void environment::set_hostname(bool bDebug)
{
  std::string ssEtcHostnameFQFS = "/etc/hostname";
  std::ifstream ifs(ssEtcHostnameFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  strcpy(gpSh->m_pShMemng->szHostname,ssInbuf.c_str());
}


/***************************************************************************
 * Retrieves the root directory path for images based on the current protocol
 * configuration.
 *
 * @param bDebug A boolean flag indicating whether debug mode is enabled.
 *               This parameter is passed but not utilized within the method.
 *
 * @return A string representing the root directory path for images.
 ***********************************************************************/
std::string environment::get_img_root(bool bDebug)
{
  std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
  return ssImgRoot;
}

/***************************************************************************
 * @brief Sets the image root directory path by constructing it from protocol,
 * IP, user, and default image path components. The method builds the full
 * path for the image root directory based on shared memory configuration data.
 * The final path is stored in the shared memory structure `szImgRoot`.
 *
 * @param bDebug A boolean flag to indicate whether debugging is enabled. This
 *               parameter is currently unused in the implementation.
 ***********************************************************************/
void environment::set_img_root(bool bDebug)
{
  std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
  ssImgRoot.append(gpSh->m_pShMemng->szIP);
  ssImgRoot.append("/~");
  ssImgRoot.append(gpSh->m_pShMemng->szUser);
  ssImgRoot.append("/fw/images/");
  strcpy(gpSh->m_pShMemng->szImgRoot,ssImgRoot.c_str());
}

/***************************************************************************
 * Retrieves the root path for styles.
 *
 * @param bDebug A boolean flag indicating if the environment is in debug mode.
 *               It does not currently affect the returned value.
 * @return A string representing the root directory path for styles.
 ***********************************************************************/
std::string environment::get_styles_root(bool bDebug)
{
  std::string ssStylesRoot = gpSh->m_pShMemng->szStylesRoot;
  return ssStylesRoot;
}

/***************************************************************************
 * @brief Configures and sets the styles root path for the environment.
 *
 * This method constructs the styles root path based on protocol, IP,
 * user information, and a predefined path structure, and then sets it to the
 * shared memory's styles root variable.
 *
 * @param bDebug A boolean flag to indicate if debugging configuration is
 *               enabled.
 */
void environment::set_styles_root(bool bDebug)
{
  std::string ssStylesRoot = gpSh->m_pShMemng->szProtocol;
  ssStylesRoot.append(gpSh->m_pShMemng->szIP);
  ssStylesRoot.append("/~");
  ssStylesRoot.append(gpSh->m_pShMemng->szUser);
  ssStylesRoot.append("/fw/styles/");
  strcpy(gpSh->m_pShMemng->szStylesRoot,ssStylesRoot.c_str());
}

/***************************************************************************
 * Retrieves the root file path for styles.
 *
 * @param bDebug A boolean flag indicating if the environment is in debug mode.
 *               It does not currently affect the returned value.
 * @return A string representing the root file directory path for styles.
 ***********************************************************************/
std::string environment::get_styles_file_root(bool bDebug)
{
	std::string ssStylesRoot = gpSh->m_pShMemng->szStylesFileRoot;
	return ssStylesRoot;
}

/***************************************************************************
 * @brief Configures and sets the styles filesystem root path for the
 * environment.
 *
 * This method constructs the styles root path based on
 * user information, and a predefined path structure, and then sets it to the
 * shared memory's styles root path variable.
 *
 * @param bDebug A boolean flag to indicate if debugging configuration is
 *               enabled.
 */
void environment::set_styles_file_root(bool bDebug)
{
	std::string ssStylesFileRoot = "/home/";
	ssStylesFileRoot.append(gpSh->m_pShMemng->szUser);
	ssStylesFileRoot.append("/public_html/fw/styles/");
	strcpy(gpSh->m_pShMemng->szStylesFileRoot,ssStylesFileRoot.c_str());
}


/***************************************************************************
 * Retrieves the journal root directory path.
 *
 * @param bDebug A boolean value indicating whether debugging is enabled.
 *               Not used in the actual implementation.
 * @return A string representing the journal root directory path.
 ***********************************************************************/
std::string environment::get_journal_root(bool bDebug)
{
  std::string ssJournalRoot = gpSh->m_pShMemng->szJournalRoot;
  return ssJournalRoot;
}

/***************************************************************************
 * @brief Sets the journal root directory path for the current environment.
 *
 * This method configures the journal root directory by constructing
 * the path based on the user's home directory and appending a folder
 * structure specific to the environment.
 *
 * @param bDebug Indicates whether debug mode is enabled. This parameter
 *               does not currently influence the method's logic.
 ***********************************************************************/
void environment::set_journal_root(bool bDebug)
{
    std::string ssJournalRoot = "/home/";
    ssJournalRoot.append(gpSh->m_pShMemng->szUser);
    ssJournalRoot.append("/Documents/Fw_Notes/");
    strcpy(gpSh->m_pShMemng->szJournalRoot,ssJournalRoot.c_str());
}   /* TODO: access into system call to check whether this dir exists, and to make
	 it if not */


/***********************************************************************
 * @brief Sets the temporary root directory path.
 *
 * This function constructs the temporary root path for the environment
 * and assigns it to the global shared memory structure. The path is
 * dynamically built based on the current user's directory and a standard
 * temporary folder structure.
 *
 * @param bDebug A boolean flag indicating whether the debug mode is enabled.
 *               Currently, this parameter is not utilized within the function.
 *
 * The function takes the following steps:
 * 1. Initializes the base path to "/home/".
 * 2. Appends the username stored in the shared memory structure.
 * 3. Appends the remainder of the temporary directory path.
 * 4. Copies the constructed path into the shared memory's temporary root
 *    variable.
 ***********************************************************************/
void environment::set_tmp_root(bool bDebug)
{
    std::string ssTmpRoot = "/home/";
    ssTmpRoot.append(gpSh->m_pShMemng->szUser);
    ssTmpRoot.append("/public_html/fw/tmp/");
    strcpy(gpSh->m_pShMemng->szTmpRoot,ssTmpRoot.c_str());
}

/***************************************************************************
 * Retrieves the name of the network interface.
 *
 * Executes the "netstat -r" command to gather routing table information
 * and extracts the interface name. The results are also stored in a
 * shared memory segment for subsequent access.
 *
 * @param bDebug Indicates whether debugging is enabled, though this parameter
 *               is currently unused in the function.
 * @return The name of the network interface as a string.
 ***********************************************************************/
std::string environment::get_interface(bool bDebug) {
	here;
	std::string ssUser = gpSh->m_pShMemng->szUser;
	gpXinetd->trigger(VPA_NETSTAT_PORT);
	here;

	char szNetstatStdoutFQFS[128];
	strcpy(szNetstatStdoutFQFS,
		("/home/"
			+ ssUser
			+ "/public_html/fw/tmp/netstat.stdout").c_str());

	gpSysLog->loginfo(szNetstatStdoutFQFS);
	sleep(2);
	here;
	gpSysLog->loginfo(szNetstatStdoutFQFS);
		// FILE *fd = fopen(szNetstatStdoutFQFS, "r");
		// char szTemp[BUFSIZ];
		// sprintf(szTemp, "fd is %p", fd);
		// gpSysLog->loginfo(szTemp);
		//
		//
		// //assert(nsfd != nullptr);
		// here;

	char szBuffer[BUFSIZ];

	std::ifstream ifs(szNetstatStdoutFQFS);
	here;
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);
	ifs >> szBuffer;
	gpSysLog->loginfo(szBuffer);


	//  fgets(szBuffer, sizeof(szBuffer), fd);
    // fgets(szBuffer, sizeof(szBuffer), fd);
    // fgets(szBuffer, sizeof(szBuffer), fd);
    //strncpy(m_szIface, &szBuffer[73], IFNAMSIZ);
	strncpy(m_szIface, szBuffer, IFNAMSIZ);
    //m_szIface[strlen(m_szIface) - 1] = 0;
    strncpy(gpSh->m_pShMemng->szIface, m_szIface, IFNAMSIZ);
    std::string ssRetVal = m_szIface;
    return ssRetVal;
}


/***************************************************************************
 * Retrieves the IP address for the configured network interface and optionally
 * performs additional processing depending on the debug mode.
 *
 * @param bDebug A boolean flag to indicate if additional debug processing
 *               should be performed.
 * @return A string representing the IP address or fully qualified DNS name
 *         associated with the network interface.
 ***********************************************************************/
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

	char szTemp[BUFSIZ];
	sprintf(szTemp, "szIface is %s",gpSh->m_pShMemng->szIface);
	gpSysLog->loginfo(szTemp);

	ofs << "#!/bin/bash" << std::endl
	    << "ip addr show "
		<< m_szIface
		<< " > /home/"
		<< ssUser
		<< "/public_html/fw/tmp/ip.stdout"
		<< std::endl;

	ofs.close();
	system(("chmod +x /home/"
					+ ssUser
					+ "/public_html/fw/scripts/inetd-ip-redirect.sh").c_str());
	gpXinetd->trigger(VPA_IP_PORT);
	sleep(1);
	here;
	// Open the read for input
	FILE *ipfd = fopen(("/home/"
								+ ssUser
								+ "/public_html/fw/tmp/ip.stdout").c_str(),
								"r");
	here;
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
	here;
	gpSysLog->loginfo(szBuffer);
	// convcert the zero terminated string to a standard string
	std::string ssBuffer = szBuffer;

	// while waiting to see the string with our interface in it...
	while (std::string::npos == ssBuffer.find(ssIfaceColon)) {

		// get another line
		fgets(szBuffer, sizeof(szBuffer), ipfd);
		gpSysLog->loginfo(szBuffer);

		// convert to a std::string
		ssBuffer = szBuffer;

	} // rinse and repeat...

	// scan for the line with the inet address in it
    fgets(szBuffer, sizeof(szBuffer), ipfd);
    while (0 != strncmp("inet", &szBuffer[4], 4)) {
        fgets(szBuffer, sizeof(szBuffer), ipfd);
    }

	// clear the result string to all zeroes
    memset(m_szIP, 0, sizeof(m_szIP));

	int index = 9;			// offset of IP address in line (fixed)
    int destindex = 0;		// starting offset in the destn string

	// copy until we find a slash
	while (szBuffer[index] != '/') {
        m_szIP[destindex++] = szBuffer[index++];
    }

	// // If it happens to be Doug's workstation, convert the IP
	// // number to a fully qualified DNS name.
 //    if (0 == strcmp("192.168.4.17", m_szIP)) {
 //        strncpy(m_szIP, "daphne.goodall.com", DNS_FQDN_SIZE_MAX);
 //    }
	// write the zero terminated IP number to the shared
    strncpy(gpSh->m_pShMemng->szIP, m_szIP, DNS_FQDN_SIZE_MAX);

	// convert the zero terminated IP to std::string
    std::string ssRetVal = gpSh->m_pShMemng->szIP;
	here;
	gpSysLog->loginfo(m_szIP);
	// return the std::string  version of the IP number
    return ssRetVal;
}

/***************************************************************************
 * Tries to determine the protocol (HTTP or HTTPS) to be used for a given
 * hostname by performing curl commands and checking for outputs indicating
 * a valid response.
 *
 * @param bDebug A boolean parameter indicating whether the call is in debug
 *               mode, although it is not actively used in the current
 *               implementation.
 * @return A string representing the chosen protocol ("https://" or "http://").
 *         If neither protocol responds, it returns an empty string.
 ***********************************************************************/
std::string environment::get_protocol(bool bDebug)
{
  std::string ssRetVal;

  // try https://
  std::string ssCommand;
  std::string ssCurlStdoutFQFS = "/tmp/curl.stdout";
  std::string ssCurlStderrFQFS = "/tmp/curl.stderr";
  ssCommand = "curl ";
  ssCommand.append("https://");
  ssCommand.append(gpSh->m_pShMemng->szHostname);
  ssCommand.append(" > ");
  ssCommand.append(ssCurlStdoutFQFS);
  ssCommand.append(" 2> ");
  ssCommand.append(ssCurlStderrFQFS);
  system(ssCommand.c_str());
  std::ifstream ifs(ssCurlStdoutFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  if(ssInbuf.empty()) {
    ssCommand = "curl ";
    ssCommand.append("http://");
    ssCommand.append(gpSh->m_pShMemng->szHostname);
    ssCommand.append(" > ");
    ssCommand.append(ssCurlStdoutFQFS);
    ssCommand.append(" 2> ");
    ssCommand.append(ssCurlStderrFQFS);
    system(ssCommand.c_str());
    std::ifstream ifs(ssCurlStdoutFQFS);
    std::string ssInbuf;
    ifs >> ssInbuf;
    if(ssInbuf.empty()) {
      ;
    } else {
      if(0 == strcmp("<!DOCTYPE",ssInbuf.c_str())) {
        ssRetVal = "http://";
      }
    }
  } else {
    if(0 == strcmp("<!DOCTYPE",ssInbuf.c_str())) {
      ssRetVal = "https://";
    }
  }
  return ssRetVal;
}


/***************************************************************************
 * @brief Sets the protocol (HTTP or HTTPS) for the system based on the
 * hostname's accessibility. This method determines whether to use "https://"
 * or "http://" as the protocol for the application's hostname. It first
 * attempts to access the hostname using HTTPS. If successful, it assigns
 * "https://" as the protocol. Otherwise, it falls back to HTTP and assigns
 * "http://" as the protocol if accessible.
 *
 * @param bDebug Indicates whether the method is executed in debug mode.
 *               Currently not used in this implementation.
 ***********************************************************************/
void environment::set_protocol(bool bDebug)
{
  std::string ssRetVal;

  // try https://
  std::string ssCommand;
  std::string ssCurlStdoutFQFS = "/tmp/curl.stdout";
  std::string ssCurlStderrFQFS = "/tmp/curl.stderr";
  ssCommand = "curl ";
  ssCommand.append("https://");
  ssCommand.append(gpSh->m_pShMemng->szHostname);
  ssCommand.append(" > ");
  ssCommand.append(ssCurlStdoutFQFS);
  ssCommand.append(" 2> ");
  ssCommand.append(ssCurlStderrFQFS);
  system(ssCommand.c_str());
  std::ifstream ifs(ssCurlStdoutFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  if(ssInbuf.empty()) {
    ssCommand = "curl ";
    ssCommand.append("http://");
    ssCommand.append(gpSh->m_pShMemng->szHostname);
    ssCommand.append(" > ");
    ssCommand.append(ssCurlStdoutFQFS);
    ssCommand.append(" 2> ");
    ssCommand.append(ssCurlStderrFQFS);
    system(ssCommand.c_str());
    std::ifstream ifs(ssCurlStdoutFQFS);
    std::string ssInbuf;
    ifs >> ssInbuf;
    if(ssInbuf.empty()) {
        ;
    } else {
      if(0 == strcmp("<!DOCTYPE",ssInbuf.c_str())) {
        ssRetVal = "http://";
      }
    }
  } else {
    if(0 == strcmp("<!DOCTYPE",ssInbuf.c_str())) {
      ssRetVal = "https://";
    }
  }
  strcpy(gpSh->m_pShMemng->szProtocol,ssRetVal.c_str());
}

/***************************************************************************
 * Retrieves the value of the private member variable `m_szLogname`.
 *
 * @return A pointer to the character array representing the log name.
 ***********************************************************************/
char *environment::get_szLogname() {
    return m_szLogname;
}

/***************************************************************************
 * Retrieves the value of the log name associated with the environment.
 *
 * @return A string representing the log name.
 ***********************************************************************/
std::string environment::get_ssLogname() {
    return m_ssLogname;
}

/***************************************************************************
 * Retrieves the name of the script associated with the environment.
 *
 * @return A pointer to a character string representing the script name.
 ***********************************************************************/
char *environment::get_scriptname() {
    return m_pszScriptName;
}


/***************************************************************************
 * Checks if the cURL library is present and available in the environment.
 *
 * @return True if the cURL library is present, otherwise false.
 ***********************************************************************/
bool environment::is_curl_present() {
    return m_bCurlPresent;
}


/***************************************************************************
 * Checks the presence of the netstat utility in the system.
 *
 * The method verifies whether the netstat executable exists at the
 * standard file path "/usr/bin/netstat" using the access system call.
 *
 * @return true if the netstat utility is present at the specified path,
 *         false otherwise.
 ***********************************************************************/
bool environment::is_netstat_present() {
    std::string ssFQFS = "/usr/bin/netstat";
    if(0 == access(ssFQFS.c_str(),F_OK)) {
        return true;
    } else {
        return false;
    };
}


///////////////////////////
// eof - environment.cpp //
///////////////////////////
