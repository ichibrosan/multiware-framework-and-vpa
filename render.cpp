////////////////////////////////////////////////////////////////////
// ~/public_html/fw/render.cpp 2025-07-15 18:16 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief The main entry point of the application.
 *
 * This function initializes various components required for the
 * application, including environment setup, CGI handling, schema
 * generation, and optional dashboard creation. It also handles CGI
 * server protocol checks and form input parameters for application
 * configuration.
 *
 * @return An integer status code, where EXIT_SUCCESS indicates successful
 *         execution.
 */
int main()
{
    mwfw2* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    std::string ssSchema =
        gpCgiBind->get_form_variable("schema");
    int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpCgiBind->get_form_variable("username");
    std::string ssPassword = gpCgiBind->get_form_variable("pwname");

    gpSchema = new schema(ssSchema);

    std::string ssStyle =
        gpCgiBind->get_form_variable("style");

    std::vector<std::vector<std::string>> render_params =
    {
        {"form_style", ssStyle},
        {"loaded_text", ""}
    };

    if (0 == strcmp("no", gpCgiBind->get_form_variable("dash").c_str()))
    {
        gpSchema->gen_from_schema(handle,
                                  render_params);
    }
    else
    {
        gpSchema->gen_from_schema(handle,
                                  JOURNAL | LOGOUT,
                                  __FILE__,
                                  ssUsername,
                                  ssPassword,
                                  render_params);
    }

    return EXIT_SUCCESS;
}
