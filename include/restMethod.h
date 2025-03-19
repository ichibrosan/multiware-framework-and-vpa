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
const char * rest_req_func_names[] = {
    "GET","HEAD","OPTIONS","PUT","DELETE","POST"
};

const char * rest_req_get_names[] = {
    "VER"
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
    "NONE","INT","STRING","FLOAT","BOOL"
};

class restMethod : public xmlrpc_c::method {
public:
    restMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:iiisiss";
        this->_help = "This method is a multipurpose interface to mwfw";
    }

    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) override {

        std::string ssBuffer;
        char szErrMsg[FILENAME_MAX];

        int const iFunc(paramList.getInt(0));
        REST_REQ_FUNCS_T eFunc = (REST_REQ_FUNCS_T)iFunc;
        int const iSubFunc(paramList.getInt(1));
        REST_REQ_SUBFNS_T eSubFunc = (REST_REQ_SUBFNS_T)iSubFunc;

        int const iParm3Type(paramList.getInt(2));
        std::string ssParm3(paramList.getString(3));

        int const iParm4Type(paramList.getInt(4));
        std::string ssParm4(paramList.getString(5));

        std::string ssAuth(paramList.getString(6));

        paramList.verifyEnd(7);

        char szPayload[FILENAME_MAX];

        if (0 != strcmp(ssAuth.c_str(),gpSh->m_pShMemng->szRpcUuid)) {
            sleep(10); // make them pay a time penalty
            *retvalP = xmlrpc_c::value_string(
                "Synchronization Error!!");
        }

        sprintf(szPayload,
            "VPA Server RPC: Func=%s,SubFunc=%s,P3Type=%s,"
                  "P3=%s,P4Type=%s,P4=%s,Auth=%s",
            rest_req_func_names[iFunc],rest_req_get_names[iSubFunc],
            rest_type_names[iParm3Type],ssParm3.c_str(),
            rest_type_names[iParm4Type],ssParm4.c_str(),ssAuth.c_str());
        gpSysLog->loginfo(szPayload);
        switch (eFunc) {
            case REST_REQ_GET:
                if (REST_REQ_SUB_VER == eSubFunc) {
                   *retvalP = xmlrpc_c::value_string(
                       RVERSION_STRING_LONG);
                } else {
                    sleep(10); // make them pay a time penalty
                    sprintf(szErrMsg,"Error!! Unknown SubFunc(%d)",
                        eSubFunc);
                   *retvalP = xmlrpc_c::value_string(szErrMsg);
                }
                break;
            case REST_REQ_HEAD:
                break;
            case REST_REQ_OPTIONS:
                break;
            case REST_REQ_PUT:
                break;
            case REST_REQ_DELETE:
                break;
            case REST_REQ_POST:
                break;
            default:
                *retvalP = xmlrpc_c::value_string("Unknown Request");
        }
    }
};

#endif //RESTMETHOD_H
