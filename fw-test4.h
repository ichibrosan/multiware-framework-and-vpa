//
// Created by doug on 1/20/25.
//

#ifndef FW_TEST4_H
#define FW_TEST4_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
using namespace cgicc;

#include "environment.h"
extern environment * gpEnv;

#include "cgibind.h"
extern cgibind * gpCgiBind;

#include "cgihtml.h"
extern cgihtml * gpHtml;

#include "osIface.h"

#include "CLog.hpp"
extern CLog   *gpLog;

#include "shared.h"
extern shared *gpSh;

#endif //FW_TEST4_H
