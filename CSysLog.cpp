////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CSyslog.cpp  2021/10  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

// CLog.cpp 2021/10/dwg - updated opening modes for use
// with MAVlink process.
// Copyright (c) 2021 RMD Systems, All Rights Reserved.
// Written by Douglas Goodall.

#include "CSysLog.hpp"

CSysLog::CSysLog()
{
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog("multiware",LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

}

void CSysLog::loginfo(const char * pszMsg)
{
    syslog(LOG_CONS|LOG_NOWAIT|LOG_NDELAY|LOG_PID,"%s",pszMsg);
}

CSysLog::~CSysLog()
{
    closelog();
}