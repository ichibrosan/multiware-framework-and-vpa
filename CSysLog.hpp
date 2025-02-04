//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CSysLog.hpp  2025/01/25 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CSYSLOG_HPP
#define MULTIWARE_CSYSLOG_HPP
#include "std.h"
class CSysLog {
public:
    CSysLog();
    void loginfo(const char *);
    ~CSysLog();
};


#endif // MULTIWARE_CSYSLOG_HPP
