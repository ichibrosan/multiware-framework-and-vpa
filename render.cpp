///////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/render.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.    //
///////////////////////////////////////////////////////////////////////////
#include "render.h"

/**
 *
 * @return This is the CGI main entry point
 */
int main() {
    char *ptr = getenv("SERVER_PROTOCOL");
    bool bCGI = false;
    if (nullptr != ptr) {
        bCGI = true;
        std::cout << "Content-type:\ttext/html\n\n" << std::endl;
    }
    gpLog       = new CLog(__FILE__, __FUNCTION__);
    gpLog->truncate();
    gpSh        = new shared();
    gpCgi       = new Cgicc();
    gpCgiBind   = new cgibind();
    std::string ssSchema =
        gpCgiBind->get_form_variable("schema");
    int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpCgiBind->get_form_variable("username");
    std::string ssPassword = gpCgiBind->get_form_variable("pwname");

    gpEnv       = new environment();
    gpSchema    = new schema(ssSchema);

    if (0 == strcmp("no", gpCgiBind->get_form_variable("dash").c_str()))
    {
        ;
    }
    else
    {
        gpDash      = new dashboard(handle,JOURNAL | LOGOUT,__FILE__,
        ssUsername,ssPassword);
    }

    std::string ssStyle =
        gpCgiBind->get_form_variable("style");

    std::vector<std::vector<std::string>> render_params =
    {
        {"form_style",ssStyle},
        {"loaded_text", ""}
    };

    gpSchema->gen_from_schema(handle,render_params);
    return EXIT_SUCCESS;
}
