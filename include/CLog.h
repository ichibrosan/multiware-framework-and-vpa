////////////////////////////////////////////////////////////////////
// ~/public_html/fw/CLog.hpp 2025-07-16 08:16 dwg -               //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"


/******************************************************************************************
 * @class CLog
 * @brief A class designed to handle logging operations within an application.
 *
 * The CLog class provides functionality for recording and managing logs.
 * It enables writing debug, error, or informational messages to a log file
 * or console, simplifying the troubleshooting and monitoring process.
 *
 * It typically includes functionalities like:
 * - Writing log messages of different severity levels.
 * - Managing log formats (e.g., timestamps, log level, message content).
 * - Controlling the output destination (file, console, etc.).
 * - Configuring settings like log retention, file rotation, or verbosity levels.
 *
 * Thread safety and performance considerations are dependent on specific implementation details.
 ******************************************************************************************/
class CLog
{
	/**
	 * @brief A variable that typically stores a fully qualified file system path as a null-terminated string.
	 *
	 * This variable is intended to hold file system paths that include a detailed specification,
	 * including drive letters (if applicable), directories, and filenames, ensuring clarity and uniqueness
	 * of the file system location within a given environment.
	 *
	 * The naming convention "m_sz" suggests that this is a member variable (m_) intended to hold a string (sz),
	 * likely represented as a C-style string. Users of this variable should ensure that its content adheres
	 * to the expected format of a fully qualified file system path and avoid overwriting it with incomplete
	 * or malformed paths.
	 *
	 * @note Adequate memory management should be maintained to prevent buffer overflow or unexpected truncation
	 * when assigning values to this variable.
	 */
	// This is the fully qualified filespec of
	// the logfile, which is used on each access
	// to open the file for appending.
	char m_szFQFS[FILENAME_MAX];

public:
	/**
	 * Logs a message with a specified logging level.
	 *
	 * @param level The logging level, indicating the severity or importance of the log message.
	 * @param message The message that needs to be logged.
	 * @return A boolean indicating whether the log operation succeeded (true) or failed (false).
	 */
	// This is the prototype of the CLog class
	// constructor. It opens a log file and saves
	// the file descriptor in member data for
	// subsequent calls to the write function.
	CLog(const char* pszFileName, const char* pszFunctionName);

	/**
	 * Truncates the current log file by clearing its contents and writing
	 * a header separator line to indicate the start of a new log session.
	 *
	 * This method ensures the log file is reset, ready to accept new data,
	 * while preserving a clear demarcation of sessions with a separator.
	 *
	 * @return An integer code indicating the outcome of the operation:
	 *         - RETURN_SUCCESS (e.g., 0) on successful truncation.
	 *         - RETURN_FAILURE (e.g., non-zero) if the truncation fails
	 *           (e.g., unable to open the log file).
	 */
	// This is the prototype of the truncate function
	// whose purpose is to delete the current contents
	// in preparation for new data.
	int truncate();

	/**
	 * Retrieves the maximum value in an integer array.
	 *
	 * @param array The array of integers to be processed.
	 * @param size The size of the array.
	 * @return The maximum value in the array. If the array is empty, returns a default minimum value or error indicator.
	 */
	// This is the prototype of the logging function
	// a string is passed to the write function and
	// it is subsequently written into the log file
	int write(const char*);

	/**
	 * Writes a given message to the log file without including a timestamp.
	 *
	 * This method appends the provided message to the log file specified by the
	 * internal member variable `m_szFQFS`. It is designed to write raw strings
	 * without prepending or appending any timestamps. The log file is opened in
	 * append mode, and the message is written to the file as-is. If any errors
	 * occur during file operations (e.g., opening, writing, or closing the file),
	 * an appropriate failure status is returned.
	 *
	 * @param szMessage The message string to be written to the log file. It must
	 *                  not be null and must point to a valid, non-empty string.
	 * @return RETURN_SUCCESS if the message is successfully written to the log file;
	 *         otherwise, RETURN_FAILURE is returned if an error occurs during the
	 *         operation.
	 */
	int writesanstime(const char*);

	/**
	 * @brief Converts a boolean value to a named string representation.
	 *
	 * This function maps the boolean value `true` to the string "true"
	 * and the boolean value `false` to the string "false".
	 *
	 * @param value The boolean input to be converted to a named string.
	 * @return A string representation of the boolean value, either "true" or "false".
	 */
	int namedBool(const char*, bool);

	/**
	 * Logs a message that includes a name and a double value into the log file. The
	 * message is appended with a timestamp and formatted as `<timestamp> <name> <value>`.
	 * Ensures the log file is correctly opened, written to, and closed.
	 *
	 * @param pszName The name or identifier associated with the value being logged.
	 *                Must not be null.
	 * @param value The double value to be logged alongside the identifier.
	 * @return Returns RETURN_SUCCESS (typically 0) on successful logging, or
	 *         RETURN_FAILURE (typically non-zero) if the logging operation fails.
	 */
	int namedDouble(const char*, double);

	/**
	 * Returns the integer associated with the given name.
	 *
	 * This method retrieves an integer value based on its corresponding name,
	 * which is typically stored within the method's implementation or an
	 * associated data structure.
	 *
	 * @param name The name as a string used to retrieve the associated integer.
	 * @return The integer value associated with the given name.
	 */
	int namedInt(const char*, int);

	/**
	 * Constructs a formatted string by combining a provided name with a specific value.
	 *
	 * @param name The string representing the name or identifier.
	 * @param value The integer value to be combined with the name.
	 * @return A concatenated string that blends the given name and value.
	 */
	int namedString(const char*, const char*);

	/**
	 * Logs a formatted message with a timestamp to a file. The method formats
	 * input using a printf-style format string and takes a variable number
	 * of arguments. The formatted message is prefixed with a timestamp and
	 * appended to the log file.
	 *
	 * @param pszFormat The format string, using printf-style formatting.
	 *                  This should not be null or empty.
	 * @return An integer indicating the success or failure of the operation.
	 *         Returns RETURN_SUCCESS on success, and RETURN_FAILURE on failure
	 *         (e.g., if the file could not be written).
	 */
	// This is the prototype of the varargs version
	// of the logging function. A format string and
	// some parameters are passed in and formatted
	// before being written to the log file..
	int writev(const char*, ...);

	/**
	 * Generates a timestamp in the format "YYYY-MM-DD_HH:MM:SS" and stores the result in the provided buffer.
	 *
	 * @param pszDest A pointer to a character buffer where the generated timestamp will be stored.
	 *                This buffer should be pre-allocated and large enough to hold the resulting string.
	 */
	void getTimeDateStamp(char*);
};

////////////////////
// eof - CLog.hpp //
////////////////////
