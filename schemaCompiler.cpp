
#include "mwfw2.h"

/**
 * Retrieves and processes schema data based on the provided schema name.
 * This function stores the schema name, initializes a CSV reader object with the schema,
 * parses the data within the CSV, and updates the number of lines processed.
 *
 * @param ssSchemaName The name of the schema to be loaded and processed.
 */
void schemaCompiler::getSchema(std::string ssSchemaName)
{
    m_ssSN = ssSchemaName;
    gpCsv = new readCsv(m_ssSN);
    gpCsv->parseData();
    m_iLines = gpCsv->m_iRow;
}


/**
 * Creates the header file name for the schema based on the current file path and schema name.
 * The resulting name will have a ".hh" extension and is stored in the member variable m_ssHFN.
 *
 * @param bDebug A boolean flag indicating whether debugging mode is active. This parameter is currently unused in this function.
 */
void schemaCompiler::createHeaderFileName(bool bDebug)
{
    std::string ssTemp;
    ssTemp = __FILE__;
    ssTemp = std::filesystem::path(ssTemp).remove_filename();
    ssTemp.append("schemas/");
    ssTemp.append(m_ssSN);
    ssTemp = std::filesystem::path(ssTemp).replace_extension(".hh");
    m_ssHFN = ssTemp;
}


/**
 * Checks whether the current schema is active.
 *
 * The method evaluates the value in the parsed data associated with
 * an "active" metadata column. If the value matches "true", the schema
 * is considered active.
 *
 * @return true if the current schema is active, otherwise false.
 */
