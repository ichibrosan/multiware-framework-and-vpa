////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/noteload.h 2025/01/29 mf  //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.          //
////////////////////////////////////////////////////////////////////////////
#ifndef MULTIWARE_NOTELOAD_H
#define MULTIWARE_NOTELOAD_H
#include "std.h"
#include "fw-limits.h"

#include "CSysLog.hpp"
/**
 * Global pointer to the CSysLog instance, used for system-level logging throughout the application.
 *
 * This variable serves as a centralized logging mechanism, allowing different parts of the application
 * to record informational or diagnostic messages for debugging, monitoring, or auditing purposes.
 * The CSysLog object underlying this pointer is responsible for interacting with the system's logging facilities.
 *
 * Utilized in scenarios like reporting usual runtime statuses, handling application flow, or
 * capturing critical events like errors or authentication failures.
 *
 * It must be initialized (e.g., dynamically allocated) before use and properly destroyed to
 * ensure resource cleanup.
 */
CSysLog     * gpSysLog;

#include "shared.h"
/**
 * @brief Global pointer to an instance of the `shared` class.
 *
 * `gpSh` is a shared memory handler that provides addressability to
 * shared memory segments used throughout the application. It is
 * instantiated as a singleton object in various modules to ensure
 * consistent access to shared memory resources.
 *
 * This pointer is initialized to `nullptr` by default and later
 * instantiated as needed during application execution.
 *
 * Usage Context:
 * - Commonly used in components that require shared memory access,
 *   such as data synchronization or inter-process communication.
 * - Instantiated using the `shared` class constructor to establish
 *   a connection to shared memory using its internal mechanisms.
 *
 * Responsibility:
 * Ensures that the application correctly handles and manipulates
 * shared memory segments as per its operational requirements.
 */
shared      * gpSh = nullptr;
#include "CLog.hpp"
/**
 * @brief Global pointer to an instance of CLog used for logging operations.
 *
 * The `gpLog` variable is a global pointer to a CLog object that provides
 * logging functionalities throughout the application. It enables recording
 * of messages, warnings, errors, and other log-related data.
 *
 * @note Ensure that the `gpLog` is properly initialized before usage to avoid
 *       undefined behavior. Proper deallocation is also necessary to manage
 *       resources correctly.
 */
CLog        * gpLog;
#include "osIface.h"
/**
 * @brief Global pointer to an instance of the osIface class.
 *
 * This pointer is used to interact with features provided by the osIface class, which
 * includes operations such as managing file paths, generating fully qualified file
 * system paths for logs or journals, and performing various file-related tasks.
 *
 * gpOS is initialized and utilized in various parts of the application to perform
 * OS-specific file and path management operations. This instance enables functions
 * like generating absolute paths suitable for logs or schemas, and provides utility
 * methods for file manipulation. It is typically created dynamically at the start
 * of the program and referenced throughout the application.
 */
osIface     * gpOS;
#include "environment.h"
/**
 * @brief Global pointer to the environment object.
 *
 * A global variable that stores a pointer to an `environment` object.
 * This variable is intended to provide access to environment-related
 * functionalities throughout the application.
 *
 * Use this pointer with caution to ensure safe and consistent access
 * to shared resources or state.
 */
environment * gpEnv;
#include "cgicc.h"
/**
 * @brief A global pointer to an instance of Cgicc used for handling CGI requests and interactions.
 *
 * This variable is used across multiple modules to provide a centralized mechanism
 * for managing Common Gateway Interface (CGI) operations such as accessing form variables,
 * environment information, and other HTTP-related functionalities.
 *
 * The `gpCgi` object is initialized at runtime and facilitates server-side processing
 * in web-based applications by allowing interaction with web server inputs.
 *
 * Typical use cases include:
 *  - Retrieving form variables submitted via HTTP GET or POST methods.
 *  - Accessing and manipulating CGI environment variables including HTTP headers.
 *  - Streamlining communication between server-side logic and client-side requests.
 *
 * It is a shared, global resource and should be initialized before usage in any component
 * requiring CGI interactions.
 *
 * Note that proper cleanup (deleting the `gpCgi` instance) is crucial to avoid memory leaks.
 */
Cgicc       * gpCgi;
#include "readCsv.h"
/**
 * @brief Global pointer to an instance of the readCsv class.
 *
 * This variable is used to manage and process CSV (Comma-Separated Value) data
 * throughout the application. It is primarily responsible for storing and
 * providing access to parsed CSV data. The readCsv instance is initialized
 * with the file name of the CSV file to be processed and is used to parse
 * and retrieve the necessary data within the application.
 *
 * @note The readCsv class provides functionality such as parsing data,
 * retrieving specific data by row and column, and providing the total
 * number of lines in the CSV file. This global instance enables centralized
 * access to CSV data across various parts of the program logic.
 *
 * @see readCsv
 */
readCsv     *gpCsv;
#include "cgibind.h"
/**
 * A global pointer to an instance of the `cgibind` class.
 *
 * This variable is used for interacting with CGI form data within the application.
 * It allows access to HTTP form variables and referrer information by leveraging
 * the methods defined in the `cgibind` class. The instance is typically initialized
 * at runtime and remains accessible throughout the application's lifecycle.
 *
 * Example functionalities provided by `gpCgiBind` include retrieving form variable
 * values (e.g., schema, handle, username), processing HTTP referrer information,
 * and more, as defined in the `cgibind` class.
 *
 * Note:
 * - Proper initialization of `gpCgiBind` is necessary before performing any operations.
 * - Ensure to release the allocated memory for `gpCgiBind` when it is no longer needed
 *   to prevent memory leaks.
 */
cgibind     * gpCgiBind;
#include "schema.h"
/**
 * @brief Global pointer to an instance of the `schema` class.
 *
 * `gpSchema` is a global variable that holds a pointer to an instance of the `schema` class.
 * The `schema` object is used to handle operations related to processing schema data,
 * handling rows, and operating on structured data files. It is initialized and utilized
 * in various application components, including rendering, login, and diagnostics modules.
 *
 * This variable allows different parts of the application to share and manipulate the same
 * schema instance, facilitating consistent access to schema-related functionalities.
 */
schema      * gpSchema;
#include "cgihtml.h"
/**
 * @brief Pointer to a cgihtml structure used for handling HTML page generation and CGI operations.
 *
 * This variable is utilized to manage and manipulate HTML content dynamically within
 * the application. It serves as the central interface for generating and processing
 * CGI-based HTML outputs.
 *
 * The `cgihtml` structure provides utilities for managing HTML elements, form
 * inputs, and responses in a CGI-based web application. Assigning and using this
 * variable is expected to conform to the standard lifecycle of a CGI handler
 * in the application context.
 *
 * It is a global pointer, and its usage must be carefully managed to avoid
 * resource conflicts or memory mismanagement.
 */
cgihtml     * gpHtml;
#endif //MULTIWARE_NOTELOAD_H
//////////////////////
// eof - noteload.h //
//////////////////////
