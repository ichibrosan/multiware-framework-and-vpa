// mwfw2.cpp

// Created by doug on 2/2/25.
//

#include "mwfw2.h"

#include "dashboard.h"

#include "stylist.h"

dashboard		* gpDash;

dotconfig		* gpDotCfg;

environment		* gpEnv;
//shmvars			* gpShmVars;
shared			* gpSh;
SharedMemoryMutex	* gpShMemMutex;
SharedMemoryManager * gpShMemMgr;

osIface			* gpOS;
CLog			* gpLog;
CSysLog			* gpSysLog;
bool			  gbHere;
cgibind			* gpCgiBind;
cgihtml			* gpHtml;
Cgicc			* gpCgi;
schema			* gpSchema;
readCsv			* gpCsv;
test			* gpTest;
schemaCompiler	* gpSchCC;
password		* gpPassword;
xinetdctl		* gpXinetd;
//stylist		* gpStylist;
config			* gpConfig;
iHex			* gpHex;
//htmlbind        * gpHB;

/**
 * Constructor for the mwfw class. Initializes the CGI mode based
 * on the SERVER_PORT environment variable and sets up the system
 * logging mechanism.
 *
 * The constructor performs the following operations:
 * - Determines if CGI mode is active based on the presence of
 *   "SERVER_PORT" environment variable.
 * - Outputs a content-type header if CGI mode is enabled.
 * - Initializes an instance of CSysLog and logs the constructor
 *   invocation.
 *
 * @return A newly constructed mwfw instance with initialized
 *         CGI and logging mechanisms.
 */
mwfw2::mwfw2(const char * pszFile,const char * pszFunction)
{
	gpSysLog = new CSysLog();
	gbHere = false;

	gpDotCfg = new dotconfig();

	m_bCGI = false;
	char * ptr = getenv("SERVER_PORT");
	if(nullptr != ptr) {
		m_bCGI = true;
	}
	if(isCGI()) {
		std::cout << "Content-type:\ttext/html\n\n" << std::endl;
	}
	gpXinetd = new xinetdctl();
	//gpShmVars = new shmvars();
	gpSh = new shared();
	gpShMemMutex = new SharedMemoryMutex(CFG_MUTEX_NAME);
	gpShMemMgr = new SharedMemoryManager(CFG_MUTEX_NAME);
    gpEnv = new environment();
    gpLog = new CLog(__FILE__,__FUNCTION__);
    gpOS = new osIface();
    gpCgi = new Cgicc();
    gpCgiBind = new cgibind();
	//gpStylist = new stylist();
	gpConfig = new config();
	gpHex = new iHex();
	//gpHB = new htmlbind();
}

/**
 * Checks whether the application is operating in a CGI (Common Gateway
 * Interface) environment.
 *
 * @return true if the application is running in a CGI environment
 *		   (determined by the internal state of m_bCGI), false otherwise.
 */
bool mwfw2::isCGI()
{
	return m_bCGI;
}

/**
 * Logs an informational message using the system logging mechanism.
 *
 * This method forwards the given message to the CSysLog instance's loginfo
 * method, which is responsible for logging the message to the system's
 * logging facilities, like syslog.
 *
 * @param pszMsg A null-terminated string containing the informational
 *				 message to log. The caller must ensure that the message
 *				 is valid and not nullptr.
 */
void mwfw2::sl_loginfo(const char *pszMsg)
{
  gpSysLog->loginfo(pszMsg);
}
