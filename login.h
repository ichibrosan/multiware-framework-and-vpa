////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/login.h 2025/01/19    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#ifndef FW_LOGIN_H
#define FW_LOGIN_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
Cgicc       * gpCgi;
#include "CSysLog.hpp"
CSysLog      * gpSysLog;
#include "CLog.hpp"
CLog        * gpLog;
#include "cgihtml.h"
cgihtml     * gpHtml;
#include "environment.h"
environment * gpEnv;
#include "osIface.h"
osIface     * gpOS;
#include "password.h"
password    * gpPassword;
#include "readCsv.h"
readCsv     * gpCsv;
#include "schema.h"
schema      * gpSchema;
#include "shared.h"
shared      * gpSh;
#include "cgibind.h"
cgibind     * gpCgiBind;
#include "dashboard.h"
dashboard   * gpDash;
#include "cgibind.h"
extern cgibind     * gpCgiBind;
#endif //FW_LOGIN_H
///////////////////
// eof - login.h //
///////////////////
