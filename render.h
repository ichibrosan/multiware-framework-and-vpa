///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/render.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////
#ifndef MULTIWARE_RENDER_H
#define MULTIWARE_RENDER_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
/**
 * @brief Pointer to a global instance of the Cgicc class.
 *
 * This variable is used to manage CGI (Common Gateway Interface) interactions
 * across various modules. It provides functionalities to process CGI requests,
 * parse HTML form data, and interact with web-server-specific environment
 * variables and headers.
 *
 * In the application, gpCgi is initialized as a new instance of the Cgicc
 * class, and serves as a central point for CGI-related operations, such as
 * retrieving form variables sent from web clients.
 *
 * Usage Scope:
 * - Used in multiple modules including `notesave`, `menu`, `journal`, and `render`
 *   to handle web-based interactions such as reading form inputs.
 *
 * Memory Management:
 * - Dynamically allocated using `new`.
 * - Ensure proper cleanup to prevent memory leaks.
 */
Cgicc       * gpCgi;
#include "CLog.hpp"
/**
 * A global pointer to an instance of the CLog class used for logging operations.
 *
 * gpLog is allocated and initialized elsewhere in the program and is used globally
 * to handle logging functionality such as writing log messages, error reporting,
 * or debugging output. The lifecycle and ownership of gpLog should be managed
 * properly to ensure resource cleanup.
 */
CLog        * gpLog;
#include "cgihtml.h"
/**
 * A global pointer to a cgihtml structure.
 *
 * This variable is used to manage and manipulate the HTML content
 * generated or handled in Common Gateway Interface (CGI) applications.
 * It is typically initialized and used throughout the CGI program
 * to store information regarding HTML generation, parsing,
 * or other related operations.
 *
 * The cgihtml structure generally provides functionality for
 * managing HTML forms, processing CGI input, and handling output generation.
 *
 * Proper initialization and cleanup of this pointer are necessary to ensure
 * the stability and correctness of the application.
 */
cgihtml     * gpHtml;
#include "environment.h"
/**
 * @brief Pointer to the global environment instance.
 *
 * This variable serves as a reference to the current environment
 * configuration or state used throughout the application. It is
 * typically initialized during application startup and provides
 * access to shared resources or environment-specific settings.
 *
 * @note Ensure that the environment is properly initialized before
 * using this variable and avoid modifying it directly unless necessary.
 */
environment * gpEnv;
#include "osIface.h"
/**
 * @brief Pointer to an osIface object used for interfacing with the operating system abstraction layer.
 *
 * This variable provides access to the operating system abstraction functionalities
 * defined by the osIface interface. It acts as a global reference to the OS-specific
 * implementation, enabling interaction with OS-level operations such as task
 * management, synchronization, and other system services.
 *
 * The gpOS variable should be initialized with an appropriate implementation of
 * osIface before use. Improper initialization or null access may result in undefined behavior.
 */
osIface     * gpOS;
#include "password.h"
/**
 * @brief A global pointer to a password object.
 *
 * This variable is typically used to reference and manage the application's
 * password-related functionalities. It allows access to the methods and attributes
 * of the password class, such as generating secure passwords, performing lookups,
 * and managing associated data.
 *
 * @note Proper memory management should be ensured when using gpPassword,
 * including initialization and deallocation, to avoid memory leaks
 * or undefined behavior when accessing the pointer.
 */
password    * gpPassword;
#include "readCsv.h"
/**
 * @brief Pointer to an instance of the readCsv class.
 *
 * This variable represents a dynamically allocated object of the `readCsv` class
 * used for handling CSV file operations, such as reading, parsing, and retrieving data.
 * The `gpCsv` pointer provides access to various methods and attributes of the `readCsv` class.
 *
 * Typical operations performed through this pointer include:
 * - Loading and parsing CSV file contents.
 * - Retrieving specific data from the parsed CSV.
 * - Accessing metadata, such as the number of rows or columns in the file.
 *
 * Ownership:
 * - Ensure proper initialization and allocation of the object before use.
 * - Properly release or delete the object to avoid memory leaks.
 *
 * @note The `readCsv` class must be properly defined and included in the source file
 *       for the `gpCsv` pointer to function correctly.
 */
readCsv     * gpCsv;
#include "schema.h"
/**
 * @brief Represents the schema for a general-purpose database or structure.
 *
 * This variable holds the schema definition, which may include the structure, fields,
 * types, and constraints necessary to define and validate data. It is used to
 * ensure consistency and integrity of the data representation throughout the system.
 *
 * The content and format of this schema are determined by the specific requirements
 * of the application and may vary depending on its use case.
 */
schema      * gpSchema;
#include "shared.h"
/**
 * @var gpSh
 * @brief Pointer to an instance of the `shared` class.
 *
 * The `gpSh` variable is a global pointer used to manage shared memory
 * segments in the application. It serves as an interface to the
 * shared memory functionality provided by the `shared` class,
 * enabling interaction with and management of key shared memory features.
 *
 * This global pointer is initialized and utilized in various parts of
 * the application (e.g., `notesave.cpp`, `menu.cpp`, `login.cpp`) to
 * establish addressability to shared memory for different execution contexts.
 */
shared      * gpSh;
#include "cgibind.h"
/**
 * Global pointer to an instance of the `cgibind` class.
 *
 * The `gpCgiBind` variable is used to manage and facilitate interactions with
 * CGI (Common Gateway Interface) input, including retrieving form variables
 * submitted by users. It leverages the functionality provided by the `cgibind`
 * class, such as accessing CGI input data like form variables, HTTP referrer
 * information, and related properties.
 *
 * This variable is initialized as a global variable and is used across the application
 * for various form handling and processing purposes. It enables efficient retrieval
 * of data submitted to the application through HTTP forms in a web environment.
 *
 * Note: Ensure that the variable is properly initialized before accessing its methods
 * to avoid runtime errors.
 */
cgibind     * gpCgiBind;
#include "dashboard.h"
/**
 * @brief Pointer to a dashboard object.
 *
 * This variable is a global pointer to an instance of the `dashboard` class, allowing
 * access to the dashboard's functionalities and properties throughout the application.
 * It is used to manage and interact with dashboard-related features.
 */
dashboard   *gpDash;
#include "cgibind.h"
/**
 * @var gpCgiBind
 *
 * Pointer to a globally instantiated `cgibind` object.
 *
 * This variable is used to manage and interact with CGI input data in the application.
 * It allows access to functionalities provided by the `cgibind` class, such as retrieving
 * CGI form variables and HTTP referrer information. The instance is initialized during the
 * program's execution to handle specific CGI-related operations.
 */
extern cgibind     * gpCgiBind;
#endif //MULTIWARE_RENDER_H
////////////////////
// eof - render.h //
////////////////////
