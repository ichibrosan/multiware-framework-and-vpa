
#include "profile.h"

profile::profile(std::string ssFile, std::string ssFunction)
{
        m_pLog = new CLog(ssFile.c_str(), ssFunction.c_str());
}

