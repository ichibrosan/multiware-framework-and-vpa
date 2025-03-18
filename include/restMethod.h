///////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/restMethod.h 2025-03-18 03:40       //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#ifndef RESTMETHOD_H
#define RESTMETHOD_H

/**
 * @brief Array of request names for the Virtual Protocol Adapter.
 *
 * This array contains string constants representing various request
 * types that the VPAD system can handle. These names are typically
 * used for logging or identifying a specific request type in the
 * system's request handling logic.
 *
 * The available request types are:
 * - "VERSION" : Request related to system version.
 * - "AUTH"    : Request for authentication.
 * - "PARMS"   : Request for parameters.
 * - "STATUS"  : Request for system status.
 * - "TERM"    : Request to terminate the system.
 */
const char * rest_req_names[] = {
    "GET",
    "HEAD",
    "OPTIONS",
    "PUT",
    "DELETE",
    "POST"
};

/**
 * @brief Array of strings representing the names of variable parameter types.
 *
 * This array is used to map integer type identifiers to their corresponding
 * string representations, providing a way to handle and log different types
 * of variable parameters (e.g., NONE, INT, STRING, FLOAT, BOOL) within the
 * system.
 *
 * @note The order of elements in the array should correspond to the
 * enumerated values or integer representations of the types used in the
 * application.
 */
const char * rest_type_names[] = {
    "NONE",
    "INT",
    "STRING",
    "FLOAT",
    "BOOL"
};

class restMethod : public xmlrpc_c::method {
public:
    restMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:iiisiss";
            // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
    }

    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) override {

        std::string ssBuffer;

        int const iParm1(paramList.getInt(0));
        int const iParm2(paramList.getInt(1));
        int const iParm3Type(paramList.getInt(2));
        std::string ssParm3(paramList.getString(3));
        int const iParm4Type(paramList.getInt(4));
        std::string ssParm4(paramList.getString(5));
        std::string ssAuth(paramList.getString(6));
        paramList.verifyEnd(7);
        char szPayload[FILENAME_MAX];

        sprintf(szPayload,
            "Server RPC: P1=%s,P2=%d,P3Type=%s,"
                  "P3=%s,P4Type=%s,P4=%s,ssAuth=%s",
            rest_req_names[iParm1],iParm2,
            rest_type_names[iParm3Type],ssParm3.c_str(),
            rest_type_names[iParm4Type],ssParm4.c_str(),ssAuth.c_str());
        gpSysLog->loginfo(szPayload);
        switch (iParm1) {
            case RESTFUL_REQ_GET:
                if (0 == strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
                   *retvalP = xmlrpc_c::value_string(RVERSION_STRING_LONG);
                } else {
                    sleep(10); // make them pay a time penalty to obviate attacks
                   *retvalP = xmlrpc_c::value_string("Synchronization Error!!");
                }
                break;
            case RESTFUL_REQ_HEAD:
                break;
            case RESTFUL_REQ_OPTIONS:
                break;
            case RESTFUL_REQ_PUT:
                break;
            case RESTFUL_REQ_DELETE:
                break;
            case RESTFUL_REQ_POST:
                break;
            default:
                *retvalP = xmlrpc_c::value_string("Unknown Request");
        }
    }
};

#endif //RESTMETHOD_H
