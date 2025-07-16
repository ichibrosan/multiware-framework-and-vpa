////////////////////////////////////////////////////////////////////
// ~/public_html/fw/mutations.cpp 2025-07-15 18:16 dwg -          //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "profile.h"

profile::profile(std::string ssFile, std::string ssFunction)
{
        m_pLog = new CLog(ssFile.c_str(), ssFunction.c_str());
}

