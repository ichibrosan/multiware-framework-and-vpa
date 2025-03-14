////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnose.cpp 2025/02/19                  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"


/**
 * @brief Entry point of the diagnose application.
 *
 * The main function is responsible for initializing necessary components, including
 * system logging and application-specific configurations. It performs the following operations:
 * - Initializes the global system logger `gpSysLog` object.
 * - Creates an instance of the `mwfw2` class to manage CGI and debug-related functionality.
 * - Outputs HTTP headers and a basic "Hello World!" message to the standard output if necessary.
 * - Instantiates a `test` object to facilitate further testing and diagnostic operations.
 * - Executes a system command to capture network interface information and logs it in temporary files.
 *
 * @return `EXIT_SUCCESS` when the program terminates successfully.
 */
int main() {
    gpSysLog = new CSysLog();
    here;
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    here;

    std::cout << "Content-type:\ttext/html\n\n" << std::endl;
    std::cout << "Hello World!!" << std::endl;
    // int iHandle    =
    //    atoi(gpCgiBind->get_form_variable("handle").c_str());

    gpTest = new test(true,pMwFw->isCGI());
    //gpSchema = new schema("login.csv");
    //gpSchema->gen_from_schema(iHandle);

    system("sudo ip a >/tmp/redir-test.stdout 2>/tmp/redir-test.stderr");
    return EXIT_SUCCESS;
}
