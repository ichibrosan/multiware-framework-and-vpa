////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/index.cpp 2025/01/14  //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////
#include "mwfw2.h"

// /**
//  * @brief Pointer to an instance of the mwfw class.
//  *
//  * This variable represents a global pointer to the `mwfw` class, which provides
//  * functionalities such as system logging and determining if the current runtime
//  * environment is CGI-based. The `mwfw` instance is used for managing logging
//  * information and interacting with the system's environment.
//  *
//  * Key functionalities of the referenced `mwfw` instance:
//  * - Logging system information through `sl_loginfo`.
//  * - Checking if the runtime environment is CGI via `isCGI`.
//  */
// mwfw * fw;

/**
 * Entry point of the program. Initializes the framework, shared memory,
 * environment, and other essential components, conducts self-tests,
 * generates schema files, and verifies the configuration.
 *
 * @return Returns 0 on successful execution.
 */
int main() {
    mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);
    pMwFw->sl_loginfo(__PRETTY_FUNCTION__);

  /*
   * Note: 2025/01/25 12:04 dwg - The schema constructor calls genSchemaFQFS
   * so the shared variables such as szProtocol must already be valid.
   * Therefore, we should run self tests before instantiating the schema.
   */

   gpTest = new test(false, pMwFw->isCGI());
  // gpTest->logHistograms();

  // if (0 < gpSh->m_pShMemng->num_tests_failed) {
  //   gpHtml->print("ERROR!! Self-test failed");
  //   exit(RETURN_SUCCESS_SORT_OF);
  // }

  gpLog = new CLog(__FILE__, __FUNCTION__);

  gpSchema = new schema("index.csv");
  gpSchema->gen_from_schema(0);

  /*
   * Let's also compile the index.csv schema into the header index.h
   */
  // gpSchCC = new schemaCompiler("create.csv",false); delete gpSchCC;
  // gpSchCC = new schemaCompiler("index.csv",false);  delete gpSchCC;
  // gpSchCC = new schemaCompiler("login.csv",false); delete gpSchCC;
  // gpSchCC = new schemaCompiler("user-menu.csv",false);  delete gpSchCC;
  // gpSchCC = new schemaCompiler("root.csv",false);  delete gpSchCC;

  return 0;
}
