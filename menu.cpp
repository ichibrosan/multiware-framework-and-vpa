////////////////////////////////////////////////////////////////////
// ~/public_html/fw/menu.cpp 2025-07-15 18:16 dwg -               //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

int main() {
  mwfw2 * pMwFw = new mwfw2(__FILE__,__FUNCTION__);

  gpSchema = new schema("user-menu.csv");

  int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
  std::string ssUsername = gpCgiBind->get_form_variable("username");
  std::string ssPassword = gpCgiBind->get_form_variable("pwname");

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

  return 0;
}

////////////////////
// eof - menu.cpp //
////////////////////
