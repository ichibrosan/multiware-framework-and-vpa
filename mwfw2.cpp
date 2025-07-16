////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mwfw2.cpp 2025-07-15 18:16 dwg -              //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "include/mwfw2.h"

#include "include/dashboard.h"

#include "include/stylist.h"

Cgicc* gpCgi;
cgibind* gpCgiBind;
config* gpConfig;
crtbind* gpCrt;
readCsv* gpCsv;
dashboard* gpDash;
dotconfig* gpDotCfg;
environment* gpEnv;
bool gbHere;
iHex* gpHex;
cgihtml* gpHtml;
CLog* gpLog;
osIface* gpOS;
password* gpPassword;
schemaCompiler* gpSchCC;
schema* gpSchema;
semigraphics* gpSemiGr;
shared* gpSh;
SharedMemoryMutex* gpShMemMutex;
SharedMemoryManager* gpShMemMgr;
CSysLog* gpSysLog;
test* gpTest;
vparpc* gpVpaRpc;
xinetdctl* gpXinetd;


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
mwfw2::mwfw2(const char* pszFile, const char* pszFunction)
{
	gpCrt = new crtbind();
	gpVpaRpc = new vparpc();
	gpSemiGr = new semigraphics();
	gpSysLog = new CSysLog();
	gbHere = false;

	m_bCGI = false;
	char* ptr = getenv("SERVER_PORT");
	if (nullptr != ptr)
	{
		m_bCGI = true;
	}
	if (isCGI())
	{
		std::cout << "Content-type:\ttext/html\n\n" << std::endl;
	}

	// gpMP3			= new MP3Player();
	// gpMP3Play		= new play();
	gpSh = new shared();
	gpShMemMutex = new SharedMemoryMutex(CFG_MUTEX_NAME);
	gpShMemMgr = new SharedMemoryManager(CFG_MUTEX_NAME);
	gpEnv = new environment();
	gpLog = new CLog(__FILE__, __FUNCTION__);
	gpOS = new osIface();
	gpCgi = new Cgicc();
	gpCgiBind = new cgibind();
	gpConfig = new config();
	gpHex = new iHex();
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
void mwfw2::sl_loginfo(const char* pszMsg)
{
	gpSysLog->loginfo(pszMsg);
}
