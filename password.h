//
// Created by doug on 1/16/25.
//

#ifndef FW_PASSWORD_H
#define FW_PASSWORD_H

#include "std.h"
#include "fw-limits.h"
#include "cgicc.h"
extern Cgicc * gpCgi;

#include "schema.h"

extern schema * gpSchema;
#include "CLog.hpp"
extern CLog * gpLog;
#include "shared.h"
extern shared * gpSh;
#include "readCsv.h"
extern readCsv * gpCsv;


class password {
    schema * m_pSchema;
    int m_iLines;
public:
    password();
    void dump();
    std::string get_uuid();
    int lookup(std::string ssUserName,std::string ssPasssword);
    int lookup_username_password(std::string ssUsername,std::string ssPassword);
};


#endif //FW_PASSWORD_H
