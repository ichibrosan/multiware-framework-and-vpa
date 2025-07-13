//
// Created by doug on 1/13/25.
//

#pragma once

#include "std.h"
#include "CLog.hpp"


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
