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
 * @brief Global pointer to the CLog instance used for logging purposes.
 *
 * The gpLog variable serves as a global access point to the overall logging system of the application.
 * It allows different parts of the program to log messages, debugging information, or errors consistently.
 *
 * This global log instance must be initialized before use to ensure logging operations function correctly.
 *
 * @note Be cautious while using global variables as it may lead to coupling of components.
 */
CLog   * gpLog;
#include "osIface.h"
/**
 * @brief Global pointer to an instance of the osIface class.
 *
 * This variable is used to manage OS-level interactions and file operations
 * by providing access to methods defined within the osIface class. The
 * osIface instance is commonly initialized at runtime and used throughout
 * the application to perform tasks such as retrieving all files in a
 * directory or converting a file name to its corresponding path.
 *
 * It is typically instantiated during the initialization phase of the
 * application and remains accessible globally to other components.
 *
 * @note Ensure proper initialization of this variable before usage.
 */
osIface * gpOS;
#include "shared.h"
/**
 * @brief Global pointer to a shared object instance.
 *
 * This global variable provides a pointer to an instance of the `shared` class,
 * which is responsible for managing the shared memory segments and their addressability.
 * It is initialized as `nullptr` and instantiated in various parts of the application
 * to ensure access to shared memory operations.
 *
 * The object is utilized in multiple components of the application such as menu, main,
 * and note-saving functionalities, ensuring a unified reference to shared memory operations.
 */
shared * gpSh = nullptr;
#include "environment.h"
/**
 * @brief Global pointer variable to access the shared environment instance.
 *
 * This variable is intended to provide a global reference to an `environment` instance,
 * facilitating access to shared resources or configurations within the scope
 * of the program. Proper initialization and cleanup of the `gpEnv` instance
 * are the responsibility of the program using it.
 *
 * @note Use caution when modifying or accessing this variable, as improper
 * handling might lead to data inconsistencies or undefined behavior in the program.
 */
environment * gpEnv;
#include "test.h"

#endif //MULTIWARE_VPAD_H
