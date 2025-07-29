////////////////////////////////////////////////////////////////////
// ~/public_html/fw/cfgini.cpp 2025-07-15 18:16 dwg -             //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#include "mwfw2.h"

/**
 * Default constructor for the cfgini class.
 * Initializes the configuration with an empty filename and sets the modified
 * flag to false.
 */
cfgini::cfgini() : m_filename(""), m_modified(false)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);
}

/**
 * Constructs a configuration object and assigns the provided filename.
 * Initializes the modified flag to false.
 *
 * @param filename The name of the configuration file to be managed.
 */
cfgini::cfgini(const std::string& filename) : m_filename(filename),
                                              m_modified(false)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);
}

/**
 * Destructor for the cfgini class.
 *
 * This destructor is responsible for cleaning up resources
 * used by the cfgini instance. It ensures that any necessary
 * cleanup is performed when the object is destroyed.
 */
cfgini::~cfgini()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);
}

/**
 * Function to remove leading and trailing whitespace characters
 * from a given string.
 * The function processes the input string and returns a new
 * string with whitespace stripped from both ends.
 */
std::string cfgini::trim(const std::string& str)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    auto start = str.begin();
    while (start != str.end() && std::isspace(*start))
    {
        start++;
    }

    auto end = str.end();
    do
    {
        end--;
    }
    while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

/**
 * Parses a line from a configuration file and updates the current section or
 * adds a key-value pair based on the content of the line.
 *
 * @param line The input line to parse, representing either a section header,
 *             a comment, a key-value pair, or an empty line.
 * @param currentSection Reference to the current section. This will be updated
 *                       if a new section header is identified.
 * @return true if the line is valid and successfully processed;
 *         false if the line does not conform to expected formats.
 *
 * The line can represent:
 * - Section headers in the format [section].
 * - Key-value pairs in the format key=value.
 * - Comments starting with ';' or '#'.
 * - Empty lines, which are skipped with no effect.
 *
 * This function trims whitespace from the line to handle formatting variations.
 * When a section header is encountered, it sets the current section and adds
 * it to the configuration. For key-value pairs, the key and value are assigned
 * to the current section if one is specified.
 */
bool cfgini::parseLine(const std::string& line, std::string& currentSection)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    std::string trimmedLine = trim(line);

    // Skip empty lines and comments
    if (trimmedLine.empty() || trimmedLine[0] == ';' || trimmedLine[0] == '#')
    {
        return true;
    }

    // Check for section header
    if (trimmedLine[0] == '[' && trimmedLine[trimmedLine.length() - 1] == ']')
    {
        currentSection = trimmedLine.substr(1, trimmedLine.length() - 2);
        currentSection = trim(currentSection);
        addSection(currentSection);
        return true;
    }

    // Check for key=value pair
    size_t equalsPos = trimmedLine.find('=');
    if (equalsPos != std::string::npos)
    {
        std::string key = trim(trimmedLine.substr(0, equalsPos));
        std::string value = trim(trimmedLine.substr(equalsPos + 1));

        if (!currentSection.empty())
        {
            setVariable(currentSection, key, value);
        }
        return true;
    }

    return false;
}

/**
 * Creates a new empty configuration by clearing all existing configuration data.
 * Marks the configuration as modified.
 *
 * @return True if the new configuration is created successfully
 */
bool cfgini::createNew()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    clear();
    m_modified = true;
    return true;
}

/**
 * Loads an INI configuration file into the current object.
 *
 * @param filename The path to the file to be loaded. If empty, the internal
 * filename stored in the object is used instead.
 * @return True if the loading and parsing are successful, otherwise false.
 *
 * This function clears any existing configuration data before loading the new
 * data from the file. If the file cannot be opened or the filename is invalid,
 * the function will fail and return false. The method updates the internal
 * filename if a valid filename is provided and ensures the internal
 * modification status is reset to false upon successful load.
 */
