////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/menu.cpp  2025/01/14  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

/**
 * The main function serves as the entry point of the program. It initializes
 * various components including logging, CGI processing, environment variables,
 * schema handling, and dashboard setup. It handles CGI detection and outputs
 * HTML headers accordingly. Schema generation and debugging outputs are provided
 * when in CGI mode.
 *
 * @return Returns 0 to indicate successful program execution.
 */
int main() {
  mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
  //char * ptr = getenv("SERVER_PORT");
  //bool bCGI = false;
  //if(nullptr != ptr) {
//    bCGI = true;
//    std::cout << "Content-type:\ttext/html\n\n" << std::endl;
//  }

  gpSchema = new schema("user-menu.csv");
  int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
  std::string ssUsername = gpCgiBind->get_form_variable("username");
  std::string ssPassword = gpCgiBind->get_form_variable("pwname");
  gpDash      = new dashboard(handle,JOURNAL | LOGOUT,__FILE__,
                              ssUsername,ssPassword);
  gpSchema->gen_from_schema(HANDLE_NA);
  if(pMwFw->isCGI()) {
    gpHtml->dump_schema();
    gpHtml->dump_shm_vars();
    gpHtml->dump_env_vars();
  }
  return 0;
}
////////////////////
// eof - menu.cpp //
////////////////////
