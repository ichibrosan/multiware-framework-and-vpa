////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CLog.hpp 2025/01/10 03:19 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.     //
////////////////////////////////////////////////////////////////////////////

#ifndef CLOG_HPP
#define CLOG_HPP

#include "std.h"
#include "fw-limits.h"
#include "osIface.h"
extern osIface *gpOS;


////////////////////////////////////////////////////
// This define declares the fully qualified file
// specification of the application log file
//#define LOG_FILESPEC "gecore-main.log"

class CLog {

    ////////////////////////////////////////////
    // This is the fully qualified filespec of
    // the logfile, which is used on each access
    // to open the file for appending.
    char m_szFQFS[FILENAME_MAX];


public:

    /////////////////////////////////////////////
    // This is the prototype of the CLog class
    // constructor. It opens a log file and saves
    // the file descriptor in member data for
    // subsequent calls to the write function.
    CLog(const char *pszFileName, const char *pszFunctionName);

    //////////////////////////////////////////////////
    // This is the prototype of the truncate function
    // whose purpose is to delete the current contents
    // in preparation in preparation for new data.
    int truncate();

    ////////////////////////////////////////////////
    // This is the prototype of the logging function
    // a string is passed to the write function and
    // it is subsequently written into the log file
    int write(const char *);

    int writesanstime(const char *);

    int namedBool(const char *, bool);

    int namedDouble(const char *, double);

    int namedInt(const char *, int);

    int namedString(const char *, const char *);

    ///////////////////////////////////////////////
    // This is the prototype of the varargs version
    // of the logging function. A format string and
    // some parameters are passed in and formatted
    // before being written to the log file..
    int writev(const char *, ...);

    void getTimeDateStamp(char *);

};

extern CLog *g_pLog;
extern osIface *pOS;

#endif //CLOG_HPP

////////////////////
// eof - CLog.hpp //
////////////////////
