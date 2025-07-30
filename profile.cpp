////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mutations.cpp 2025-07-15 18:16 dwg -          //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "profile.h"

profile::profile(std::string ssFile, std::string ssFunction)
{
        m_pLog = new CLog(ssFile.c_str(), ssFunction.c_str());
}