bool cfgini::load(const std::string& filename)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);


    std::string fileToLoad = filename.empty() ? m_filename : filename;

    if (fileToLoad.empty())
    {
        return false;
    }

    std::ifstream file(fileToLoad);
    if (!file.is_open())
    {
        return false;
    }

    clear();

    std::string line;
    std::string currentSection;

    while (std::getline(file, line))
    {
        if (!parseLine(line, currentSection))
        {
            // Log warning about invalid line if needed
        }
    }

    file.close();
    m_modified = false;

    if (!filename.empty())
    {
        m_filename = filename;
    }

    return true;
}

/**
 * Saves the current state or data to a specified destination.
 * This function ensures that the relevant information is persisted.
 */
bool cfgini::save(const std::string& filename)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    std::string fileToSave = filename.empty() ? m_filename : filename;

    if (fileToSave.empty())
    {
        return false;
    }

    std::ofstream file(fileToSave);
    if (!file.is_open())
    {
        return false;
    }

    for (const auto& section : m_sections)
    {
        file << "[" << section.first << "]" << std::endl;

        for (const auto& variable : section.second)
        {
            file << variable.first << "=" << variable.second << std::endl;
        }

        file << std::endl;
    }

    file.close();
    m_modified = false;

    if (!filename.empty())
    {
        m_filename = filename;
    }

    return true;
}

/**
 * Sets the filename for the configuration file.
 *
 * This method updates the internal filename used for loading or saving
 * the configuration data. The new filename will replace any previously
 * set filename.
 *
 * @param filename The new filename to set.
 */
void cfgini::setFilename(const std::string& filename)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    m_filename = filename;
}

/**
 * Retrieves the filename associated with the configuration.
 * @return The stored filename as a string.
 */
std::string cfgini::getFilename() const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    return m_filename;
}

/**
 * Adds a new section to the configuration.
 *
 * If a section with the specified name already exists, the method returns
 * false and no changes are made. Otherwise, a new section is created,
 * the modified flag is set to true, and the method returns true.
 *
 * @param sectionName The name of the section to add.
 * @return True if the section was successfully added, false if the section
 * already exists.
 */
bool cfgini::addSection(const std::string& sectionName)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    if (m_sections.find(sectionName) != m_sections.end())
    {
        return false; // Section already exists
    }

    m_sections[sectionName] = std::map<std::string, std::string>();
    m_modified = true;
    return true;
}

/**
 * Removes a section from the configuration.
 *
 * This function searches for the specified section by its name.
 * If the section exists, it is removed from the configuration
 * and the modified flag is set to true. If the section does not
 * exist, the function returns false.
 *
 * @param sectionName The name of the section to remove.
 * @return True if the section existed and was successfully removed, false
 * otherwise.
 */
bool cfgini::removeSection(const std::string& sectionName)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    auto it = m_sections.find(sectionName);
    if (it == m_sections.end())
    {
        return false;
    }

    m_sections.erase(it);
    m_modified = true;
    return true;
}

/**
 * Checks if a section exists in the configuration.
 *
 * This function searches for the specified section name in the
 * internal map of sections and determines if it exists.
 *
 * @param sectionName The name of the section to check.
 * @return True if the section exists, false otherwise.
 */
bool cfgini::hasSection(const std::string& sectionName) const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    return m_sections.find(sectionName) != m_sections.end();
}

/**
 * Retrieves a list of all section names present in the configuration.
 *
 * @return A vector containing the names of all sections.
 */
std::vector<std::string> cfgini::getSections() const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    std::vector<std::string> sections;
    for (const auto& section : m_sections)
    {
        sections.push_back(section.first);
    }
    return sections;
}

/**
 * Sets the value of a variable within a specific section.
 *
 * If the specified section does not exist, it is created automatically.
 * The variable will be added or updated with the provided value.
 *
 * @param sectionName The name of the section to which the variable belongs.
 * @param variableName The name of the variable to set.
 * @param value The value to assign to the variable.
 * @return True if the operation is successful.
 */
