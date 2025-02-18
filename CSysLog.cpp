////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CSyslog.cpp  2021/10  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

// CLog.cpp 2021/10/dwg - updated opening modes for use
// with MAVlink process.
// Copyright (c) 2021 RMD Systems, All Rights Reserved.
// Written by Douglas Goodall.

#include "CSysLog.hpp"

/**
 * Constructor for the CSysLog class.
 *
 * Initializes the system logging mechanism by:
 * - Setting the log mask to log messages up to the priority level of 'LOG_INFO'.
 * - Opening a connection to the syslog service using specific flags and the 'LOG_LOCAL1' facility.
 *
 * This constructor prepares the logging environment for system-level logging
 * operations to be performed subsequently by instances of this class.
 *
 * @return An instance of the CSysLog class.
 */
CSysLog::CSysLog()
{
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog("multiware",LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

}

void CSysLog::here(const char *pszFile,const char *pszFunction,int iLine) {
    char szTemp[1024];
    sprintf(szTemp,"%s::%s()#%d",pszFile,pszFunction,iLine);
    loginfo(szTemp);
}


/**
 * Logs an informational message to the system log.
 *
 * This method writes the provided message to the system's logging mechanism
 * with the informational priority level. It is useful for tracking general
 * system events or debugging details during application runtime.
 *
 * @param pszMsg A constant pointer to a null-terminated string representing
 *               the message to be logged.
 */
void CSysLog::loginfo(const char * pszMsg)
{
    syslog(LOG_CONS|LOG_NOWAIT|LOG_NDELAY|LOG_PID,"%s",pszMsg);
}

/**
 * Destructor for the CSysLog class.
 *
 * Ensures proper cleanup of the syslog resources by invoking the `closelog()` function.
 * This method is automatically called when an instance of the CSysLog class is destroyed.
 * It is responsible for closing the connection to the system log that was established
 * during the lifetime of the instance.
 */
CSysLog::~CSysLog()
{
    closelog();
}