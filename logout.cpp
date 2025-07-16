////////////////////////////////////////////////////////////////////
// ~/public_html/fw/logout.cpp 2025-07-15 18:16 dwg -             //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

char* gpszServerPort;

/**
 * @brief A global pointer to a character string representing the server port.
 *
 * gpszServerPort is used to store a dynamically allocated or assigned
 * string containing the server port number. This variable is intended
 * for use in scenarios where the server port needs to be globally
 * accessible within the application.
 *
 * Proper memory management is required when handling the content
 * of this pointer to avoid memory leaks, particularly when it is
 * reassigned or deallocated.
 */

/**
 * Main program entry point. Initializes necessary components, processes
 * CGI environment if present, invalidates user authentication credentials,
 * and generates schema data based on input.
 *
 * @return EXIT_SUCCESS upon successful execution.
 */
int main()
{
       mwfw2* pMwFw = new mwfw2(__FILE__, __FUNCTION__);
       int iHandle = atoi(gpCgiBind->get_form_variable("handle").c_str());

       /**
        * Invalidate authentication information in shared
        */
       memset(gpSh->m_pShMemng->creds[iHandle].szAuthUserName, 0,
              sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthUserName));
       memset(gpSh->m_pShMemng->creds[iHandle].szAuthFirstName, 0,
              sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthFirstName));
       memset(gpSh->m_pShMemng->creds[iHandle].szAuthLastName, 0,
              sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthLastName));
       memset(gpSh->m_pShMemng->creds[iHandle].szAuthUUID, 0,
              sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthUUID));
       gpSh->m_pShMemng->creds[iHandle].iAuthHandle = 0;

       std::string ssHttpReferrer = gpCgi->getEnvironment().getReferrer();
       std::string ssReferrerPath =
              std::filesystem::path(ssHttpReferrer).remove_filename();
       std::string ssReferrerFile =
              ssHttpReferrer.substr(ssReferrerPath.length(),
                                    ssHttpReferrer.length());

       gpSchema = new schema("index.csv");
       gpSchema->gen_from_schema(1);


       return EXIT_SUCCESS;
}