bool schemaCompiler::isActiveSchema()
{
    if (0 == strcmp("true",
                    gpCsv->m_parsed_data[ROW_META_DATA][COL_META_ACTIVE].
                    c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Checks if the schema version of the provided CSV data is valid.
 *
 * Validity is determined by comparing the parsed schema version data
 * with the expected version "1".
 *
 * @return true if the schema version matches "1", false otherwise.
 */
bool schemaCompiler::isValidSchemaVersion()
{
    if (0 == strcmp("1",
                    gpCsv->m_parsed_data[ROW_META_DATA][COL_META_VERSION].
                    c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Checks if a specific row in the dataset is marked as active.
 *
 * This method determines whether the row at the specified index
 * is designated as active by comparing its "active" column value to "true".
 *
 * @param iRow The index of the row to check.
 * @return true if the row is active, false otherwise.
 */
bool schemaCompiler::isRowActive(int iRow)
{
    if (0 == strcmp("true",
                    gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Checks if the type of the given row is "precheckbox".
 *
 * @param iRow The index of the row to check in the CSV data.
 * @return true if the type of the specified row is "precheckbox", otherwise false.
 */
bool schemaCompiler::isTypePreCheckbox(int iRow)
{
    bool bRetVal;
    if (0 == strcmp("precheckbox",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        bRetVal = true;
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}


/**
 * Determines whether the type of a given row is a 'precheckbox'.
 *
 * @param iRow The row index to check in the parsed data.
 * @return True if the type of the given row is 'precheckbox'; otherwise, false.
 */
bool schemaCompiler::isTypePostCheckbox(int iRow)
{
    bool bRetVal;
    if (0 == strcmp("precheckbox",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        bRetVal = true;
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}


/**
 * Determines if the data type in the specified row is "image".
 *
 * @param iRow An integer representing the row number in the parsed CSV data.
 * @return True if the data type in the specified row is "image", otherwise false.
 */
bool schemaCompiler::isTypeImage(int iRow)
{
    bool bRetVal;
    if (0 == strcmp("image",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        bRetVal = true;
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}


/**
 * Checks if the type of the specified row is "password".
 *
 * @param iRow The index of the row to check in the parsed data.
 * @return True if the specified row type is "password", otherwise false.
 */
bool schemaCompiler::isTypePassword(int iRow)
{
    bool bRetVal;
    if (0 == strcmp("password",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        bRetVal = true;
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}


/**
 * Checks if the type of the specified row in the CSV data is a radio button.
 *
 * @param iRow The row index in the parsed CSV data to check.
 * @return True if the type of the specified row is "radiobutt", false otherwise.
 */
bool schemaCompiler::isTypeRadioButton(int iRow)
{
    if (0 == strcmp("radiobutt",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 * Checks if the type of the specified row is "text".
 *
 * @param iRow The index of the row to check in the parsed data.
 * @return True if the type of the row is "text", false otherwise.
 */
bool schemaCompiler::isTypeText(int iRow)
{
    bool bRetVal;
    if (0 == strcmp("text",
                    gpCsv->m_parsed_data[iRow][COL_TYPE].c_str()))
    {
        bRetVal = true;
    }
    else
    {
        bRetVal = false;
    }
    return bRetVal;
}


/**
 * Constructor for the schemaCompiler class. Initializes the schema compiler
 * with the specified schema name and debug mode. Generates a header file
 * with schema structure if the schema is active and valid.
 *
 * @param ssSchemaName The name of the schema to be compiled.
 * @param bDebug A boolean indicating whether to enable debug mode.
 * @return A schemaCompiler object properly initialized with the provided schema
 *         details.
 */
schemaCompiler::schemaCompiler(std::string ssSchemaName, bool bDebug)
{
    char szTimeStamp[128];
    std::string ssFile = __FILE__;
    std::string ssPath = std::filesystem::path(ssFile).remove_filename();
    ssPath = ssPath.append("schemas/");
    ssPath.append(ssSchemaName);
    ssPath = std::filesystem::path(ssPath).replace_extension(".csv");
    getSchema(ssSchemaName);
    createHeaderFileName(bDebug);
    if (isActiveSchema())
    {
        if (isValidSchemaVersion())
        {
            std::ofstream ofs(m_ssHFN);
            ofs << "/////////////////////////////////////////////"
                << "///////////////////////" << std::endl;
            ofs << "// " << gpSh->m_pShMemng->szHostname << ":" << ssPath
                << "" << std::endl;
            ofs << "// Copyright (c) 2025 Douglas Wade Goodall. "
                << "All rights reserved." << std::endl;
            ofs << "// " << m_ssHeaderFQFS << " Automatically Generated "
                << szTimeStamp << std::endl;
            ofs << "/////////////////////////////////////////////"
                << "///////////////////////" << std::endl;
            ofs << "#include \"../std.h\"" << std::endl;
            std::size_t SNperiod = ssSchemaName.find_last_of(".");
            std::string SNsansType = ssSchemaName.substr(0, SNperiod);
            ofs << "struct schema_" << SNsansType << "_t {" << std::endl;
            for (int iRow = 3; iRow < m_iLines; iRow++)
            {
                if (isRowActive(iRow))
                {
                    m_bHandlePreCheckbox = true;
                    if (isTypePreCheckbox(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_precheckbox_t {\t// precheckbox element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;
                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssName;";
                        ofs << std::endl;
                        ofs << "            std::string ssId;";
                        ofs << std::endl;
                        ofs << "            std::string ssValue;";
                        ofs << std::endl;
                        ofs << "            std::string ssVisible;";
                        ofs << std::endl;
                        ofs << "            std::string ssDescription;";
                        ofs << std::endl;
                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";
                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_ACTIVE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_PREPARA].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_POSTPARA].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_TYPE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_NAME].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_ID].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_VALUE].c_str();
                        ofs << "\"," << std::endl;
                        ofs << "                  \"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_VISIBLE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_DESCRIPTION].c_str();
                        ofs << "\"";
                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandlePostCheckbox = true;
                    if (isTypePostCheckbox(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_postcheckbox_t {\t// postcheckbox element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;
                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssName;";
                        ofs << std::endl;
                        ofs << "            std::string ssId;";
                        ofs << std::endl;
                        ofs << "            std::string ssValue;";
                        ofs << std::endl;
                        ofs << "            std::string ssVisible;";
                        ofs << std::endl;
                        ofs << "            std::string ssDescription;";
                        ofs << std::endl;
                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";
                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_ACTIVE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_PREPARA].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_POSTPARA].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_TYPE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_NAME].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_ID].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_VALUE].c_str();
                        ofs << "\"," << std::endl;
                        ofs << "                  \"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_VISIBLE].c_str();
                        ofs << "\"";
                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data
                            [iRow][COL_CHECKBOX_DESCRIPTION].c_str();
                        ofs << "\"";
                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandleImage = true;
                    if (isTypeImage(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_image_t {\t// image element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;

                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssImageName;";
                        ofs << std::endl;
                        ofs << "            std::string ssWidth;";
                        ofs << std::endl;
                        ofs << "            std::string ssHeight;";
                        ofs << std::endl;
                        ofs << "            std::string ssAltDescription;";
                        ofs << std::endl;

                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";

                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PREPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_POSTPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TYPE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_FILENAME].
                            c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_WIDTH].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_HEIGHT].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][
                            COL_IMAGE_ALTDESCRIPTION].c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandlePassword = true;
                    if (isTypePassword(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_password_t {\t// password element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;
                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssName;";
                        ofs << std::endl;
                        ofs << "            std::string ssValue;";
                        ofs << std::endl;
                        ofs << "            std::string ssSize;";
                        ofs << std::endl;
                        ofs << "            std::string ssVisible;";
                        ofs << std::endl;
                        ofs << "            std::string ssDescription;";
                        ofs << std::endl;
                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";
                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PREPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_POSTPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TYPE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_NAME].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_VALUE].
                            c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_SIZE].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_VISIBLE].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_DESCR].
                            c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandleRadioButton = true;
                    if (isTypeRadioButton(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_radiobutton_t {\t// radiobutton element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;
                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssId;";
                        ofs << std::endl;
                        ofs << "            std::string ssName;";
                        ofs << std::endl;
                        ofs << "            std::string ssValue;";
                        ofs << std::endl;
                        ofs << "            std::string ssLabel;";
                        ofs << std::endl;
                        ofs << "            std::string ssDescription;";
                        ofs << std::endl;
                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";
                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PREPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_POSTPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TYPE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_ID].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_NAME].
                            c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_VALUE].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_LABEL].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_DESCRIPTION]
                            .c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandleText = true;
                    if (isTypeText(iRow))
                    {
                        ofs << "    struct row";
                        ofs << iRow;
                        ofs << "_text_t {\t// text element";
                        ofs << std::endl;
                        ofs << "        struct {";
                        ofs << std::endl;
                        ofs << "            std::string bActive;";
                        ofs << std::endl;
                        ofs << "            std::string bPrePara;";
                        ofs << std::endl;
                        ofs << "            std::string bPostPara;";
                        ofs << std::endl;
                        ofs << "            std::string ssType;";
                        ofs << std::endl;
                        ofs << "            std::string ssName;";
                        ofs << std::endl;
                        ofs << "            std::string ssValue;";
                        ofs << std::endl;
                        ofs << "            std::string ssSize;";
                        ofs << std::endl;
                        ofs << "            std::string ssVisible;";
                        ofs << std::endl;
                        ofs << "            std::string ssDescription;";
                        ofs << std::endl;
                        ofs << "        }row";
                        ofs << iRow;
                        ofs << " = { ";

                        ofs << "\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PREPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_POSTPARA].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TYPE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_NAME].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_VALUE].
                            c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_SIZE].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_VISIBLE].
                            c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_DESCR].
                            c_str();
                        ofs << "\"";
                        ofs << "    };";
                        ofs << std::endl;
                    }
                }
                else
                {
                    // data row not active
                    if (bDebug)
                    {
                        std::cerr << " Schema " << ssSchemaName
                            << " row " << iRow
                            << " not active" << std::endl;
                    }
                }
            }
            ofs << "};" << std::endl;
            ofs.close();
        }
        else
        {
            //meta version is wrong
            if (bDebug)
            {
                std::cerr << "Schema "
                    << ssSchemaName
                    << " wrong version" << std::endl;
            }
        }
    }
    else
    {
        // meta active = false
        std::cerr << "Schema "
            << ssSchemaName
            << " not active"
            << std::endl;
    }
}

//////////////////////////////
// eof - schemaCompiler.cpp //
//////////////////////////////