bool cfgini::setVariable(const std::string& sectionName,
                         const std::string& variableName,
                         const std::string& value)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    // Auto-create section if it doesn't exist
    if (m_sections.find(sectionName) == m_sections.end())
    {
        m_sections[sectionName] = std::map<std::string, std::string>();
    }

    m_sections[sectionName][variableName] = value;
    m_modified = true;
    return true;
}

/**
 * Retrieves the value of a variable from a specified section in the
 * configuration.
 *
 * If the section or the variable does not exist, the specified default value
 * is returned.
 *
 * @param sectionName The name of the section to search within.
 * @param variableName The name of the variable to retrieve.
 * @param defaultValue The value to return if the section or variable is not
 * found.
 * @return The value of the variable if found, or the default value if not
 * found.
 */
std::string cfgini::getVariable(const std::string& sectionName,
                                const std::string& variableName,
                                const std::string& defaultValue) const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end())
    {
        return defaultValue;
    }

    auto variableIt = sectionIt->second.find(variableName);
    if (variableIt == sectionIt->second.end())
    {
        return defaultValue;
    }

    return variableIt->second;
}

/**
 * Removes a variable from a specified section in the configuration.
 *
 * This function searches for a section by its name and, within that section,
 * attempts to find and erase a variable by its name. If either the section or
 * the variable does not exist, the function returns false. If the variable is
 * successfully removed, the function returns true and marks the configuration
 * as modified.
 *
 * @param sectionName The name of the section from which the variable should be
 * removed.
 * @param variableName The name of the variable to be removed.
 * @return true if the variable was removed successfully; false otherwise.
 */
bool cfgini::removeVariable(const std::string& sectionName,
                            const std::string& variableName)
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end())
    {
        return false;
    }

    auto variableIt = sectionIt->second.find(variableName);
    if (variableIt == sectionIt->second.end())
    {
        return false;
    }

    sectionIt->second.erase(variableIt);
    m_modified = true;
    return true;
}

/**
 * Checks if a variable exists within a specific section in the configuration.
 *
 * The method first searches for the specified section.
 * If the section exists, it checks if the variable exists
 * within that section.
 *
 * @param sectionName The name of the section to check.
 * @param variableName The name of the variable to look for within the section.
 * @return True if the variable exists in the specified section,
 *         otherwise false.
 */
bool cfgini::hasVariable(const std::string& sectionName,
                         const std::string& variableName) const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end())
    {
        return false;
    }

    return sectionIt->second.find(variableName) != sectionIt->second.end();
}

/**
 * Retrieves all variable names within a specified section of the configuration.
 *
 * This function searches the configuration for the given section name. If the
 * section exists, it extracts and returns all variable names within that
 * section. If the section does not exist, an empty vector is returned.
 *
 * @param sectionName The name of the section from which to retrieve variable
 * names.
 * @return A vector containing the variable names in the specified section.
 */
std::vector<std::string> cfgini::getVariables(
    const std::string& sectionName) const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    std::vector<std::string> variables;

    auto sectionIt = m_sections.find(sectionName);
    if (sectionIt == m_sections.end())
    {
        return variables;
    }

    for (const auto& variable : sectionIt->second)
    {
        variables.push_back(variable.first);
    }

    return variables;
}

/**
 * Clears all sections and marks the configuration as modified.
 * This method removes all section data from the configuration
 * and sets the modified flag to true, indicating that the
 * configuration has been changed.
 */
void cfgini::clear()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    m_sections.clear();
    m_modified = true;
}

/**
 * Checks if the configuration has been modified.
 *
 * @return True if the configuration has been modified, otherwise false.
 */
bool cfgini::isModified() const
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    return m_modified;
}

/**
 * Marks the configuration as saved by resetting the modified flag.
 * After calling this method, the configuration is considered unmodified.
 */
void cfgini::markSaved()
{
    CLog log(__FILE__, __FUNCTION__);
    log.write(__PRETTY_FUNCTION__);

    m_modified = false;
}
