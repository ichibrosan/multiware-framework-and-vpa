/////////////////////////////////////////////////////////////////////////
// cfgini.cpp - Basic INI config file functionality                   //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
/////////////////////////////////////////////////////////////////////////

#include "include/cfgini.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

cfgini::cfgini() : m_filename(""), m_modified(false) {
}

cfgini::cfgini(const std::string& filename) : m_filename(filename), m_modified(false) {
}

cfgini::~cfgini() {
}

std::string cfgini::trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }

    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

bool cfgini::parseLine(const std::string& line, std::string& currentSection) {
    std::string trimmedLine = trim(line);

    // Skip empty lines and comments
    if (trimmedLine.empty() || trimmedLine[0] == ';' || trimmedLine[0] == '#') {
        return true;
    }

    // Check for section header
    if (trimmedLine[0] == '[' && trimmedLine[trimmedLine.length() - 1] == ']') {
        currentSection = trimmedLine.substr(1, trimmedLine.length() - 2);
        currentSection = trim(currentSection);
        addSection(currentSection);
        return true;
    }

    // Check for key=value pair
    size_t equalsPos = trimmedLine.find('=');
    if (equalsPos != std::string::npos) {
        std::string key = trim(trimmedLine.substr(0, equalsPos));
        std::string value = trim(trimmedLine.substr(equalsPos + 1));

        if (!currentSection.empty()) {
            setVariable(currentSection, key, value);
        }
        return true;
    }

    return false;
}

bool cfgini::createNew() {
    clear();
    m_modified = true;
    return true;
}

bool cfgini::load(const std::string& filename) {
    std::string fileToLoad = filename.empty() ? m_filename : filename;

    if (fileToLoad.empty()) {
        return false;
    }

    std::ifstream file(fileToLoad);
    if (!file.is_open()) {
        return false;
    }

    clear();

    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        if (!parseLine(line, currentSection)) {
            // Log warning about invalid line if needed
        }
    }

    file.close();
    m_modified = false;

    if (!filename.empty()) {
        m_filename = filename;
    }

    return true;
}

bool cfgini::save(const std::string& filename) {
    std::string fileToSave = filename.empty() ? m_filename : filename;

    if (fileToSave.empty()) {
        return false;
    }

    std::ofstream file(fileToSave);
    if (!file.is_open()) {
        return false;
    }

    for (const auto& section : m_sections) {
        file << "[" << section.first << "]" << std::endl;

        for (const auto& variable : section.second) {
            file << variable.first << "=" << variable.second << std::endl;
        }

        file << std::endl;
    }

    file.close();
    m_modified = false;

    if (!filename.empty()) {
        m_filename = filename;
    }

    return true;
}

void cfgini::setFilename(const std::string& filename) {
    m_filename = filename;
}

std::string cfgini::getFilename() const {
    return m_filename;
}

bool cfgini::addSection(const std::string& sectionName) {
    if (m_sections.find(sectionName) != m_sections.end()) {
        return false; // Section already exists
    }

    m_sections[sectionName] = std::map<std::string, std::string>();
    m_modified = true;
    return true;
}

bool cfgini::removeSection(const std::string& sectionName) {
    auto it = m_sections.find(sectionName);
    if (it == m_sections.end()) {
        return false;
    }

    m_sections.erase(it);
    m_modified = true;
    return true;
}

bool cfgini::hasSection(const std::string& sectionName) const {
    return m_sections.find(sectionName) != m_sections.end();
}

std::vector<std::string> cfgini::getSections() const {
    std::vector<std::string> sections;
    for (const auto& section : m_sections) {
        sections.push_back(section.first);
    }
    return sections;
}

bool cfgini::setVariable(const std::string& sectionName, const std::string& variableName, const std::string& value) {
    // Auto-create section if it doesn't exist
    if (m_sections.find(sectionName) == m_sections.end()) {
        m_sections[sectionName] = std::map<std::string, std::string>();
    }

    m_sections[sectionName][variableName] = value;
    m_modified = true;
    return true;
}

std::string cfgini::getVariable(const std::string& sectionName, const std::string& variableName, const std::string& defaultValue) const {
    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end()) {
        return defaultValue;
    }

    auto variableIt = sectionIt->second.find(variableName);
    if (variableIt == sectionIt->second.end()) {
        return defaultValue;
    }

    return variableIt->second;
}

bool cfgini::removeVariable(const std::string& sectionName, const std::string& variableName) {
    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end()) {
        return false;
    }

    auto variableIt = sectionIt->second.find(variableName);
    if (variableIt == sectionIt->second.end()) {
        return false;
    }

    sectionIt->second.erase(variableIt);
    m_modified = true;
    return true;
}

bool cfgini::hasVariable(const std::string& sectionName, const std::string& variableName) const {
    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end()) {
        return false;
    }

    return sectionIt->second.find(variableName) != sectionIt->second.end();
}

std::vector<std::string> cfgini::getVariables(const std::string& sectionName) const {
    std::vector<std::string> variables;

    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end()) {
        return variables;
    }

    for (const auto& variable : sectionIt->second) {
        variables.push_back(variable.first);
    }

    return variables;
}

void cfgini::clear() {
    m_sections.clear();
    m_modified = true;
}

bool cfgini::isModified() const {
    return m_modified;
}

void cfgini::markSaved() {
    m_modified = false;
}