//
// Created by doug on 3/23/25.
//

#ifndef DIAGNOSE_H
#define DIAGNOSE_H

#include "std.h"
#include "mwfw2.h"

class diagnose {
    std::string m_ssNodeIP;
    std::string m_ssUrl;
    std::string m_ssMethod;
    std::string m_ssFormat;
    std::string m_ssAuth;
public:
    diagnose(std::string ssNodeIP);
    std::string diagnoseCall(diagnose_request_t& request);
};



#endif //DIAGNOSE_H
