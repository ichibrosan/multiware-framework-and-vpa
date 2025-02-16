////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/login.cpp 2025/01/20  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * @brief A temporary character buffer used for storing formatted strings.
 *
 * This buffer is typically utilized for logging and debugging purposes,
 * where formatted strings containing file names, function names, and line
 * numbers are stored before being passed to a logging mechanism.
 *
 * @note The buffer has a fixed size of 128 characters. Care should be
 *       taken to avoid buffer overflows when copying or formatting
 *       strings into it.
 */
char szTemp[128];


/**
 * @brief Entry point of the application, initializes various objects,
 *        handles user authentication, and generates appropriate dashboards
 *        or schemas based on the authentication and permissions.
 *
 * Initializes system logging, CGI environment, shared memory, and CSV
 * data parser. It checks CGI mode, processes user credentials, fetches
 * user-specific data from the CSV storage, and determines access levels
 * and permissions. Based on the user's authentication level, it generates
 * customized schemas or dashboards.
 *
 * @return EXIT_SUCCESS on successful execution.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

  std::string ssActive;
  std::string ssUsername;
  std::string ssPassword;
  std::string ssAuthLevel;
  std::string ssFirstName;
  std::string ssLastName;
  std::string ssDescript;

  std::string ssHttpReferrer = gpCgiBind->get_referrer();
  std::string ssReferrerPath = gpCgiBind->get_referrer_path();
  std::string ssReferrerFile = gpCgiBind->get_referrer_file();

  gpCsv = new readCsv("passwd.csv");
  gpCsv->parseData();

  std::string ssUsernameX = gpCgiBind->get_form_variable("username");
  std::string ssPasswordX = gpCgiBind->get_form_variable("pwname");

  std::string ssbDisplaySchema  = gpCgiBind->get_form_variable("bDisplaySchema");
  if (ssbDisplaySchema == "true") {
    gpSh->m_pShMemng->bDisplaySchema = true;
  }
  if (ssbDisplaySchema == "false") {
    gpSh->m_pShMemng->bDisplaySchema = false;
  }

  std::string ssbDisplayEnvVars = gpCgiBind->get_form_variable("bDisplayEnvVars");
  if (ssbDisplayEnvVars == "true") {
    gpSh->m_pShMemng->bDisplayEnvVars = true;
  }
  if (ssbDisplayEnvVars == "false") {
    gpSh->m_pShMemng->bDisplayEnvVars = false;
  }

  std::string ssbDisplayShmVars = gpCgiBind->get_form_variable("bDisplayShmVars");
  if (ssbDisplayShmVars == "true") {
    gpSh->m_pShMemng->bDisplayShmVars = true;
  }
  if (ssbDisplayShmVars == "false") {
    gpSh->m_pShMemng->bDisplayShmVars = false;
  }

  int handle = gpPassword->lookup_username_password(
                                ssUsernameX, ssPasswordX);

  if(RETURN_FAILURE == handle) {
    sprintf(szTemp,"%s::%s::line#%d",__FILE__,__FUNCTION__,__LINE__);
    gpSysLog->loginfo(szTemp);
    // If the password lookup failed, select the login screen
    gpSchema = new schema("index.csv");

  } else {
    // The user is authenticated, fetch his password variables
    ssActive    = gpCsv->m_parsed_data[handle][COL_PASSWD_ACTIVE];
    ssUsername  = gpCsv->m_parsed_data[handle][COL_PASSWD_USERNAME];
    ssPassword  = gpCsv->m_parsed_data[handle][COL_PASSWD_PASSWORD];
    ssAuthLevel = gpCsv->m_parsed_data[handle][COL_PASSWD_AUTHLEVEL];
    ssFirstName = gpCsv->m_parsed_data[handle][COL_PASSWD_FIRSTNAME];
    ssLastName  = gpCsv->m_parsed_data[handle][COL_PASSWD_LASTNAME];
    ssDescript  = gpCsv->m_parsed_data[handle][COL_PASSWD_DESCR];

    if (0 == strcmp("admin",ssAuthLevel.c_str()) ) {
      gpSchema = new schema("admin-menu.csv");
    }
    if (0 == strcmp("devo",ssAuthLevel.c_str()) ) {
      gpSchema = new schema("devo-"
                            "menu.csv");
    }
    if (0 == strcmp("user",ssAuthLevel.c_str()) ) {
      gpSchema = new schema("user-menu.csv");
    }
  }

  // // If the user authenticated, select the menu screen
  // gpDash = new dashboard(
  //   handle,JOURNAL | LOGOUT,__FILE__,ssUsername,ssPassword);

  gpSchema->gen_from_schema(handle,JOURNAL | LOGOUT,__FILE__,ssUsername,ssPassword);

  if(pMwFw->isCGI()) {
    std::string ssHttpReferrer = gpCgiBind->get_referrer();
    std::string ssReferrerPath = gpCgiBind->get_referrer_path();
    std::string ssReferrerFile = gpCgiBind->get_referrer_file();
    //gpHtml->dump_referrer(ssHttpReferrer,ssReferrerPath,ssReferrerFile);
    if (gpSh->m_pShMemng->bDisplaySchema) {
      gpHtml->dump_schema();
    }
    if (gpSh->m_pShMemng->bDisplayEnvVars) {
      gpHtml->dump_env_vars();
    }
    if (gpSh->m_pShMemng->bDisplayShmVars) {
      gpHtml->dump_shm_vars();
    }
  }
  return EXIT_SUCCESS;
}
