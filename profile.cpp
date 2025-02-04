//
// Created by doug on 1/13/25.
//

#include "profile.h"

profile::profile(std::string ssFile,std::string ssFunction) {
        m_pLog = new CLog(ssFile.c_str(),ssFunction.c_str());
}

