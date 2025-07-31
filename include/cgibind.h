////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cgibind.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include "mwfw2.h"

/**
 * @class cgibind
 * @brief Provides an interface for handling CGI form variables and HTTP
 * referrer parsing. The cgibind class is designed to interact with CGI
 * environment variables, allowing extraction of form data submitted via
 * HTTP requests as well as analyzing information about the referrer
 * (the source of a web request).
 */
class cgibind {

/**
 * Default constructor for the `cgibind` class.
 * Initializes an instance of the `cgibind` class.
 * @return A new instance of the `cgibind` class.
 */
public:
    cgibind();

	/**
	 * Retrieves the value of a form variable from CGI input based on the
	 * given variable name.
	 *
	 * @param ssVariableName The name of the variable to retrieve from the
	 * form data.
	 * @return The value of the specified form variable as a string. If the
	 * variable is not found,
	 *         an empty string is returned.
	 */
	std::string get_form_variable(std::string ssVariableName);

	/**
	 * Retrieves the referrer of the current HTTP request.
	 *
	 * The method extracts the HTTP referrer information from the CGI
	 * environment
	 * and returns it as a string.
	 *
	 * @return A string containing the HTTP referrer of the current request.
	 */
	std::string get_referrer();

	/**
	 * Retrieves the directory path portion of the HTTP referrer URL.
	 *
	 * This method extracts the HTTP referrer using the CGI environment and
	 * remove the filename portion of the path, returning only the directory
	 * path.
	 *
	 * @return A string representing the path portion of the HTTP referrer URL.
	 *         If the HTTP referrer is invalid or unavailable, the returned
	 *         path could be empty.
	 */
	std::string get_referrer_path();

	/**
	 * Extracts and returns the file name component from the HTTP referrer URL.
	 * This method processes the HTTP referrer obtained via the CGI environment
	 * to isolate the file name part by removing the path portion of the URL.
	 *
	 * @return The file name component of the HTTP referrer URL as a
	 * std::string.
	 */
	std::string get_referrer_file();

};

/////////////////////
// eof - cgibind.h //
/////////////////////
