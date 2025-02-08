//
// Created by doug on 2/2/25.
//

#ifndef MWFW_H
#define MWFW_H

#include "CSysLog.hpp"

/**
 * @class mwfw
 * @brief This class provides foundational functionality for the middleware framework (MWFW).
 *
 * The mwfw class encapsulates the state and behavior necessary for managing server configurations
 * (e.g., CGI mode) and logging system information. It interacts with the CSysLog class for
 * logging and provides mechanisms for determining whether the framework is running in CGI mode.
 */
class mwfw {
	/**
	 * Pointer to an instance of the CSysLog class used for system logging.
	 *
	 * This member variable is responsible for handling system log operations
	 * within the `mwfw` class. It is initialized during the construction of
	 * the `mwfw` object and facilitates the logging of messages to the system's
	 * logging service. The CSysLog class handles the details of connecting to
	 * the syslog service and formatting messages for logging.
	 *
	 * Usage:
	 * - Primarily used internally within the `mwfw` class to log messages.
	 * - Provides logging functionality such as information-level messages.
	 *
	 * Ownership:
	 * - The `mwfw` class is responsible for managing the memory associated
	 *   with this pointer. It ensures that the instance of `CSysLog` is
	 *   properly initialized and released during the lifecycle of the `mwfw` object.
	 */
	CSysLog * m_pSysLog;
	/**
	 * A boolean flag indicating whether the application is running in a CGI (Common Gateway Interface) environment.
	 *
	 * This member variable is set during object initialization in the constructor of the `mwfw` class.
	 * It checks the presence of the "SERVER_PORT" environment variable to determine if the application is
	 * running in a CGI context. If the environment variable exists, `m_bCGI` is set to `true`, otherwise it is `false`.
	 *
	 * This variable is primarily used in conjunction with the `isCGI()` method to provide access to
	 * its value for other parts of the application.
	 */
	bool      m_bCGI;
	/**
	 * Constructor for the mwfw class.
	 * Initializes the mwfw instance, determines if the current execution context
	 * is in a CGI environment, and sets up a system logger.
	 *
	 * The method checks for the presence of the "SERVER_PORT" environment variable
	 * to infer if the code is being executed in a CGI context. If the CGI environment
	 * is detected, it outputs content-type headers. Additionally, it initializes
	 * an instance of the CSysLog class for system logging purposes.
	 *
	 * @return An instance of the mwfw class.
	 */
public:
  mwfw();
	/**
	 * Determines whether the application is running in a CGI (Common Gateway Interface) context.
	 *
	 * This method evaluates the internal state of the class to check whether it is functioning
	 * as a CGI process based on certain environment variables set at runtime.
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
	 * @param pszMsg A pointer to a null-terminated string containing the message to log.
	 */
	void sl_loginfo(const char *);
};



#endif //MWFW_H
