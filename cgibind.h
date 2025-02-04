/////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/cgibind.h 2025/01/27 02:51 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.      //
// This file is part of the Goodall MultiWare Framework Project.           //
/////////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_CGIBIND_H
#define MULTIWARE_CGIBIND_H

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
extern Cgicc * gpCgi;

class cgibind {
public:
    cgibind();
    std::string get_form_variable(std::string ssVariableName);
    std::string get_referrer();
    std::string get_referrer_path();
    std::string get_referrer_file();
};

#endif // MULTIWARE_CGIBIND_H

/////////////////////
// eof - cgibind.h //
/////////////////////