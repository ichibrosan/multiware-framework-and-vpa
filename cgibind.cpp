///////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/cgibind.cpp 2025/01/27 02:51 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.        //
// This file is part of the Goodall MultiWare Framework Project.             //
///////////////////////////////////////////////////////////////////////////////

#include "cgibind.h"

cgibind::cgibind()
{

}

/*****************************************************************
 * Fetch form parameter by name
 * @param ssVariableName
 * @return Returns a standard string with the parameter value
 *****************************************************************/
std::string cgibind::get_form_variable(std::string ssVariableName)
{
    std::string ssVariableValue;
    form_iterator name = gpCgi->getElement(ssVariableName);
    if (name != gpCgi->getElements().end()) {
        ssVariableValue = **name;
    }
    return ssVariableValue;
};


/*************************************************
 * Get referrer from Apache2 environment via cgicc
 * @return Returns a standard string with referrer
 *************************************************/
std::string cgibind::get_referrer()
{
    std::string ssHttpReferrer =
        gpCgi->getEnvironment().getReferrer();
    return ssHttpReferrer;
}


/*************************************************
 * Derive referrer path from Apache2's referrer
 * @return Returns a standard string with the path
 *************************************************/
std::string cgibind::get_referrer_path()
{
    std::string ssHttpReferrer =
        gpCgi->getEnvironment().getReferrer();
    std::string ssReferrerPath =
        std::filesystem::path(ssHttpReferrer).remove_filename();
    return ssReferrerPath;
}


/**********************************************
 * Derive referrer file from Apache2's referrer
 * @return Returns standard string filename
 **********************************************/
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