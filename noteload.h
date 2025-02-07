////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/noteload.h 2025/01/29 mf  //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.          //
////////////////////////////////////////////////////////////////////////////
#ifndef MULTIWARE_NOTELOAD_H
#define MULTIWARE_NOTELOAD_H
#include "std.h"
#include "fw-limits.h"

#include "CSysLog.hpp"
CSysLog     * gpSysLog;

#include "shared.h"
shared      * gpSh = nullptr;
#include "CLog.hpp"
CLog        * gpLog;
#include "osIface.h"
osIface     * gpOS;
#include "environment.h"
environment * gpEnv;
#include "cgicc.h"
Cgicc       * gpCgi;
#include "readCsv.h"
readCsv     *gpCsv;
#include "cgibind.h"
cgibind     * gpCgiBind;
#include "schema.h"
schema      * gpSchema;
#include "cgihtml.h"
cgihtml     * gpHtml;
#endif //MULTIWARE_NOTELOAD_H
//////////////////////
// eof - noteload.h //
//////////////////////
