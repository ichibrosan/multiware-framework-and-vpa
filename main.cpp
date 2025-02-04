////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/main.cpp 2025/01/11 05:21 //
// Copyright (c) Douglas Wade Goodall. All Rights Reserved.               //
////////////////////////////////////////////////////////////////////////////

#include "main.h"

///////////////////////////////////////
// Allocate pointers to user classes //
///////////////////////////////////////

/******************************************************
 * This is the main entry point of the framework
 * @return Returns EXIT_SUCCESS or EXIT_FAILURE (POSIX)
 ******************************************************/
int main(int argc, char **argv) {
    //std::cout << argv[0] << std::endl;

    gpLog = new CLog(__FILE__,__FUNCTION__);
    gpLog->truncate();

    CLog log(__FILE__,__FUNCTION__);
    log.truncate();

    gpOS  = new osIface();

    gpSh  = new shared();

    gpEnv = new environment();
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

    // Instantiate Prerequisite Class Objects
    gpOS   = new osIface();
    gpTest = new test(false,false);

    gpTest->logHistograms();

    return EXIT_SUCCESS;
}
