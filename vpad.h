////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/vpad.h 2025/01/11 05:21   //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_VPAD_H
#define MULTIWARE_VPAD_H

#include "std.h"
#include "fw-limits.h"
#include "CLog.hpp"
/**
 * @brief Global pointer to an instance of CLog used for logging purposes.
 *
 * gpLog is a pointer to the CLog class that can be utilized throughout the
 * application to log messages, errors, or other relevant information.
 * This global instance ensures centralized and consistent logging.
 */
CLog   * gpLog;
#include "osIface.h"
/**
 * @brief Represents the operating system currently in use or targeted.
 *
 * The `gpOS` variable is utilized to store information about the
 * operating system environment or platform on which the application
 * is running or is intended to run. It may encapsulate platform-specific
 * details, including version, architecture, or identification strings.
 *
 * This variable can be leveraged in scenarios where platform-based
 * configuration, conditional behavior, or diagnostic operations
 * are needed within the application lifecycle.
 */
osIface * gpOS;
#include "shared.h"
/**
 * @brief A global pointer to a `shared` instance.
 *
 * This variable is used to provide global access to an instance of the `shared` class,
 * which manages shared resources or functionalities within the application. It is
 * initialized to `nullptr` by default and should be properly instantiated and managed
 * during the runtime of the application to ensure resource integrity and avoid memory leaks.
 */
shared * gpSh = nullptr;
#include "environment.h"
/**
 * @brief Global environment pointer used to manage and maintain
 *        access to global application state and resources.
 *
 * This variable acts as a centralized object which provides
 * interfaces to interact with system-level or global configurations,
 * services, or resources that are shared across different modules
 * of the application. Proper initialization and cleanup are crucial
 * for maintaining application stability.
 */
environment * gpEnv;
#include "readCsv.h"
/**
 * @brief A variable representing data in CSV (Comma-Separated Values) format.
 *
 * This variable is utilized to handle, process, or store tabular data that adheres to the CSV file format.
 * It may hold the raw CSV string, parsed data structures, or any intermediate state required for CSV operations.
 * Common operations could include reading from or writing to CSV files, parsing data, or data manipulation.
 *
 * The structure, type, and contents of `gpCsv` should be aligned with the specific use case and
 * application logic it is associated with.
 */
readCsv * gpCsv;
#include "cgihtml.h"
/**
 * @brief Pointer to a `cgihtml` instance used to manage and process HTML content in
 * the current CGI (Common Gateway Interface) context.
 *
 * This variable provides access to the HTML-related functionalities required for
 * handling user inputs, generating HTML outputs, and performing other
 * web-based operations in the CGI framework. It is typically initialized as part
 * of the application startup procedure and used throughout the application lifecycle.
 */
cgihtml * gpHtml;
#include "cgibind.h"
/**
 * @brief A global pointer to a `cgibind` object used for handling CGI-related operations.
 *
 * This variable serves as a global instance of the `cgibind` class, which provides functionalities
 * such as retrieving CGI form variables and HTTP referrer information. It is intended to facilitate
 * CGI processing within the application.
 *
 * The `gpCgiBind` instance is commonly initialized during application startup and accessed throughout
 * the program for operations related to CGI data handling.
 */
cgibind * gpCgiBind;
#include "cgicc.h"
/**
 * @brief A global pointer to a Cgicc object for handling CGI operations.
 *
 * This variable enables the handling of server-based CGI requests and responses
 * throughout different parts of the application. It's utilized for extracting form
 * variables, managing the web environment, and performing required CGI-based functionalities.
 *
 * @note It is initialized at runtime and used extensively in modules like `diagnose`, `journal`,
 *       `render`, and `menu`. Proper instantiation is required to avoid segmentation faults or
 *       unintended behavior.
 *
 * @see Cgicc
 */
Cgicc * gpCgi;


#endif // MULTIWARE_VPAD_H