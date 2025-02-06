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
 * @return
 ******************************************/
std::string environment::get_ip(bool bDebug)
{
  char szBuffer[BUFSIZ];
  system("ip a > /tmp/ip.out");
  FILE *ipfd = fopen("/tmp/ip.out", "r");
  char szIfaceColon[BUFSIZ];
  strncpy(szIfaceColon, m_szIface, BUFSIZ);
  strcat(szIfaceColon, ":");
  fgets(szBuffer, sizeof(szBuffer), ipfd);
  while (0 != strncmp(&szBuffer[3],
                      szIfaceColon,
                      strlen(szIfaceColon))) {
      fgets(szBuffer, sizeof(szBuffer), ipfd);
    }
    fgets(szBuffer, sizeof(szBuffer), ipfd);
    while (0 != strncmp("inet", &szBuffer[4], 4)) {
        fgets(szBuffer, sizeof(szBuffer), ipfd);
    }
    memset(m_szIP, 0, sizeof(m_szIP));
    int index = 9;
    int destindex = 0;
    while (szBuffer[index] != '/') {
        m_szIP[destindex++] = szBuffer[index++];
    }
    if (0 == strcmp("192.168.4.17", m_szIP)) {
        strncpy(m_szIP, "daphne.goodall.com", DNS_FQDN_SIZE_MAX);
    }
    strncpy(gpSh->m_pShMemng->szIP, m_szIP, DNS_FQDN_SIZE_MAX);

    std::string ssRetVal = gpSh->m_pShMemng->szIP;
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
