////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/main.h   2025/01/20 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_H
#define MAIN_H
#include "std.h"
//#include "limits.h"
#include "cgicc.h"
using namespace cgicc;
Cgicc          * gpCgi;
#include "test.h"
test           * gpTest;
#include "environment.h"
environment    * gpEnv;
#include "shared.h"
shared         * gpSh;
#include "readCsv.h"
readCsv        * gpCsv;
#include "CLog.hpp"
CLog           * gpLog;
#include <cgicc/Cgicc.h>    // the cgicc headers
#include "schemaCompiler.h"
schemaCompiler * gpSchema;
#include "osIface.h"
osIface        * gpOS;

#endif //MAIN_H
