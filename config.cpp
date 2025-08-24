////////////////////////////////////////////////////////////////////
// ~/public_html/fw/config.cpp 2025-07-15 18:16 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

config::config()
{
    gpSysLog->loginfo(__PRETTY_FUNCTION__);
    if (access(gpSh->m_pShMemng->szConfigFQDS,F_OK))
    {
        //gpSysLog->loginfo("config directory does not exist");
        std::filesystem::create_directories(gpSh->m_pShMemng->szConfigFQDS);
    }
    else
    {
        //gpSysLog->loginfo("config directory exists");
    }
}
