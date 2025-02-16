////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/main.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

///////////////////////////////////////
// Allocate pointers to user classes //
/*************************************************/

/******************************************************
 * This is the main entry point of the application.
 * It initializes critical components, checks for system
 * requirements, and ensures necessary preconditions
 * are met before running the program's core.
 *
 * @param argc The count of command-line arguments passed.
 * @param argv The array of command-line arguments passed.
 * @return Returns EXIT_SUCCESS if execution completes successfully,
 *         or EXIT_FAILURE if there is an error preventing startup.
 ******************************************************/
int main(int argc, char **argv) {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

    CLog log(__FILE__,__FUNCTION__);
    log.truncate();



    gpEnv->extract_username();

    if(! gpEnv->is_curl_present()) {
        log.write("ERROR: curl not installed. Please install the "
                  "\"curl\" package and re-run this software.");
        exit(EXIT_FAILURE);
    }

    if(! gpEnv->is_netstat_present()) {
        log.write("ERROR: netstat not installed. Please install the "
                  "\"net-tools\" package and re-run this software.");
        exit(EXIT_FAILURE);
    }

    gpTest = new test(false,false);

    gpTest->logHistograms();

    return EXIT_SUCCESS;
}
