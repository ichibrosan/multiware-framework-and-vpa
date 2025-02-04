////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/login.cpp 2025/01/20  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "login.h"
char szTemp[128];


/*****************************************************************
 * This is the main entry point of the CGI script
 * @return Always returns EXIT_SUCCESS
 *****************************************************************/
int main() {
  gpSysLog = new CSysLog();
  gpSysLog->loginfo(__FILE__ );
  CLog log(__FILE__,__FUNCTION__);
  //log.truncate();

  std::string ssActive;
  std::string ssUsername;
  std::string ssPassword;
  std::string ssAuthLevel;
  std::string ssFirstName;
  std::string ssLastName;
  std::string ssDescript;

  char *ptr = getenv("GATEWAY_INTERFACE"); // s/b "CGI/1.1"
  bool bCGI = false;
  if (nullptr != ptr) {
    bCGI = true;
    std::cout << "content-type:\ttext/html\n\n" << std::endl;
  }

  gpLog     = new CLog(__FILE__, __FUNCTION__);
  gpLog->truncate();
  gpSh      = new shared();
  gpEnv     = new environment();

  gpCgi     = new Cgicc();


  gpCgiBind = new cgibind();

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

  // If the user authenticated, select the menu screen
  gpDash = new dashboard(
    handle,JOURNAL | LOGOUT,__FILE__,ssUsername,ssPassword);

  gpSchema->gen_from_schema(handle);

  if(bCGI) {
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
