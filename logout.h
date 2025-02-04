/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/logout.h   2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef FW_LOGOUT_H
#define FW_LOGOUT_H

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
using namespace cgicc;
Cgicc       * gpCgi;

#include "CLog.hpp"
CLog        * gpLog;
#include "cgihtml.h"
cgihtml     * gpHtml;
#include "environment.h"
environment * gpEnv;
#include "logout.h"
#include "osIface.h"
osIface     * gpOS;
#include "password.h"
#include "readCsv.h"
readCsv     * gpCsv;
#include "schema.h"
schema      * gpSchema;
#include "shared.h"
shared      * gpSh;
#include "cgibind.h"
cgibind     * gpCgiBind;

class logout {
public:
  logout();
};

#endif // FW_LOGOUT_H
