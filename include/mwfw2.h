/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/mwfw2.h 2025/02/14     //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#ifndef MWFW_H
#define MWFW_H

#include "std.h"
#include "fw-limits.h"
#include "version.h"
#include "config.h"

#ifndef gpSysLog
#include "CSysLog.hpp"
extern CSysLog * gpSysLog;
extern bool gbHere;
#endif

#ifndef gpEnv
#include "environment.h"
extern environment * gpEnv;
#endif

#include "cgicc.h"
#include <cgicc/Cgicc.h>
#include <cgicc/CgiDefs.h>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/FormEntry.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>

using namespace cgicc;
extern Cgicc * gpCgi;

#ifndef gpCgiBind
#include "cgibind.h"
extern cgibind * gpCgiBind;
#endif

#ifndef gpDash
#include "dashboard.h"
extern dashboard * gpDash;
#endif

#ifndef gpHtml
#include "cgihtml.h"
extern cgihtml * gpHtml;
#endif

#ifndef gpHB
#include "htmlbind.h"
extern  htmlbind * gpHB;
#endif

#ifndef gpLog
#include "CLog.hpp"
extern CLog * gpLog;
#endif

#ifndef gpOS
#include "osIface.h"
extern osIface * gpOS;
#endif

#ifndef gpSchema
#include "schema.h"
extern schema * gpSchema;
#endif

#ifndef gpSh
#include "shared.h"
extern shared * gpSh;
#endif

#ifndef gpPassword
#include "password.h"
extern password * gpPassword;
#endif

#ifndef gpCsv
#include "readCsv.h"
extern readCsv * gpCsv;
#endif

#ifndef gpSchCC
#include "schemaCompiler.h"
extern schemaCompiler * gpSchCC;
#endif

#ifndef gpTest
#include "test.h"
extern test * gpTest;
#endif

#ifndef gpXinetd
#include "xinetdctl.h"
extern xinetdctl * gpXinetd;
#endif

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include "config.h"
#include "diagnoseDefs.h"
#include "restDefs.h"
#include "diagnose.h"
#include "stylist.h"

#ifndef gpHex
#include "iHex.h"
extern iHex * gpHex;
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
class mwfw2 {
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
	bool      m_bCGI;
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
public:
  mwfw2(const char *pszFile,const char *pszFunction);
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
	void sl_loginfo(const char *);
};



#endif //MWFW_H
