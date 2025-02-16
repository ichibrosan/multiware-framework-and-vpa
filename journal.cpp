///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/journal.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * The main function initializes necessary components for an application, including logging, environment settings,
 * schema processing, and dashboard display. It also processes input data from CGI form variables.
 *
 * @return An integer value which signifies the program's exit status.
 *         Returns EXIT_SUCCESS if the program executes successfully.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpCgiBind->get_form_variable("username");
    std::string ssPassword = gpCgiBind->get_form_variable("pwname");
    gpSchema    = new schema("journal.csv");
    std::vector<std::vector<std::string>> journal_params =
            {
        {"journal_style","journal_style"},
        {"anothertest", "is this the style problem?"},
        {"test", "does this thing actually work"}
            };

    gpDash      = new dashboard(handle,LOGOUT | MENU,__FILE__,
        ssUsername,ssPassword);
    gpSchema->gen_from_schema(handle,
    journal_params);
    return EXIT_SUCCESS;
}
