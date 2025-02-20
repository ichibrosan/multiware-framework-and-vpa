////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnosticMethod.hpp 2025/02/20          //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef MULTIWARE_DIAGNOSEMETHOD_HPP
#define MULTIWARE_DIAGNOSEMETHOD_HPP

#include "std.h"

/**
 * The purpose of this enum is to define parameter indices
 * for the RPC function invocation.
 */
enum {
    FUNCTION,
    PARAMETER,
    TERMINATOR
};


class diagnoseMethod : public xmlrpc_c::method
{
    char m_szTemp[128];
public:

    diagnoseMethod()
    {
        this->_signature = "s:ii";
        this->_help      = "diagnostic response";
    };

    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        int const function(paramList.getInt(FUNCTION));
        int const parameter(paramList.getInt(PARAMETER));
           paramList.verifyEnd(TERMINATOR);

        xmlrpc_c::value_string const
            param1( g_pModel->diagnose(
                function, parameter));

        *retvalP = xmlrpc_c::value_string(param1);
    };

};

#endif // MULTIWARE_DIAGNOSEMETHOD_HPP

//////////////////////////////
// eof - diagnoseMethod.hpp //
//////////////////////////////
