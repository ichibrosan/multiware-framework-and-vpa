////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/index.cpp 2025/01/14  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "index.h"

mwfw * fw;

int main() {
  fw = new mwfw();
  fw->sl_loginfo(__PRETTY_FUNCTION__);

  /**
   * Note: 2025/01/25 dwg -
   * shared and environment have been re-written and no longer call
   * the CLog class which used shared parameters to operate. Instead
   * they call the CSysLog class which writes log entries into the
   * system syslog. After environment is instantiated, then can test
   * to assure the shared parameters were properly set up.
   */
  gpSh  = new shared();

  gpEnv = new environment();


  /*
   * Note: 2025/01/25 12:04 dwg - The schema constructor calls genSchemaFQFS
   * so the shared variables such as szProtocol must already be valid.
   * Therefore, we should run self tests before instantiating the schema.
   */

  gpTest = new test(false, fw->isCGI());
  gpTest->logHistograms();

  if (0 < gpSh->m_pShMemng->num_tests_failed) {
    gpHtml->print("ERROR!! Self-test failed");
    exit(RETURN_SUCCESS_SORT_OF);
  }

  gpLog = new CLog(__FILE__, __FUNCTION__);

  gpSchema = new schema("index.csv");
  gpSchema->gen_from_schema(0);
  // if(bCGI) {
  //   gpHtml->dump_schema();
  // }
  // std::cout << "debug " << std::endl;
  // return(0);

  /*
   * Let's also compile the index.csv schema into the header index.h
   */
  gpSchCC = new schemaCompiler("create.csv",false); delete gpSchCC;
  gpSchCC = new schemaCompiler("index.csv",false);  delete gpSchCC;
  gpSchCC = new schemaCompiler("login.csv",false); delete gpSchCC;
  gpSchCC = new schemaCompiler("user-menu.csv",false);  delete gpSchCC;
  gpSchCC = new schemaCompiler("root.csv",false);  delete gpSchCC;

  // if(bCGI) {
  //    gpHtml->dump_shm_vars();
  //    gpHtml->dump_env_vars();
  // }

  return 0;
}
