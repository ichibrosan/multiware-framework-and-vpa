//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/schemaCompiler.h 2025/01/10 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#ifndef INDEX_CGI_SCHEMACOMPILER_H
#define INDEX_CGI_SCHEMACOMPILER_H

#include "std.h"
#include "readCsv.h"

class schemaCompiler {
    int m_iLines;
    int m_iRow;
    std::size_t m_lastPeriodOffset;
    std::string m_ssSN;
    std::string m_ssHFN;
    std::string m_ssPathFNsansType;
    std::string m_ssHeaderFQFS;
    readCsv * m_pCsv;
public:

    schemaCompiler(std::string ssSchemaName,bool bDebug);

    void createHeaderFileName(bool bDebug);
    void getSchema(std::string);
    bool isActiveSchema();
    bool isValidSchemaVersion();
    bool isRowActive(int);
    bool isTypePostCheckbox(int);
    bool isTypePreCheckbox(int);
    bool isTypeImage(int);
    bool isTypeRadioButton(int);
    bool isTypeText(int);
    bool isTypePassword(int);

    bool m_bHandleImage;
    bool m_bHandlePassword;
    bool m_bHandlePostCheckbox;
    bool m_bHandlePreCheckbox;
    bool m_bHandleRadioButton;
    bool m_bHandleText;
    bool m_bHandleTextArea;
} ;


#endif //INDEX_CGI_SCHEMACOMPILER_H
