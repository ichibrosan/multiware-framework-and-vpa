////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/menu.h 2025/01/19     //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#ifndef FW_MENU_H
#define FW_MENU_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
Cgicc   * gpCgi;
#include "CLog.hpp"
CLog    * gpLog;
#include "cgihtml.h"
cgihtml * gpHtml;
#include "environment.h"
environment * gpEnv;
#include "osIface.h"
osIface * gpOS;
#include "readCsv.h"
readCsv * gpCsv;
#include "schema.h"
schema  * gpSchema;
#include "shared.h"
shared  * gpSh;
#include "cgibind.h"
cgibind * gpCgiBind;
#include "dashboard.h"
dashboard * gpDash;
#endif //FW_MENU_H
//////////////////
// eof - menu.h //
//////////////////