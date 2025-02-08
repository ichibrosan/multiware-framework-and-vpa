////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/main.h   2025/01/20 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#ifndef MAIN_H
#define MAIN_H
#include "std.h"
//#include "limits.h"
#include "cgicc.h"
using namespace cgicc;
/**
 * @brief Represents a global instance used for managing CGI (Common Gateway Interface) operations.
 *
 * This variable handles CGI-specific functionalities, such as processing client requests
 * and rendering dynamic content for web applications. It is typically utilized in systems
 * that rely on server-side interaction and response generation based on user input or requests.
 *
 * Note: Proper initialization and cleanup of this variable are critical to avoid unexpected behavior
 * during the execution of CGI processes.
 */
Cgicc          * gpCgi;
#include "test.h"
/**
 * @brief Global pointer to an instance of the `test` class.
 *
 * This variable serves as a shared global reference for managing test
 * operations throughout the application. The `test` class provides methods
 * to execute various test sequences, log test results, and ensure the proper
 * configuration of essential shared parameters.
 *
 * It is typically instantiated at the start of the application and can be
 * used to run mandatory or comprehensive test suites. It also supports
 * logging histogram data and debugging output.
 *
 * @note This variable must be properly initialized before use to prevent
 * undefined behavior.
 *
 * @see test
 */
test           * gpTest;
#include "environment.h"
/**
 * @brief Global pointer to the environment instance.
 *
 * This variable holds a reference to the environment or system context,
 * providing access to global functionalities, settings, services, or
 * configurations required across the application. It may be used by various
 * components or modules to interact with shared resources or achieve integration
 * with the system environment.
 *
 * Note:
 * - Ensure proper initialization of the environment before accessing this variable.
 * - Modifying this variable directly may lead to unintended behavior or system instability.
 */
environment    * gpEnv;
#include "shared.h"
/**
 * @brief Global pointer to the shared object.
 *
 * The variable `gpSh` serves as a global pointer referencing a shared object
 * or resource within the application. It is primarily used for shared access
 * and operations performed on the associated entity across different parts
 * of the program.
 *
 * Usage and lifecycle management of `gpSh` should ensure thread safety and
 * proper synchronization mechanisms if the shared resource is accessed
 * concurrently in a multi-threaded environment.
 */
shared         * gpSh;
#include "readCsv.h"
/**
 * @brief Global pointer to a `readCsv` instance.
 *
 * This variable is used to manage and parse CSV data within the application.
 * It is instantiated with a filename and provides access to the parsed
 * data through a matrix-like structure. The instance enables operations
 * such as retrieving specific data points and parsing the entire CSV file.
 *
 * @details Defined in `main.h` and initialized in `login.cpp`. The CSV file
 * is expected to hold rows and columns of data that can be accessed via the
 * class methods or directly through its parsed data members.
 *
 * Example functionalities include:
 * - Parsing a CSV file into a structured data format.
 * - Accessing specific rows and columns within the parsed data.
 * - Retrieving the number of lines in the CSV.
 *
 * @see readCsv
 */
readCsv        * gpCsv;
#include "CLog.hpp"
/**
 * @brief Global pointer to the logging object used for application-wide logging.
 *
 * The gpLog variable is a pointer to an instance of the CLog class, which
 * is responsible for handling logging functionalities in the application.
 * It provides methods for writing messages, errors, and other details to a log.
 *
 * The gpLog is initialized and managed to ensure logging is accessible
 * throughout the application.
 *
 * @note Ensure the gpLog object is properly initialized before use to avoid
 *       null pointer dereferencing. The lifecycle of the logging object must
 *       be managed carefully to prevent resource leaks.
 */
CLog           * gpLog;
#include <cgicc/Cgicc.h>    // the cgicc headers
#include "schemaCompiler.h"
/**
 * @brief Global pointer to a schemaCompiler object.
 *
 * This variable holds the address of a schemaCompiler instance, which is used for managing and
 * validating schema-related operations. The schemaCompiler class provides functionalities such
 * as creating file headers, checking schema validity, and determining the active state of rows
 * or specific types within the schema.
 *
 * The object accessed through this pointer is essential for interacting with schemas in the
 * system and ensuring their proper handling in terms of conditions, types, and file headers.
 */
schemaCompiler * gpSchema;
#include "osIface.h"
/**
 * @brief Global pointer to an instance of the osIface class.
 *
 * This variable is used to interact with the operating system interface
 * through the osIface class. It is typically initialized during the
 * program's startup and is shared across various components for utilizing
 * the functionalities provided by the osIface class.
 *
 * Note:
 * - The osIface class may comprise methods that provide OS-related operations.
 * - It is common practice to ensure the proper instantiation and deletion
 *   of this global variable to avoid memory leaks.
 */
osIface        * gpOS;

#endif //MAIN_H
