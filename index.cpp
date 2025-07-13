////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/index.cpp 2025/07/13  06:11 dwg -        //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

/**
 * @file index.cpp
 * @brief Main entry point for the framework application
 * @author Douglas Wade Goodall
 * @date 2025/07/13
 * @copyright Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.
 * 
 * @details
 * This file contains the main entry point for the framework application.
 * It initializes the mwfw2 framework and processes a schema file to generate
 * application components or configurations based on the schema definition.
 * 
 * The application follows a schema-driven approach where configuration and
 * behavior are defined through CSV schema files that are processed at runtime.
 * 
 * @dependencies
 * - mwfw2.h: Framework initialization and management
 * - schema class: Schema processing and generation capabilities
 * - Standard C++ memory management utilities
 * 
 * @usage
 * This executable should be run with the schema file (index.csv) present
 * in the working directory. The framework will automatically process the
 * schema and generate the necessary components.
 */

#include "mwfw2.h"

/**
 * @brief Main entry point for the application
 * 
 * This function serves as the primary entry point for the framework application.
 * It performs the following operations:
 * 1. Initializes the mwfw2 framework with debugging information
 * 2. Creates a schema processor for handling CSV-based configuration
 * 3. Processes the schema file to generate application components
 * 
 * @return int Returns 0 upon successful execution, non-zero on failure
 * 
 * @note
 * The framework object is created with the current file name (__FILE__) and 
 * function name (__FUNCTION__) for debugging and logging purposes.
 * 
 * @details
 * The schema processor is initialized with a predefined schema file name
 * (index.csv) and uses the gen_from_schema() method with handle parameter 0
 * to process the schema data. This typically generates HTML, configuration
 * files, or other application components based on the schema definition.
 * 
 * @see mwfw2 class for framework initialization details
 * @see schema class for schema processing capabilities
 * @see gen_from_schema() method for schema generation process
 * 
 * @exception
 * This function does not explicitly handle exceptions. Any exceptions thrown
 * by the framework or schema processor will propagate up and terminate the
 * application unless caught by a higher-level exception handler.
 * 
 * @memory
 * Uses smart pointers (std::unique_ptr) for automatic memory management.
 * All allocated resources are automatically cleaned up when the function
 * exits, preventing memory leaks.
 * 
 * @thread_safety
 * This function is not thread-safe and should only be called from the main
 * thread as the application entry point.
 */
int main()
{
    /** @brief Schema filename constant for configuration processing */
    const std::string SCHEMA_FILENAME = "index.csv";

    /** 
     * @brief Framework instance for application initialization
     * 
     * Creates the main framework object with file and function information
     * for debugging and logging purposes. The framework handles core
     * application functionality including configuration management,
     * logging, and resource initialization.
     */
    auto framework = std::make_unique<mwfw2>(__FILE__, __FUNCTION__);

    /** 
     * @brief Schema processor instance for CSV-based configuration
     * 
     * Creates a schema processor that reads and processes the specified
     * CSV schema file. The schema defines the structure and behavior
     * of various application components.
     */
    auto schemaProcessor = std::make_unique<schema>(SCHEMA_FILENAME);

    /**
     * @brief Process the schema file and generate components
     * 
     * Invokes the schema generation process with handle parameter 0.
     * This typically generates HTML pages, configuration files, or
     * other application components based on the schema definition.
     * The handle parameter (0) indicates the default processing mode.
     */
    schemaProcessor->gen_from_schema(0);

    // Successful completion
    return 0;
}
