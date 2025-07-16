////////////////////////////////////////////////////////////////////
// ~/public_html/fw/profile.h 2025-07-16 08:08 dwg -              //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
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
