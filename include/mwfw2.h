////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mwfw2.h 2025-07-16 08:08 dwg -                //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#define MWFW_SUPPORT_CRTBIND

#include "std.h"
#include "fw-limits.h"
#include "version.h"
#include "config.h"
//#include "vpadiscclient.h"
//#include "vpadiscserver.h"
#include "testdiscclient.h"
#include "testdiscclient.h"
#include "mutations.h"

#ifndef gpCrt
#include "crtbind.h"
extern crtbind* gpCrt;
#endif // gpCrt

#ifndef gpSemiGr
#include "semigraphics.h"
extern semigraphics* gpSemiGr;
#endif


#include "window.h"
#include "vparpc.h"
#include "CVpaRpc.h"

#ifndef gpSysLog
#include "CSysLog.h"
extern CSysLog* gpSysLog;
extern bool gbHere;
#endif

#include "cfgini.h"				// config file support class

#include "xinetdcfg.h"			// /etc/xinetd.d/vpa  maintenance class
#include "CServices.h"			// /etc/services file maintenance class
#include "checkAuth.h"			// check user authentication class
#include "cliLogin.h"			// command-line login class

#ifndef gpDotCfg
#include "dotconfig.h"
extern dotconfig* gpDotCfg;
#endif

#ifndef gpEnv
#include "environment.h"
extern environment* gpEnv;
#endif

#include "cgicc.h"
#include <cgicc/Cgicc.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/FormEntry.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace cgicc;
extern Cgicc* gpCgi;

#ifndef gpCgiBind
#include "cgibind.h"
extern cgibind* gpCgiBind;
#endif

#ifndef gpDash
#include "dashboard.h"
extern dashboard* gpDash;
#endif

#ifndef gpGPIO
#include "RTkGPIO.h"
extern RTkGPIO* gpGPIO;
#endif

#ifndef gpHtml
#include "cgihtml.h"
extern cgihtml* gpHtml;
#endif

#ifndef gpLog
#include "CLog.h"
extern CLog* gpLog;
#endif

#ifndef gpOS
#include "osIface.h"
extern osIface* gpOS;
#endif

#ifndef gpSchema
#include "schema.h"
extern schema* gpSchema;
#endif

#ifndef gpSh
#include "shared.h"
extern shared* gpSh;
#endif

#ifndef gpShMemMutex
#include "shMemMutex.h"
extern SharedMemoryMutex* gpShMemMutex;
#endif

#ifndef gpShMemMgr
#include "shMemMgr.h"
extern SharedMemoryManager* gpShMemMgr;
#endif

#ifndef gpPassword
#include "password.h"
extern password* gpPassword;
#endif

#ifndef gpCsv
#include "readCsv.h"
extern readCsv* gpCsv;
#endif

#ifndef gpSchCC
#include "schemaCompiler.h"
extern schemaCompiler* gpSchCC;
#endif

#ifndef gpXinetd
#include "xinetdctl.h"
extern xinetdctl* gpXinetd;
#endif

#ifndef gpVpaRpc
#include "vparpc.h"
extern vparpc* gpVpaRpc;
#endif

#include "config.h"
#include "stylist.h"

#ifndef gpHex
#include "iHex.h"
extern iHex* gpHex;
#endif

#ifndef gpIchi
#include "ichibrosan.h"
extern ichibrosan *gpIchi;
#endif

/**
 * @class mwfw2
 * @brief This class provides foundational functionality for the middleware
 * framework (MWFW). The mwfw class encapsulates the state and behavior
 * necessary for managing server configurations (e.g., CGI mode) and logging
 * system information. It interacts with the CSysLog class for logging and
 * provides mechanisms for determining whether the framework is running in
 * CGI mode.
 */
class mwfw2
{
	/**
	 * A boolean flag indicating whether the application is running in a CGI
	 * (Common Gateway Interface) environment. This member variable is set
	 * during object initialization in the constructor of the `mwfw` class.
	 * It checks the presence of the "SERVER_PORT" environment variable to
	 * determine if the application is running in a CGI context. If the
	 * environment variable exists, `m_bCGI` is set to `true`, otherwise it
	 * is `false`. This variable is primarily used in conjunction with the
	 * `isCGI()` method to provide access to its value for other parts of
	 * the application.
	 */
	bool m_bCGI;
	/**
	 * Constructor for the mwfw class.
	 * Initializes the mwfw instance, determines if the current execution
	 * context is in a CGI environment, and sets up a system logger. The
	 * method checks for the presence of the "SERVER_PORT" environment variable
	 * to infer if the code is being executed in a CGI context. If the CGI
	 * environment is detected, it outputs content-type headers. Additionally,
	 * it initializes an instance of the CSysLog class for system logging
	 * purposes.
	 *
	 * @return An instance of the mwfw class.
	 */

	int m_iFeatureset;
	int m_iEventset;
	int m_iDebugset;

public:
	mwfw2(const char* pszFile, const char* pszFunction);
	/**
	 * Determines whether the application is running in a CGI (Common Gateway
	 * Interface) context. This method evaluates the internal state of the
	 * class to check whether it is functioning as a CGI process based on
	 * certain environment variables set at runtime.
	 *
	 * @return True if the application is running in a CGI context, otherwise false.
	 */
	bool isCGI();
	/**
	 * Logs an informational message using the system logging mechanism.
	 *
	 * This function routes the provided message to an internal system logger
	 * for informational purposes.
	 *
	 * @param pszMsg A pointer to a null-terminated string containing the
	 * message to log.
	 */
	void sl_loginfo(const char*);
};

////////////////////
// eof - mwfrw2.h //
////////////////////
