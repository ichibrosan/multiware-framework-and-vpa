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

        // Create all parent directories if they don’t exist
        return fs::create_directories(configPath);
    }
    catch (const fs::filesystem_error& e) {
        // Handle filesystem errors (permissions, etc.)
        return false;
    }
}

bool dotconfig::isLicenseUUID() {
    std::ifstream etcFile("/etc/license");
    std::ifstream docFile("/home/doug/public_html/fw/doc/license");

    if (!etcFile.is_open() || !docFile.is_open()) {
        std::cout << "Content-type: text/html\n\n" << std::endl;
    }
    if (!etcFile.is_open()) {
        std::cout << "etcFile not open" << std::endl;
        return false;
    }
    if (!docFile.is_open()) {
        std::cout << "docFile not open" << std::endl;
        return false;
    }

    try {
        std::string etcUUID, docUUID;

        // Read UUIDs from both files
        // Assuming UUID is on a single line
        std::getline(etcFile, etcUUID);
        std::getline(docFile, docUUID);

        // Trim whitespace
        etcUUID.erase(0, etcUUID.find_first_not_of(" \t\n\r"));
        etcUUID.erase(etcUUID.find_last_not_of(" \t\n\r") + 1);
        docUUID.erase(0, docUUID.find_first_not_of(" \t\n\r"));
        docUUID.erase(docUUID.find_last_not_of(" \t\n\r") + 1);

        // Validate UUID format (basic check)
        const std::regex uuidRegex("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$");
        if (!std::regex_match(etcUUID, uuidRegex) || !std::regex_match(docUUID, uuidRegex)) {
            return false;
        }

        return etcUUID == docUUID;
    }
    catch (const std::exception& e) {
        return false;
    }
}