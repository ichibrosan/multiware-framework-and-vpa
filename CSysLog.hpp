//////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/CSysLog.hpp  2025/01/25 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.   //
//////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CSYSLOG_HPP
#define MULTIWARE_CSYSLOG_HPP
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
class CSysLog {
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
	void loginfo(const char *);

	void here(const char *,const char *,int);

	/**
	 * Destructor for the CSysLog class.
	 *
	 * Closes the system log opened for this instance by invoking closelog().
	 * This ensures that any resources associated with the logging system
	 * are properly released.
	 */
	~CSysLog();
};


#endif // MULTIWARE_CSYSLOG_HPP
