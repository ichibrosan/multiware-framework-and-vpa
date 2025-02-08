///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/diagnose.h   2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#ifndef DIAGNOSE_H
#define DIAGNOSE_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
using namespace cgicc;
/**
 * @brief Global pointer to an instance of the Cgicc class.
 *
 * This variable is used for handling and parsing CGI inputs in the application.
 * It provides the ability to extract, process, and interact with form data
 * submitted via HTTP requests. The Cgicc instance initializes and manages
 * the environment for handling CGI operations.
 *
 * Typical use of this variable includes retrieving form data sent through
 * HTTP POST or GET methods, which is then utilized for further processing
 * in various modules of the application.
 *
 * This object is globally allocated and initialized in multiple parts of the
 * program and is integral to the application's handling of web-based interactions.
 */
Cgicc       * gpCgi;
#include "CLog.hpp"
/**
 * @brief Pointer to the global logging utility instance.
 *
 * This variable is used across the application to handle logging functionalities such as
 * debug messages, errors, warnings, or other runtime information. The instance of CLog
 * provides methods to facilitate consistent logging throughout the system.
 *
 * Ensure that an instance of CLog is correctly initialized before attempting to use gpLog.
 * Accessing or invoking logging methods through an uninitialized gpLog may result in
 * undefined behavior.
 */
CLog        * gpLog;
#include "cgihtml.h"
/**
 * @brief Global pointer to a cgihtml structure.
 *
 * This variable represents a global pointer to an instance of the cgihtml structure, which is typically
 * used for managing and processing CGI (Common Gateway Interface) HTML content in a web application.
 *
 * The cgihtml structure may include various attributes and functionalities required for handling HTML
 * content generation, CGI parsing, and related operations. It is used throughout the program for
 * interacting with HTML data in CGI contexts.
 *
 * Proper initialization and appropriate usage of this variable are essential to avoid potential issues in
 * managing or rendering HTML content in the application.
 */
cgihtml     * gpHtml;
#include "environment.h"
/**
 * @brief Global pointer to an instance of the `environment` class.
 *
 * This variable is used throughout the application to manage and
 * interact with the execution environment, such as retrieving
 * environment variables, paths, or system-related configurations.
 *
 * It is typically initialized during the startup process of the application
 * and provides access to essential environment-specific data.
 *
 * Usage of this variable should be thread-safe if accessed in a concurrent
 * environment, depending on the implementation details of the `environment` class.
 */
environment * gpEnv;
#include "osIface.h"
/**
 * @brief Global pointer to an instance of the osIface class.
 *
 * This variable serves as a globally accessible instance of the `osIface`
 * class, primarily used to manage operating system-level functionality
 * such as file handling and path operations. It is instantiated in
 * multiple parts of the application, providing access to methods and
 * utilities that interface with the file system and associated
 * functionalities.
 *
 * The `gpOS` pointer is initialized at runtime and should be treated as a
 * shared resource, with caution taken to ensure thread safety if accessed
 * concurrently. It enables centralized management of OS-level operations
 * across different modules in the application.
 */
osIface     * gpOS;
#include "password.h"
/**
 * @brief A global pointer to an instance of the `password` class.
 *
 * This variable serves as a shared reference to manage and validate
 * password authentication and operations throughout the application.
 * The `password` class provides functionalities such as retrieving UUIDs,
 * dumping internal state information, and validating username-password
 * combinations.
 *
 * Usage:
 * The `gpPassword` pointer is used to invoke methods for user authentication
 * and associated tasks. It must be properly initialized before use.
 */
password    * gpPassword;
#include "readCsv.h"
/**
 * @brief Pointer to a global object of type readCsv used for reading and parsing CSV files.
 *
 * This variable is initialized with a reference to a readCsv instance and is utilized throughout
 * the application for managing CSV data parsing and retrieval. It stores the parsed dataset and provides
 * access to individual rows and columns by indexing. Specifically, it allows the retrieval
 * and manipulation of user authentication data and other CSV-structured content, such as "passwd.csv".
 *
 * For example, this variable plays a key role in authentication processes, granting access
 * to user credentials and related attributes stored in the parsed data.
 *
 * @note This global variable is used across multiple modules and is fundamental to user data handling.
 */
readCsv     * gpCsv;
#include "schema.h"
/**
 * @brief Global pointer to an instance of the schema class.
 *
 * This variable acts as a shared resource across various implementations
 * involving schema-related operations. It holds a dynamically allocated
 * instance of the schema class, representing the structure and data
 * defined by the corresponding schema file.
 *
 * The gpSchema variable is typically initialized with a specific schema file
 * name and is used for performing schema-driven actions such as data
 * preprocessing, schema generation, and processing of schema data.
 *
 * Examples of files that initialize or utilize gpSchema:
 * - menu.cpp
 * - noteload.cpp
 * - journal.cpp
 *
 * It is important to ensure that the corresponding schema instance
 * is appropriately managed (e.g., dynamically allocated and destroyed)
 * in order to prevent memory leaks or undefined behavior.
 *
 * Note: This global pointer may be shared across different parts of the
 * application, and its usage should be guarded to avoid concurrency issues
 * or unintended data modifications.
 */
schema      * gpSchema;
#include "shared.h"
/**
 * @brief Global pointer to a `shared` object.
 *
 * This variable is used to manage and establish access to shared memory segments within
 * the application. It instantiates the `shared` class, enabling operations that interface
 * with shared resources.
 *
 * gpSh is utilized in multiple modules of the application, including initialization and
 * management of shared memory segments, ensuring consistent access across components. The
 * `shared` object instance it points to is created dynamically based on the application's
 * runtime requirements.
 *
 * @note Ensure that gpSh is appropriately initialized and deallocated to avoid memory leaks
 * or undefined behavior. It is a critical resource shared among multiple modules.
 */
shared      * gpSh;
#include "cgibind.h"
/**
 * Pointer to a singleton instance of the `cgibind` class.
 *
 * This variable is used to interface with CGI form data and handle HTTP requests
 * in server-side applications. `gpCgiBind` enables access to functionality such as
 * retrieving form variables, extracting HTTP referrer information, and providing
 * directory or file name components of referrer URLs.
 *
 * The instance of `cgibind` is created and initialized at runtime and can be
 * used globally across the application once initialized.
 *
 * Usage examples include fetching form variables like usernames and passwords,
 * as well as processing referrer data for navigation purposes.
 */
cgibind     * gpCgiBind;

#endif //DIAGNOSE_H
