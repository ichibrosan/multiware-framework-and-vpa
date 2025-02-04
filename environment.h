//////////////////////////////////////////////////////////////////////////
// daphe.goodall.com:/home/doug/public_html/fw/environment.h 2025/01/10 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_ENVIRONMENT_H
#define MULTIWARE_ENVIRONMENT_H

#include "std.h"
#include "fw-limits.h"
#include "osIface.h"
extern osIface *gpOS;
#include "CLog.hpp"
extern CLog   *gpLog;
#include "shared.h"
extern shared *gpSh;

class environment {

    CSysLog * m_pSysLog;

    bool m_bCgiccPresent;
    bool m_bCurlPresent;
    bool m_bMwcgiPresent;

    char m_szMwcgi[BUFSIZ];
    char m_szCurlVersion[BUFSIZ];
    char *m_pszLogname;
    char m_szLogname[FILENAME_MAX];
    std::string m_ssLogname;

    // Remote user name from Apache environment (CGI)
    char *m_pszRemoteUser;
    char m_szRemoteUser[UT_NAMESIZE];
    std::string m_ssRemoteUser;

    char m_szHostName[DNS_FQDN_SIZE_MAX];
    char m_szIface[IFNAMSIZ];

    char m_szIP[DNS_FQDN_SIZE_MAX];
    std::string m_ssIP;

    char *m_pszScriptName;
public:
    environment();

    bool check_curl_installed();

    std::string get_hostname(bool bDebug);
    void        set_hostname(bool bDebug);
    std::string get_interface(bool bDebug);
    std::string get_ip(bool bDebug);
    std::string get_protocol(bool bDebug);
    void        set_protocol(bool bDebug);

    std::string get_cgi_root(bool bDebug);
    char *      get_cgi_root_as_sz(bool bDebug);
    void        set_cgi_root(bool bDebug);

    std::string get_img_root(bool bDebug);
    void        set_img_root(bool bDebug);

    std::string get_styles_root(bool bDebug);
    void        set_styles_root(bool bDebug);

    std::string get_journal_root(bool bDebug);
    void        set_journal_root(bool bDebug);

    std::string extract_username();

    bool is_curl_present();
    bool is_netstat_present();

    char *get_curl_version();



    char *get_szLogname();

    std::string get_ssLogname();

    char *get_scriptname();

};

#endif //MULTIWARE_ENVIRONMENT_H
