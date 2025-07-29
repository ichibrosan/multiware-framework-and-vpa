////////////////////////////////////////////////////////////////////
// ~/public_html/fw/admin.cpp 2025-07-22 02:16 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include "mwfw2.h"
using namespace std;

void cfgHandler(char * pArgv0)
{
    // Establish addressability to config filespec
    std::string ssCfgFQFS = gpSh->m_pShMemng->szConfigFQDS;
    ssCfgFQFS.append(gpOS->file2filenamesansext(__FILE__));
    ssCfgFQFS.append(".ini");
    cfgini config(ssCfgFQFS.c_str());
    std::string ssCM = "ConfigurationMetadata";
    std::string ssID = "IdentificationDivision";
    std::string ssED = "EnvironmentDivision";
    std::string ssDD = "DataDivision";
    std::string ssPD = "ProcedureDivision";
    // Create a new config or load existing
    if (!config.load())
    {   config.createNew();
        config.addSection(ssID);
        config.addSection(ssED);
        config.addSection(ssDD);
        config.addSection(ssPD);
    }
    config.setVariable(ssCM,"ConfigFileName",ssCfgFQFS);
    config.setVariable(ssID,"ProgramName",pArgv0);
    config.setVariable(ssPD,"FileName",__FILE__);
    config.setVariable(ssED,"SemanticVersion",RSTRING);
    config.setVariable(ssED,"Architecture",RARCH);
    config.setVariable(ssED,"OperatingSystem",ROS);
    config.setVariable(ssED,"DevoIDE",RIDE);
    config.setVariable(ssED,"DevoBuild",RIDEBLD);
    config.setVariable(ssED,"DevoBuilt",RIDEDTG);
    config.setVariable(ssED,"DevoCompiler","clang++");
    config.setVariable(ssID,"Copyright",RCOPR);
    config.save();
}

int
main(int argc, char** argv)
{
    auto* pMwfw = new mwfw2(__FILE__, __FUNCTION__);

    int handle = atoi(gpCgiBind->get_form_variable("handle").c_str());
    std::string ssUsername = gpSh->m_pShMemng->creds[handle].szAuthUserName;

    cfgHandler(argv[0]);

    // Establish addressability to schema filespec
    std::string ssSchema = gpOS->file2filenamesansext(__FILE__);
    ssSchema.append(".csv");
    gpSchema = new schema(ssSchema.c_str());
    gpSchema->gen_from_schema(handle,
        LOGOUT | SHUTDOWN,
        __FILE__,
        ssUsername,
        "passwd");

    if (pMwfw->isCGI()) { gpHtml->dumps(); }

    return EXIT_SUCCESS;
}
