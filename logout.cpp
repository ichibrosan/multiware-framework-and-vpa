/////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/logout.cpp 2025/01/17  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.  //
/////////////////////////////////////////////////////////////////////////

#include "logout.h"

char * gpszServerPort;  // used to detect CGI activity

logout::logout()
{

}

int main() {
  CLog log(__FILE__,__FUNCTION__);
  log.truncate();

  char *ptr = getenv("SERVER_PORT");
  bool bCGI = false;
  if (nullptr != ptr) {
    bCGI = true;
    std::cout << "content-type:\ttext/html\n\n" << std::endl;
  }

  gpLog = new CLog(__FILE__, __FUNCTION__);
  gpLog->truncate();

  gpSh = new shared();

  gpCgi = new Cgicc();
  gpCgiBind = new cgibind();

  // int         iHandle    =
  //    atoi(gpCgiBind->get_form_variable("handle").c_str());
    int iHandle = atoi(gpCgiBind->get_form_variable("handle").c_str());
  log.namedInt("handle", iHandle);

  /**
   * Invalidate authentication information in shared
   */
  memset(       gpSh->m_pShMemng->creds[iHandle].szAuthUserName,0,
         sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthUserName));
  memset(       gpSh->m_pShMemng->creds[iHandle].szAuthFirstName,0,
         sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthFirstName));
  memset(       gpSh->m_pShMemng->creds[iHandle].szAuthLastName,0,
         sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthLastName));
  memset(       gpSh->m_pShMemng->creds[iHandle].szAuthUUID,0,
         sizeof(gpSh->m_pShMemng->creds[iHandle].szAuthUUID));
                gpSh->m_pShMemng->creds[iHandle].iAuthHandle = 0;

  std::string ssHttpReferrer = gpCgi->getEnvironment().getReferrer();
  std::string ssReferrerPath =
      std::filesystem::path(ssHttpReferrer).remove_filename();
  std::string ssReferrerFile =
      ssHttpReferrer.substr(ssReferrerPath.length(), ssHttpReferrer.length());

  gpEnv = new environment();

  gpSchema = new schema("index.csv");
  gpSchema->gen_from_schema(1);


  return EXIT_SUCCESS;
}
