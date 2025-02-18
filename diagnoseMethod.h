//////////////////////////////////////////////////////////////////////////////
// daphne.goodall.com:/home/doug/public_html/fw/diagnoseMethod.h 2025/02/12 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.       //
//////////////////////////////////////////////////////////////////////////////

#ifndef DIAGNOSEMETHOD_H
#define DIAGNOSEMETHOD_H

/**
 * @class diagnoseMethod
 * @brief A class that implements an XML-RPC method for diagnostic purposes.
 *
 * This class inherits from `xmlrpc_c::method` and provides a diagnostic
 * method implementation. It sets its signature and help description,
 * and the method can be invoked via XML-RPC.
 */
class diagnoseMethod : public xmlrpc_c::method {
    /**
     * Constructs the `diagnoseMethod` class and initializes its member
     * documentation for XML-RPC functionality. This includes the method
     * signature and help description.
     *
     * @return A constructed instance of the `diagnoseMethod` class with
     *         predefined signature and help strings.
     */
public:
    diagnoseMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:iis";  // method's arguments are two integers
        this->_help = "This method adds two integers together";
    }

    /**
     * Executes the XML-RPC method.
     *
     * This method processes the input parameters, constructs a formatted string indicating
     * method execution information, and sets the resulting string as the return value.
     *
     * @param paramList The list of input parameters provided to the method.
     *                  It is expected to contain two integers as input arguments.
     * @param retvalP Pointer to the xmlrpc_c::value object that will hold
     *                the result of the method execution.
     */
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

        int const func(paramList.getInt(0));
        int const parm(paramList.getInt(1));
        std::string auth(paramList.getString(2));
        paramList.verifyEnd(3);

        char szPayload[FILENAME_MAX];
         if (0 == strcmp(auth.c_str(),
                        gpSh->m_pShMemng->szRpcUuid)) {

            sprintf(szPayload, "%s::%s() on %s at line %d %s",
                __FILE__,__FUNCTION__,__DATE__,__LINE__,
                gpSh->m_pShMemng->szStylesRoot

                );
        } else {
            strcpy(szPayload,"Synchronization Error!!");
        }

        *retvalP = xmlrpc_c::value_string(szPayload);
    }
};

#endif //DIAGNOSEMETHOD_H
