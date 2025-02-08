//
// Created by doug on 1/20/25.
//

#ifndef FW_TEST4_H
#define FW_TEST4_H
#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
using namespace cgicc;

#include "environment.h"
/**
 * @brief Global pointer to the environment object.
 *
 * This global variable is used to provide access to the application's
 * environment context. The application must ensure that gpEnv is
 * properly initialized and managed during the runtime. It is typically
 * defined within the respective implementation file.
 *
 * @note Accessing or modifying gpEnv without proper initialization
 * may result in undefined behavior.
 */
extern environment * gpEnv;

#include "cgibind.h"
/**
 * A global pointer to an instance of the `cgibind` class.
 *
 * This variable is used to interact with CGI input data, providing functionality
 * for retrieving form variables and parsing HTTP referrer information. It is
 * instantiated and utilized in multiple applications where CGI functionality
 * is required.
 *
 * The `gpCgiBind` object allows retrieval of user input passed through web
 * application forms using its methods such as `get_form_variable`. It also
 * facilitates working with referrer-related data, streamlining CGI input
 * processing in web server applications.
 */
extern cgibind * gpCgiBind;

#include "cgihtml.h"
/**
 * @brief Global pointer to an instance of the cgihtml object, used to handle
 *        CGI processing and HTML generation in the application.
 *
 * This variable provides access to cgihtml functionalities, enabling the program
 * to dynamically create and submit HTML content and process CGI inputs. It is
 * used across the application for seamless interaction with web-based interfaces.
 *
 * Note: Proper initialization and management of this variable are required to
 * ensure the correct functioning of CGI and HTML handling functionalities.
 */
extern cgihtml * gpHtml;

#include "osIface.h"

#include "CLog.hpp"
/**
 * @brief Global pointer to the logging instance.
 *
 * The gpLog variable is utilized as a global access point to the
 * logging mechanism within the application. It is used for logging
 * messages, warnings, errors, or other relevant data throughout
 * various components of the program. This shared resource allows
 * for consistent logging behavior and output format, enabling
 * centralized management of logs.
 *
 * Proper care must be taken when accessing or modifying this
 * object in multithreaded environments to avoid potential race
 * conditions or undefined behavior.
 */
extern CLog   *gpLog;

#include "shared.h"
/**
 * @brief Pointer to a `shared` object used for managing shared memory operations.
 *
 * The `gpSh` variable serves as a global instance of the `shared` class. It is initialized
 * as a new `shared` object during the program's execution. The shared object handles
 * the establishment of addressability to shared memory segments and facilitates inter-process
 * memory sharing.
 *
 * @note This variable is utilized across multiple modules, including `notesave.cpp`,
 * `journal.cpp`, and `render.cpp`, to provide shared memory functionality. Proper
 * initialization and cleanup are critical to prevent memory leaks or access violations.
 */
extern shared *gpSh;

#endif //FW_TEST4_H
