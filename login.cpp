////////////////////////////////////////////////////////////////////
// ~/public_html/fw/login.cpp 2025-07-15 18:16 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

/**
 * @file login.cpp
 * @brief User authentication and authorization module for the framework
 * @author Douglas Wade Goodall
 * @date 2025/02/19
 * @copyright Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.
 * 
 * @details
 * This module handles user authentication, authorization, and session management
 * for the web framework application. It processes login credentials, validates
 * users against a CSV-based password database, and generates appropriate
 * user interfaces based on authentication levels.
 * 
 * The authentication system supports multiple user roles (admin, devo, user)
 * with different access levels and menu configurations. It also handles
 * debugging options for displaying schema information, environment variables,
 * and shared memory variables.
 * 
 * @dependencies
 * - mwfw2.h: Main framework header with global objects and utilities
 * - readCsv class: CSV file parsing for password database
 * - cgiBind class: CGI form variable processing
 * - password class: Password validation and user lookup
 * - schema class: Dynamic UI generation based on user roles
 * - Various global objects (gpCsv, gpCgiBind, gpPassword, gpSchema, etc.)
 * 
 * @security
 * This module implements basic authentication mechanisms. Passwords are
 * stored in plaintext in the CSV file, which may not be suitable for
 * production environments requiring enhanced security.
 * 
 * @usage
 * This executable is typically invoked as a CGI script by a web server
 * when users submit login credentials through a web form.
 */

#include "mwfw2.h"

int main()
{
    mwfw2* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    std::string ssActive;
    std::string ssUsername;
    std::string ssPassword;
    std::string ssAuthLevel;
    std::string ssFirstName;
    std::string ssLastName;
    std::string ssDescript;

    gpCsv = new readCsv("passwd.csv");
    gpCsv->parseData();

    std::string ssUsernameX      = gpCgiBind->get_form_variable("username");
    std::string ssPasswordX      = gpCgiBind->get_form_variable("pwname");

    std::string ssbDisplaySchema = gpCgiBind->get_form_variable(
        "bDisplaySchema");
    if (ssbDisplaySchema == "true")
    { gpSh->m_pShMemng->bDisplaySchema = true;
    }
    if (ssbDisplaySchema == "false")
    { gpSh->m_pShMemng->bDisplaySchema = false;
    }

    std::string ssbDisplayEnvVars = gpCgiBind->get_form_variable(
        "bDisplayEnvVars");
    if (ssbDisplayEnvVars == "true")
    { gpSh->m_pShMemng->bDisplayEnvVars = true;
    }
    if (ssbDisplayEnvVars == "false")
    { gpSh->m_pShMemng->bDisplayEnvVars = false;
    }

    std::string ssbDisplayShmVars = gpCgiBind->get_form_variable(
        "bDisplayShmVars");
    if (ssbDisplayShmVars == "true")
    { gpSh->m_pShMemng->bDisplayShmVars = true;
    }
    if (ssbDisplayShmVars == "false")
    { gpSh->m_pShMemng->bDisplayShmVars = false;
    }

    int handle =
        gpPassword->lookup_username_password(ssUsernameX, ssPasswordX);

    if (RETURN_FAILURE == handle)
    { char szTemp[128];
      sprintf(szTemp,
              "%s::%s::line#%d",
              __FILE__, __FUNCTION__, __LINE__);
      gpSysLog->loginfo(szTemp);

      // Display login screen for failed authentication
      gpSchema = new schema("index.csv");
    }
    else
    { ssActive    = gpCsv->m_parsed_data[handle][COL_PASSWD_ACTIVE];
      ssUsername  = gpCsv->m_parsed_data[handle][COL_PASSWD_USERNAME];
      ssPassword  = gpCsv->m_parsed_data[handle][COL_PASSWD_PASSWORD];
      ssAuthLevel = gpCsv->m_parsed_data[handle][COL_PASSWD_AUTHLEVEL];
      ssFirstName = gpCsv->m_parsed_data[handle][COL_PASSWD_FIRSTNAME];
      ssLastName  = gpCsv->m_parsed_data[handle][COL_PASSWD_LASTNAME];
      ssDescript  = gpCsv->m_parsed_data[handle][COL_PASSWD_DESCR];

      if (0 == strcmp("admin", ssAuthLevel.c_str()))
      { gpSchema = new schema("admin-menu.csv");
      }
      if (0 == strcmp("devo", ssAuthLevel.c_str()))
      { gpSchema = new schema("devo-menu.csv");
      }
      if (0 == strcmp("user", ssAuthLevel.c_str()))
      { gpSchema = new schema("user-menu.csv");
      }
    }

    gpSchema->gen_from_schema(handle,
        ABOUT | ADMIN | SHUTDOWN | PREFS | LOGOUT,
        __FILE__, ssUsername, ssPassword);

    if (pMwFw->isCGI())
    { if (gpSh->m_pShMemng->bDisplaySchema)
      { gpHtml->dump_schema();
      }
      if (gpSh->m_pShMemng->bDisplayEnvVars)
      { gpHtml->dump_env_vars();
      }
      if (gpSh->m_pShMemng->bDisplayShmVars)
      { gpHtml->dump_shm_vars();
      }
    }

    return EXIT_SUCCESS;
}
