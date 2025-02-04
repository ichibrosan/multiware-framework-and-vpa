///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/diagnose.h   2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#ifndef DIAGNOSE_H
#define DIAGNOSE_H
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

#endif //DIAGNOSE_H
