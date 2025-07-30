////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cfgini.h 2025-07-16 08:08 dwg -               //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <map>
#include <vector>
#include <fstream>

/**
 * @class cfgini
 * @brief A class for managing INI-style configuration files.
 *
 * This class provides functionality for creating, reading, and writing
 * INI-style configuration files. It supports sections, variables within
 * sections, and basic file operations.
 */
class cfgini
{
private:
    /**
     * Structure to hold section data
     * Maps variable names to their values within a section
     */
    std::map<std::string, std::map<std::string, std::string>> m_sections;

    /**
     * The filename of the configuration file
     */
    std::string m_filename;

    /**
     * Flag indicating if the configuration has been modified
     */
    bool m_modified;

    /**
     * Trims whitespace from the beginning and end of a string
     * @param str The string to trim
     * @return The trimmed string
     */
    std::string trim(const std::string& str);

    /**
     * Parses a line from the INI file
     * @param line The line to parse
     * @param currentSection Reference to the current section name
     * @return True if the line was parsed successfully
     */
    bool parseLine(const std::string& line, std::string& currentSection);

public:
    /**
     * Default constructor
     */
    cfgini();

    /**
     * Constructor with filename
     * @param filename The name of the configuration file
     */
    cfgini(const std::string& filename);

    /**
     * Destructor
     */
    ~cfgini();

    /**
     * Creates a new empty configuration
     * @return True if successful
     */
    bool createNew();

    /**
     * Loads configuration from file
     * @param filename The filename to load from (optional, uses stored filename if not provided)
     * @return True if successful
     */
    bool load(const std::string& filename = "");

    /**
     * Saves configuration to file
     * @param filename The filename to save to (optional, uses stored filename if not provided)
     * @return True if successful
     */
    bool save(const std::string& filename = "");

    /**
     * Sets the filename for the configuration
     * @param filename The filename to set
     */
    void setFilename(const std::string& filename);

    /**
     * Gets the current filename
     * @return The current filename
     */
    std::string getFilename() const;

    /**
     * Adds a new section to the configuration
     * @param sectionName The name of the section to add
     * @return True if successful (false if section already exists)
     */
    bool addSection(const std::string& secName);

    /**
     * Removes a section from the configuration
     * @param sectionName The name of the section to remove
     * @return True if successful
     */
    bool removeSection(const std::string& secName);

    /**
     * Checks if a section exists
     * @param sectionName The name of the section to check
     * @return True if the section exists
     */
    bool hasSection(const std::string& secName) const;

    /**
     * Gets a list of all section names
     * @return Vector of section names
     */
    std::vector<std::string> getSections() const;

    /**
     * Sets a variable value in a section
     * @param sectionName The name of the section
     * @param variableName The name of the variable
     * @param value The value to set
     * @return True if successful
     */
    bool setVariable(const std::string& secName,
                     const std::string& varName, const std::string& value);

    /**
     * Gets a variable value from a section
     * @param sectionName The name of the section
     * @param variableName The name of the variable
     * @param defaultValue The default value to return if variable doesn't exist
     * @return The variable value or default value
     */
    std::string getVariable(const std::string& sectionName,
                            const std::string& variableName,
                            const std::string& defaultValue = "") const;

    /**
     * Removes a variable from a section
     * @param sectionName The name of the section
     * @param variableName The name of the variable
     * @return True if successful
     */
    bool removeVariable(const std::string& sectionName,
                        const std::string& variableName);

    /**
     * Checks if a variable exists in a section
     * @param sectionName The name of the section
     * @param variableName The name of the variable
     * @return True if the variable exists
     */
    bool hasVariable(const std::string& sectionName,
                     const std::string& variableName) const;

    /**
     * Gets all variable names in a section
     * @param sectionName The name of the section
     * @return Vector of variable names
     */
    std::vector<std::string> getVariables(const std::string& sectionName) const;

    /**
     * Clears all configuration data
     */
    void clear();

    /**
     * Checks if the configuration has been modified
     * @return True if modified
     */
    bool isModified() const;

    /**
     * Marks the configuration as saved (clears modified flag)
     */
    void markSaved();
};

////////////////////
// eof - cfgini.h //
////////////////////
