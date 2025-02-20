///////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/devo/public_html/fw/cgibind.cpp 2025/01/27 02:51 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.        //
// This file is part of the Goodall MultiWare Framework Project.             //
///////////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

/**
 * Default constructor for the `cgibind` class.
 * Initializes an instance of the `cgibind` class.
 *
 * @return A new instance of the `cgibind` class.
 */
cgibind::cgibind()
{

}

/************************************************************************
 * Retrieves the value of a form variable from the CGI input based on the
 * given variable name. This method checks the incoming CGI form data for
 * a variable matching the specified name and returns its value. If the
 * variable is not found, an empty string is returned.
 *
 * @param ssVariableName The name of the form variable to retrieve.
 * @return The value of the specified form variable as a string. If the
 *         variable is not present in the form data, returns an empty string.
 */
std::string cgibind::get_form_variable(std::string ssVariableName)
{
    std::string ssVariableValue;
    form_iterator name = gpCgi->getElement(ssVariableName);
    if (name != gpCgi->getElements().end()) {
        ssVariableValue = **name;
    }
    return ssVariableValue;
};


/**
 * Retrieves the HTTP referrer for the current CGI-based request.
 *
 * This method accesses the CGI environment to obtain the value of the
 * HTTP referrer, which indicates the address of the webpage that linked
 * to the requested resource.
 *
 * @return A string containing the HTTP referrer of the current request.
 *         If no referrer is available, an empty string is returned.
 */
std::string cgibind::get_referrer()
{
    std::string ssHttpReferrer =
        gpCgi->getEnvironment().getReferrer();
    return ssHttpReferrer;
}


/**
 * Extracts the directory path portion of the HTTP referrer URL.
 *
 * This method retrieves the HTTP referrer from the CGI environment and removes
 * the filename component from the path, leaving only the directory portion.
 *
 * @return A string containing the directory path of the HTTP referrer. If the
 *         referrer is invalid or unavailable, an empty string may be returned.
 */
std::string cgibind::get_referrer_path()
{
    std::string ssHttpReferrer =
        gpCgi->getEnvironment().getReferrer();
    std::string ssReferrerPath =
        std::filesystem::path(ssHttpReferrer).remove_filename();
    return ssReferrerPath;
}


/**
 * Extracts and returns the file name component from the HTTP referrer URL.
 *
 * This method processes the HTTP referrer obtained from the CGI environment
 * by isolating the file name part of the URL. This is achieved by removing
 * the directory path portion of the referrer.
 *
 * @return The file name component of the HTTP referrer URL as a std::string.
 *         If the HTTP referrer is invalid or unavailable, an empty string
 *         is returned.
 */
std::string cgibind::get_referrer_file()
{
    std::string ssHttpReferrer = gpCgi->getEnvironment().getReferrer();
    std::string ssReferrerPath =
        std::filesystem::path(ssHttpReferrer).remove_filename();
    std::string ssReferrerFile =
        ssHttpReferrer.substr(
            ssReferrerPath.length(),
            ssHttpReferrer.length());
    return ssReferrerFile;
}

///////////////////////
// eof - cgibind.cpp //
///////////////////////
