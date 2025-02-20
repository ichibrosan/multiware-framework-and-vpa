// advDiagnoseMethod.hpp 2021/12/06 dwg -
// Copyright (c) 2020 RMD Systems.
// Written by Douglas Goodall

#ifndef GAIT_ENGINE_ADVDIAGNOSEMETHOD_HPP
#define GAIT_ENGINE_ADVDIAGNOSEMETHOD_HPP

/**
 * The purpose of this enum is to define parameter indices
 * for the RPC function invocation.
 */
enum ADV_DIAGNOSE_TAG{
    ADV_FUNCTION,       ADV_PARAMETER,    ADV_STRIDEANGLE,
    ADV_VELOCITYFACTOR, ADV_BODYZHEIGHT,  ADV_RIDEHEIGHT,
    ADV_SHIFTLRDELTA,   ADV_SHIFTFBDELTA, ADV_TERMINATOR
};

class advDiagnoseMethod : public xmlrpc_c::method
{
public:
    advDiagnoseMethod()
    {
        this->_signature = "s:iidddddd";
        this->_help      = "diagnostic response";
    };

    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        int const function(paramList.getInt(ADV_FUNCTION));
        int const parameter(paramList.getInt(ADV_PARAMETER));
        double const strideangle(paramList.getDouble(ADV_STRIDEANGLE));
        double const velocityfactor(paramList.getDouble(ADV_VELOCITYFACTOR));
        double const bodyzheight(paramList.getDouble(ADV_BODYZHEIGHT));
        double const rideheight(paramList.getDouble(ADV_RIDEHEIGHT));
        double const shiftlrdelta(paramList.getDouble(ADV_SHIFTLRDELTA));
        double const shiftfbdelta(paramList.getDouble(ADV_SHIFTFBDELTA));
        paramList.verifyEnd(ADV_TERMINATOR);
        xmlrpc_c::value_string const
            param1( g_pModel->diagnose(function,parameter,
                   strideangle,velocityfactor,bodyzheight,rideheight,
                   shiftlrdelta,shiftfbdelta));

        *retvalP = xmlrpc_c::value_string(param1);
    };
};

#endif //GAIT_ENGINE_ADVDIAGNOSEMETHOD_HPP

/////////////////////////////////
// eof - advDiagnoseMethod.hpp //
/////////////////////////////////
