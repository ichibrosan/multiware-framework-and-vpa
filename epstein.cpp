//////////////////////////////////////////////////////////////////////
// ~/public_html/fw/epstein.cpp 2025-11-15 01:53 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork   //
//////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////


#include "mwfw2.h"

std::string getSectionFQFS(std::string ssFileNum)
{
    return("baddata");

}

int main(int argc, char** argv)
{
    auto* pMwFw = new mwfw2(__FILE__, __FUNCTION__);

    auto* pWin = new window();
    
    gpSemiGr->cosmetics(
        SRUL, SRUR, SRLL,
        // Corner characters: ┌ ┐ └ ┘
        SRLR, SVSR, SVSL,
        // Right corner and separators
        SH, SV);
        // Horizontal ─ and vertical │ lines
    
    char szVersion[64];
    sprintf(szVersion, "Epstein Utility "
            "Ver %d.%d.%d.%d", RMAJ, RMIN, RREV, RBLD);
    pWin->set_title(szVersion);
    
    std::string ssCopr =
        "Creative Commons CC0 1.0 Universal Public Domain Dedication";
    pWin->add_row(ssCopr);
    pWin->add_row("Written by Douglas Wade Goodall, Multiware Engineer");

    std::string ssCfgFQFS = gpSh->m_pShMemng->szConfigFQDS;
    ssCfgFQFS.append(gpOS->file2filenamesansext(__FILE__));
    ssCfgFQFS.append(".ini");

    cfgini config(ssCfgFQFS.c_str());
    
    std::string ssCM = "ConfigurationMetadata";    // metadata
    std::string ssID = "IdentificationDivision";   // Program identity
    std::string ssED = "EnvironmentDivision";      // Runtime environment
    std::string ssDD = "DataDivision";             // Data-related config
    std::string ssPD = "ProcedureDivision";        // Procedural config
    
    if (!config.load())
    {   
        // Create new configuration file with structured sections
        config.createNew();
        config.addSection(ssID);    // Program identification
        config.addSection(ssED);    // Environment information  
        config.addSection(ssDD);    // Data configuration (reserved)
        config.addSection(ssPD);    // Procedural configuration
    }
    
    config.setVariable(ssCM, "ConfigFileName", ssCfgFQFS);
    
    config.setVariable(ssID, "ProgramName", argv[0]);
    config.setVariable(ssID, "License", RCOPR);

    config.setVariable(ssPD, "FileName", __FILE__);

    config.setVariable(ssED, "SemanticVersion", RSTRING);
    config.setVariable(ssED, "Architecture", RARCH);
    config.setVariable(ssED, "OperatingSystem", ROS);
    config.setVariable(ssED, "DevoIDE", RIDE);
    config.setVariable(ssED, "DevoCompiler", "clang++");

    config.save();

    char szTemp[128];
    sprintf(szTemp, "Config file: %s", ssCfgFQFS.c_str());
    pWin->add_row(szTemp);

    std::string ssOptCSV = "20250822-opt.csv";
    sprintf(szTemp, "OPT file: %s", ssOptCSV.c_str());
    pWin->add_row(szTemp);
    readCsv * pCsvOpt = new readCsv(ssOptCSV);
    pCsvOpt->parseData();
    int iOptLines = pCsvOpt->getLines();
    sprintf(szTemp, "OPT file has %d lines", iOptLines);
    pWin->add_row(szTemp);

    std::string ssTifCSV = "20250822-tif.csv";
    sprintf(szTemp, "TIF file: %s", ssTifCSV.c_str());
    pWin->add_row(szTemp);
    readCsv * pCsvTif = new readCsv(ssTifCSV);
    pCsvTif->parseData();
    int iTifLines = pCsvTif->getLines();
    sprintf(szTemp, "TIF file has %d lines", iTifLines);
    pWin->add_row(szTemp);



    FILE * fd = fopen("/home/doug/public_html/fw/html/datafile.html","w");
    fprintf(fd,"<!DOCTYPE html>\n");
    fprintf(fd,"<html lang=\"en\">\n");
    fprintf(fd,"<head>\n");
    fprintf(fd,"    <meta charset=\"UTF-8\">\n");
    fprintf(fd,"    <title>Title</title>\n");
    fprintf(fd,"</head>\n");
    fprintf(fd,"<body>\n");

    iOptLines = 10;
    for (int index=0; index<iOptLines; index++)
    {

        std::string ssImgFQFS = "http://localhost/~doug/epstein/DOJ_Epstein_Files_First_Production/";
        std::string ssField2  = pCsvOpt->getData(index,2);

        std::string ssImgFrag = ssField2.substr(2,ssField2.length());

        ssImgFQFS.append(ssImgFrag);
        sprintf(szTemp,"ssImgFQFS: %s",ssImgFQFS.c_str());
        pWin->add_row(szTemp);

        fprintf(fd,"<p><img src=\"%s\" width=\"1024\" height=\"768\">\n",ssImgFQFS.c_str());

    }
    pWin->render();
    fprintf(fd,"</body>\n");
    fprintf(fd,"</html>\n");
    fclose(fd);
    return EXIT_SUCCESS;
}
