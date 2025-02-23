////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/prefs.cpp 2025/02/23 11:28 dwg           //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
#include "vpadDefs.h"
using namespace std;
#include "stylist.h"
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

const char * vpad_req_names[] = {
    "VERSION",
    "AUTH",
    "PARMS",
    "STATUS",
    "TERM"
};

const char * vpad_type_names[] = {
    "NONE",
    "INT",
    "STRING",
    "FLOAT",
    "BOOL"
};

class preferences {
public:
    preferences();
};

/**************************************************************************************
 * @brief Entry point of the prefs CGI script.
 *
 *
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of character pointers listing all command-line
 *              arguments.
 * @return Returns `EXIT_SUCCESS` (0) upon successful execution or an error
 * code in case of failure.
 **************************************************************************************/
int
main(int argc,char ** argv) {
    auto * pMwfw = new mwfw2(__FILE__,__FUNCTION__);

    // printf("prefs Copyright (c) 2025 "
    //         "Douglas Wade Goodall. "
    //         "All Rights Reserved.\n");
    gpSchema = new schema("prefs.csv");
    gpSchema->gen_from_schema(0);

}