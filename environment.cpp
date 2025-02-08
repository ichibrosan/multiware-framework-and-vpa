/////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/environment.cpp 2025/01/10 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.      //
/////////////////////////////////////////////////////////////////////////////
#include "environment.h"

#define GET_HOSTNAME_AND_PROTOCOL
#define GET_INTERFACE
#define GET_IP
#define GET_ROOTS
#define GET_REMOTE_USER

char gszUser[32];
std::string gssUser;

/**
 *
 */
environment::environment() {
  char szTemp[128];

    m_pSysLog = new CSysLog();

    extract_username();

    m_bCurlPresent = check_curl_installed();

    get_interface(false);

    set_hostname(false);

    set_protocol(false);

    get_scriptname();

    get_ip(false);

    set_cgi_root(false);

    set_img_root(false);

    set_styles_root(false);

    set_journal_root(false);

}

std::string environment::extract_username() {
    std::string ssTemp = __FILE__;
    ssTemp = ssTemp.substr(6,ssTemp.length());
    int offset = ssTemp.find('/');
    ssTemp = ssTemp.substr(0,offset);
    strcpy(gpSh->m_pShMemng->szUser,ssTemp.c_str());
    return ssTemp;
}

/**
 * Check of curl in installed in the system and set pS->
 */
bool environment::check_curl_installed() {
    char szTemp[128];
    bool bRetVar;

    m_bCurlPresent = false;

    int retval = system("curl --version >/tmp/curl_version.txt 2>/tmp/curl.err");
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


std::string environment::get_cgi_root(bool bDebug)
{
  std::string ssCgiRoot = gpSh->m_pShMemng->szCgiRoot;
  return ssCgiRoot;
}

char * environment::get_cgi_root_as_sz(bool bDebug)
{
  return gpSh->m_pShMemng->szCgiRoot;
}

void environment::set_cgi_root(bool bDebug)
{
  std::string ssCgiRoot = gpSh->m_pShMemng->szProtocol;
  ssCgiRoot.append(gpSh->m_pShMemng->szIP);
  ssCgiRoot.append("/cgi-bin/");
  strcpy(gpSh->m_pShMemng->szCgiRoot,ssCgiRoot.c_str());
}

char *environment::get_curl_version() {
    return m_szCurlVersion;
}


/**************************************************
 * Determine the hostname of the host machine
 * @return A std::string containing the hostname
 **************************************************/
std::string environment::get_hostname(bool bDebug)
{
  std::string ssEtcHostnameFQFS = "/etc/hostname";
  std::ifstream ifs(ssEtcHostnameFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  return ssInbuf;
}

/**************************************************
 * Determine the hostname of the host machine
 * @return A std::string containing the hostname
 **************************************************/
void environment::set_hostname(bool bDebug)
{
  std::string ssEtcHostnameFQFS = "/etc/hostname";
  std::ifstream ifs(ssEtcHostnameFQFS);
  std::string ssInbuf;
  ifs >> ssInbuf;
  strcpy(gpSh->m_pShMemng->szHostname,ssInbuf.c_str());
}


/*************************************************
 * Determine img root
 * @param bDebug
 * @return
 *************************************************/
std::string environment::get_img_root(bool bDebug)
{
  std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
  return ssImgRoot;
}

/*************************************************
 * Determine img root
 * @param bDebug
 * @return
 *************************************************/
void environment::set_img_root(bool bDebug)
{
  std::string ssImgRoot = gpSh->m_pShMemng->szProtocol;
  ssImgRoot.append(gpSh->m_pShMemng->szIP);
  ssImgRoot.append("/~");
  ssImgRoot.append(gpSh->m_pShMemng->szUser);
  ssImgRoot.append("/fw/images/");
  strcpy(gpSh->m_pShMemng->szImgRoot,ssImgRoot.c_str());
}

/*************************************************
 * Determine styles root
 * @param bDebug
 * @return
 *************************************************/
std::string environment::get_styles_root(bool bDebug)
{
  std::string ssStylesRoot = gpSh->m_pShMemng->szStylesRoot;
  return ssStylesRoot;
}

/*************************************************
 * Determine styles root
 * @param bDebug
 * @return
 *************************************************/
void environment::set_styles_root(bool bDebug)
{
  std::string ssStylesRoot = gpSh->m_pShMemng->szProtocol;
  ssStylesRoot.append(gpSh->m_pShMemng->szIP);
  ssStylesRoot.append("/~");
  ssStylesRoot.append(gpSh->m_pShMemng->szUser);
  ssStylesRoot.append("/fw/styles/");
  strcpy(gpSh->m_pShMemng->szStylesRoot,ssStylesRoot.c_str());
}

/*************************************************
 * Determine styles root
 * @param bDebug
 * @return
 *************************************************/
std::string environment::get_journal_root(bool bDebug)
{
  std::string ssJournalRoot = gpSh->m_pShMemng->szJournalRoot;
  return ssJournalRoot;
}

/*************************************************
 * Determine styles root
 * @param bDebug
 * @return
 *************************************************/
void environment::set_journal_root(bool bDebug)
{
  std::string ssJournalRoot = "/home/";
  ssJournalRoot.append(gpSh->m_pShMemng->szUser);
  ssJournalRoot.append("/Documents/Fw_Notes/");
  strcpy(gpSh->m_pShMemng->szJournalRoot,ssJournalRoot.c_str());
}

std::string environment::get_interface(bool bDebug) {
    system("netstat -r > /tmp/netstat.out");
    FILE *nsfd = fopen("/tmp/netstat.out", "r");
    char szBuffer[BUFSIZ];
    fgets(szBuffer, sizeof(szBuffer), nsfd);
    fgets(szBuffer, sizeof(szBuffer), nsfd);
    fgets(szBuffer, sizeof(szBuffer), nsfd);
    strncpy(m_szIface, &szBuffer[73], IFNAMSIZ);
    m_szIface[strlen(m_szIface) - 1] = 0;
    strncpy(gpSh->m_pShMemng->szIface, m_szIface, IFNAMSIZ);
    std::string ssRetVal = m_szIface;
    return ssRetVal;
}


/******************************************
 * Determine the IP of the host machine
 * @param bDebug
 * @return Returns a std::string containing
 *			our primary IPv4 IP number
 *	Note: The method used in this function
 *	is to redirect the stdout of the "ip a"
 *	command to a file in the /tmp and read it
 *	back to scrape the IP number from the
 *	output. Having previously found our
 *	interface name, we scan down the output
 *	until we find the line for our interface,
 *	then we look a line later for the IPv4 IP
 *	number associated with the interface.
 *	2025-02-07 20:33 dwg -
 ******************************************/
std::string environment::get_ip(bool bDebug)
{
	// define a buffer for reading lines from the
	// /tmp/ip.out file.
	char szBuffer[BUFSIZ];

	// execute the ip command and redirect the
	// output where we can find it.
	system("ip a > /tmp/ip.out");

	// Open the read for input
	FILE *ipfd = fopen("/tmp/ip.out", "r");

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

	// convcert the zero terminated string to a standard string
	std::string ssBuffer = szBuffer;

	// while waiting to see the string with our interface in it...
	while (std::string::npos == ssBuffer.find(ssIfaceColon)) {

		// get another line
		fgets(szBuffer, sizeof(szBuffer), ipfd);

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

	// If it happens to be Doug's workstation, convert the IP
	// number to a fully qualified DNS name.
    if (0 == strcmp("192.168.4.17", m_szIP)) {
        strncpy(m_szIP, "daphne.goodall.com", DNS_FQDN_SIZE_MAX);
    }
	// write the zero terminated IP number to the shared
    strncpy(gpSh->m_pShMemng->szIP, m_szIP, DNS_FQDN_SIZE_MAX);

	// convert the zero terminated IP to std::string
    std::string ssRetVal = gpSh->m_pShMemng->szIP;

	// return the std::string  version of the IP number
    return ssRetVal;
}

/******************************************************************
 * Determine the best working protocol for curl access
 * @param bDebug
 * @return Returns a std::string containing "https://" or "http://"
 ******************************************************************/
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


/******************************************************************
 * Determine the best working protocol for curl access
 * @param bDebug
 * @return Returns a std::string containing "https://" or "http://"
 ******************************************************************/
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

char *environment::get_szLogname() {
    return m_szLogname;
}

std::string environment::get_ssLogname() {
    return m_ssLogname;
}

/****************************************************************************
 * Get pointer to null terminated C string containing SCRIPT_NAME from getenv
 * @return C string pointer to script name
 ***************************************************************************/
char *environment::get_scriptname() {
    return m_pszScriptName;
}


/*********************************************************************
 * Return a boolean indicating whether curl is installed and available
 * @return
 *********************************************************************/
bool environment::is_curl_present() {
    return m_bCurlPresent;
}


/***********************************************************************
 * Test for the presence of the "netstat" extrinsic utility that is part
 * of the "net-tools" package.
 * @return
 * 2025/01/11 dwg - we noticed that locus didn't have netstat installed
 * and this caused the  environment constructor to fail.
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
