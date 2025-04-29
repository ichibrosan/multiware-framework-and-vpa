////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/dotconfig.cpp 2025/04/28                 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#include "include/mwfw2.h"

dotconfig::dotconfig() {
    m_bCTOR = true;
}

bool dotconfig::isConfigDir() {
    namespace fs = std::filesystem;
    
    const char* homeDir = std::getenv("HOME");
    if (!homeDir) {
        return false;
    }
    
    fs::path configPath = fs::path(homeDir) / ".config" / "multiware";
    return fs::exists(configPath) && fs::is_directory(configPath);
}

bool dotconfig::assureConfigDir() {
    namespace fs = std::filesystem;

    const char* homeDir = std::getenv("HOME");
    if (!homeDir) {
        return false;
    }

    try {
        fs::path configPath = fs::path(homeDir) / ".config" / "multiware";

        // If directory already exists, return true
        if (isConfigDir()) {
            return true;
        }

        // Create all parent directories if they don't exist
        return fs::create_directories(configPath);
    }
    catch (const fs::filesystem_error& e) {
        // Handle filesystem errors (permissions, etc.)
        return false;
    }
}
