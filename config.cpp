////////////////////////////////////////////////////////////////////
// ~/public_html/fw/config.cpp 2025-07-15 18:16 dwg -             //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.  //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

config::config() {
    gpSysLog->loginfo(__PRETTY_FUNCTION__);
    if (access(gpSh->m_pShMemng->szConfigRoot,F_OK)) {
        //gpSysLog->loginfo("config directory does not exist");
        std::filesystem::create_directories(gpSh->m_pShMemng->szConfigRoot);
    } else {
        //gpSysLog->loginfo("config directory exists");
    }
}