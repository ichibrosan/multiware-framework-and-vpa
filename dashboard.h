//
// Created by doug on 1/20/25.
//

#ifndef DASHBOARD_H
#define DASHBOARD_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
//Cgicc * gpCgi;
#include "cgibind.h"
//cgibind * gpCgiBind;
#include "shared.h"
extern shared * gpSh;
#include "schema.h"
#include "cgihtml.h"
extern cgihtml * gpHtml;
#include "osIface.h"
extern osIface * gpOS;

enum {
    JOURNAL = 1<<0,
    LOGOUT  = 1<<1,
    MENU    = 1<<2,
    NUM_DASHBOARD_BUTTONS = 3
};

class dashboard {
    cgibind * m_pCgiBind;
    CSysLog * m_pSysLog;

    char m_szAuthUserName[UT_NAMESIZE];
    char m_szAuthFirstName[UT_NAMESIZE];
    char m_szAuthLastName[UT_NAMESIZE];
    char m_szAuthLevel[UT_NAMESIZE];
    char m_szAuthUUID[UUID_SIZE];

public:
    dashboard(
        int handle,
        int buttons,
        const char *pszFile,
        std::string ssUsername,
        std::string ssPassword);

    std::string form_cgi(
        const char *pszName,
        int handle);

    static void threadSystemCall(std::string ssCmd);

    void navbar(
        int handle,
        int buttons,
        std::string ssCgiName,
        std::string ssUsername,
        std::string ssPassword);


    void process_toggles(
        std::string ssCgiName,
        std::string ssUsername,
        std::string ssPassword,
        int handle);

};

#endif //DASHBOARD_H
