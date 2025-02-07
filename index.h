////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/index.h 2025/01/19    //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#ifndef INDEX_H
#define INDEX_H
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
#include "schemaCompiler.h"
schemaCompiler * gpSchCC;
#include "test.h"
test * gpTest;
#include "cgibind.h"
cgibind * gpCgiBind;
#include "CSysLog.hpp"
CSysLog * gpSysLog;

#include "mwfw.h"

// #include "cgibind.h"
// cgibind * gpCgibind;

#endif //INDEX_H
///////////////////
// eof - index.h //
///////////////////
