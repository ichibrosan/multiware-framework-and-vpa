///////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/schemaCompiler.cpp 2025/01/10//
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.        //
///////////////////////////////////////////////////////////////////////////////
///

#include "std.h"
#include "osIface.h"
extern osIface * gpOS;
#include "schema.h"
#include "schemaCompiler.h"
#include "readCsv.h"
extern readCsv * gpCsv;
#include "CLog.hpp"
#include "shared.h"
extern shared * gpSh;

//#include "login.h"


/******************************************************
 * Read and parse a new schema by name
 * @param ssSchemaName
 ******************************************************/
void schemaCompiler::getSchema(std::string ssSchemaName)
{
    m_ssSN = ssSchemaName;
    gpCsv = new readCsv(m_ssSN);
    gpCsv->parseData();
    m_iLines = gpCsv->m_iRow;
}


/***************************************************************
 * Create a header file name from a schema name, save in m_ssHFN
 * @param bDebug
 ***************************************************************/
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


/************************************
 * Is the current schema active?
 * @return Boolean true or false
 ************************************/
bool schemaCompiler::isActiveSchema()
{
    if(0 == strcmp("true",
        gpCsv->m_parsed_data[ROW_META_DATA][COL_META_ACTIVE].c_str())) {
        return true;
    } else {
        return false;
    }
}


/*******************************************
 * Is the current schema a valid version?
 * @return
 *******************************************/
bool schemaCompiler::isValidSchemaVersion()
{
    if(0 == strcmp("1",
        gpCsv->m_parsed_data[ROW_META_DATA][COL_META_VERSION].c_str())) {
        return true;
    } else {
        return false;
    }
}


/***********************************************************************
 * Is the current schema row active?
 * @param iRow
 * @return
 ***********************************************************************/
bool schemaCompiler::isRowActive(int iRow)
{
    if(0 == strcmp("true",
        gpCsv->m_parsed_data[iRow][COL_ACTIVE].c_str())) {
        return true;
    } else {
        return false;
    }
}


/************************************************************************
 * is the element type of the current row "precheckbox"?
 * @param iRow
 * @return
 ************************************************************************/
bool schemaCompiler::isTypePreCheckbox(int iRow)
{
    bool bRetVal;
    if(0 == strcmp("precheckbox",
                gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
            bRetVal = true;
        } else {
            bRetVal = false;
        }
    return bRetVal;
}


/******************************************************************
 * is the element type of the current row "postcheckbox"?
 * @param iRow
 * @return
 ******************************************************************/
bool schemaCompiler::isTypePostCheckbox(int iRow)
{
    bool bRetVal;
    if(0 == strcmp("precheckbox",
                   gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
        bRetVal = true;
    } else {
        bRetVal = false;
    }
    return bRetVal;
}


/****************************************************
 * is the element type of the current row "image"?
 * @param iRow
 * @return
 ****************************************************/
bool schemaCompiler::isTypeImage(int iRow)
{
    bool bRetVal;
    if(0 == strcmp("image",
                   gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
        bRetVal = true;
    } else {
        bRetVal = false;
    }
    return bRetVal;
}


/*****************************************************
 * is the element type of the current row "passsword"?
 * @param iRow
 * @return
 *****************************************************/
bool schemaCompiler::isTypePassword(int iRow)
{
    bool bRetVal;
    if(0 == strcmp("password",
                   gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
        bRetVal = true;
    } else {
        bRetVal = false;
    }
    return bRetVal;
}


/********************************************************
 * is the element type of the current row "radiobutton"?
 * @param iRow
 * @return
 ********************************************************/
bool schemaCompiler::isTypeRadioButton(int iRow)
{
    if(0 == strcmp("radiobutt",
                   gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
        return true;
    } else {
        return false;
    }
}


/************************************************
 * is the element type of the current row "text"?
 * @param iRow
 * @return
 ************************************************/
bool schemaCompiler::isTypeText(int iRow)
{
    bool bRetVal;
    if(0 == strcmp("text",
        gpCsv->m_parsed_data[iRow][COL_TYPE].c_str())) {
        bRetVal = true;
    } else {
        bRetVal = false;
    }
    return bRetVal;
}


/*******************************************************************
 * This is the constructor for the Schema Compiler
 * @param ssSchemaName
 * @param bDebug
 *******************************************************************/
schemaCompiler::schemaCompiler(std::string ssSchemaName,bool bDebug)
{
    char szTimeStamp[128];
    std::string ssFile = __FILE__;
    std::string ssPath = std::filesystem::path(ssFile).remove_filename();
                ssPath = ssPath.append("schemas/");
                ssPath.append(ssSchemaName);
                ssPath = std::filesystem::path(ssPath).replace_extension(".csv");
    getSchema(ssSchemaName);
    createHeaderFileName(bDebug);
    if(isActiveSchema()) {
        if(isValidSchemaVersion()) {
            std::ofstream ofs(m_ssHFN);
            ofs << "/////////////////////////////////////////////"
                << "///////////////////////" << std::endl;
            ofs << "// " << gpSh->m_pShMemng->szHostname << ":" << ssPath
                << ""   << std::endl;
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
            for (int iRow = 3; iRow < m_iLines; iRow++) {
                if(isRowActive(iRow)) {

                    m_bHandlePreCheckbox = true;
                    if(isTypePreCheckbox(iRow)) {
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
                                [iRow][COL_ACTIVE ].c_str();
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
                    if(isTypePostCheckbox(iRow)) {
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
                                [iRow][COL_ACTIVE ].c_str();
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
                                [iRow][COL_CHECKBOX_ID].c_str();                        ofs << "\"";
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
                    if(isTypeImage(iRow)) {
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE ].c_str();
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_FILENAME].c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_WIDTH].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_HEIGHT].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_IMAGE_ALTDESCRIPTION].c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandlePassword = true;
                    if(isTypePassword(iRow)) {
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE ].c_str();
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_NAME].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_VALUE].c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_SIZE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_VISIBLE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_PASSWORD_DESCR].c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandleRadioButton = true;
                    if(isTypeRadioButton(iRow)) {
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE ].c_str();
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_NAME].c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_VALUE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_LABEL].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_RADIO_DESCRIPTION].c_str();
                        ofs << "\"";

                        ofs << "};";
                        ofs << std::endl;
                        ofs << "    };";
                        ofs << std::endl;
                    }

                    m_bHandleText = true;
                    if(isTypeText(iRow)) {
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_ACTIVE ].c_str();
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
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_NAME].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_VALUE].c_str();
                        ofs << "\",";
                        ofs << std::endl;

                        ofs << "                   \"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_SIZE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_VISIBLE].c_str();
                        ofs << "\"";

                        ofs << ",\"";
                        ofs << gpCsv->m_parsed_data[iRow][COL_TEXT_DESCR].c_str();
                        ofs << "\"";
                        ofs << "    };";
                        ofs << std::endl;
                    }
                } else {
                    // data row not active
                    if(bDebug) {
                        std::cerr << " Schema " << ssSchemaName
                                  << " row " << iRow
                                  << " not active" << std::endl;
                    }
                }
            }
            ofs << "};" << std::endl;
            ofs.close();
        } else {
            //meta version is wrong
            if (bDebug) {
                std::cerr << "Schema "
                          << ssSchemaName
                          << " wrong version" << std::endl;

            }
        }
    } else {
        // meta active = false
        std::cerr   << "Schema "
                    <<  ssSchemaName
                    << " not active"
                    << std::endl;
    }
}

//////////////////////////////
// eof - schemaCompiler.cpp //
//////////////////////////////
