////////////////////////////////////////////////////////////////////
// ~/public_html/fw/profile.h 2025-07-16 08:08 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include "std.h"
#include "CLog.h"


class profile
{
    std::string m_ssFile;
    std::string m_ssFunction;

public:
    profile(std::string ssFile, std::string ssFunction);
    CLog* m_pLog;
};

/////////////////////
// eof - profile.h //
/////////////////////
