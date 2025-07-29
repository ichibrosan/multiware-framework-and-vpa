////////////////////////////////////////////////////////////////////
// ~/public_html/fw/CSysLog.hpp 2025-07-16 08:16 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#include "std.h"
/**
 * @class CSysLog
 * @brief The CSysLog class is designed for logging system-related information.
 *
 * This class provides a basic logging mechanism for recording information
 * related to the execution of a program. Designed primarily for use in
 * server-side or backend applications where critical logging is essential
 * for debugging and tracking system operations.
 */
class CSysLog
{
	/**
	 * Constructor for the CSysLog class.
	 * Initializes the system logging mechanism by setting the log mask and
	 * opening a connection to the syslog service with predetermined parameters.
	 *
	 * @return An instance of the CSysLog class.
	 */
public:
	CSysLog();
	/**
	 * Logs an informational message to the system log.
	 *
	 * This method sends a message with informational priority to the system's logging mechanism.
	 * It can be used for recording runtime details, tracking execution flow, or logging general text-based information.
	 *
	 * @param pszMsg A pointer to a null-terminated string, which is the message to be logged.
	 */
	static void loginfo(const char* pszMsg);

	void herefunc(const char*, const char*, int);

	/**
	 * Destructor for the CSysLog class.
	 *
	 * Closes the system log opened for this instance by invoking closelog().
	 * This ensures that any resources associated with the logging system
	 * are properly released.
	 */
	~CSysLog();
};

///////////////////////
// eof - CSysLog.hpp //
///////////////////////
