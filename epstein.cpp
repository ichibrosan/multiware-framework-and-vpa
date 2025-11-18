//////////////////////////////////////////////////////////////////////
// ~/public_html/fw/epstein.cpp 2025-11-15 01:53 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork   //
//////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////


#include "mwfw2.h"

void do_config(char * argv0)
{
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
    config.setVariable(ssID, "ProgramName", argv0);
    config.setVariable(ssID, "License", RCOPR);
    config.setVariable(ssPD, "FileName", __FILE__);
    config.setVariable(ssED, "SemanticVersion", RSTRING);
    config.setVariable(ssED, "Architecture", RARCH);
    config.setVariable(ssED, "OperatingSystem", ROS);
    config.setVariable(ssED, "DevoIDE", RIDE);
    config.setVariable(ssED, "DevoCompiler", "clang++");
    config.save();
}

void do_conversions(int iLines)
{
}

int main(int argc, char** argv)
{
    char szTemp[FILENAME_MAX];

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

    do_config(argv[0]);

    std::string ssCSV = "20250822.csv";
    sprintf(szTemp, "CSV file: %s", ssCSV.c_str());
    pWin->add_row(szTemp);
    readCsv * pCsv = new readCsv(ssCSV);
    pCsv->parseData();
    int iLines = pCsv->getLines();
    sprintf(szTemp, "CSV file has %d lines", iLines);
    pWin->add_row(szTemp);

    // std::string ssTifCSV = "20250822-tif.csv";
    // sprintf(szTemp, "TIF file: %s", ssTifCSV.c_str());
    // pWin->add_row(szTemp);
    // readCsv * pCsvTif = new readCsv(ssTifCSV);
    // pCsvTif->parseData();
    // int iTifLines = pCsvTif->getLines();
    // sprintf(szTemp, "TIF file has %d lines", iTifLines);
    // pWin->add_row(szTemp);

    // DO CONVERSIONS
    // std::string ssImgBase = "/home/doug/public_html/epstein/DOJ_Epstein_Files_First_Production/";
    // for (int index=0; index<iTifLines; index++)
    // {
    //     std::string ssSrcFQFS = ssImgBase;
    //     std::string ssField1 = pCsvTif->getData(index,2);
    //     std::string ssSrcFrag = ssField1.substr(2,ssField1.length());
    //     ssSrcFQFS.append(ssSrcFrag);
    //     //pWin->add_row(ssSrcFQFS);
    //
    //     std::string ssDstFQFS = ssSrcFQFS.substr(0,ssSrcFQFS.length()-4);
    //     ssDstFQFS.append(".jpg");
    //     //pWin->add_row(ssDstFQFS);
    //
    //     std::string ssCmd = "magick " + ssSrcFQFS + " " + ssDstFQFS;
    //     //pWin->add_row(ssCmd);
    //     std::cout << ssCmd << std::endl;
    //     system(ssCmd.c_str());
    //
    //     //std::string ssRmCmd = "rm " + ssSrcFQFS;
    //     //system(ssRmCmd.c_str());
    // }

    FILE * fd = fopen("/home/doug/public_html/fw/html/datafile.html","w");
    fprintf(fd,"<!DOCTYPE html>\n");
    fprintf(fd,"<html lang=\"en\">\n");
    fprintf(fd,"<head>\n");
    fprintf(fd,"    <meta charset=\"UTF-8\">\n");
    fprintf(fd,"    <title>Title</title>\n");
    fprintf(fd,"</head>\n");
    fprintf(fd,"<body>\n");


    for (int index=0; index<iLines; index++)
    {

        std::string ssImgFQFS = "http://localhost/~doug/epstein/DOJ_Epstein_Files_First_Production/";
        std::string ssField2  = pCsv->getData(index,2);

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
