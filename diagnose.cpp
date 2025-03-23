///////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/diagnose.cpp 2025-03-23 00:57       //
// Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. //
///////////////////////////////////////////////////////////////////

#include "mwfw2.h"
#include "include/diagnose.h"
using namespace std;

/**
 * @brief Constructor for the `diagnose` class. Initializes and sends an
 * XML-RPC request to a specified server node for authentication.
 *
 * This constructor sets up the URL, method name, and format for the XML-RPC
 * request. It then constructs a `diagnose_request_t` request
 * object and sends the request using an `xmlrpc_c::clientSimple` object.
 * Upon successful completion, it stores the authentication token
 * in the shared memory and outputs it to the console.
 *
 * @param ssNodeIP The IP address of the server node to communicate with.
 *
 * This implementation performs the following:
 * - Constructs the full URL for the XML-RPC server using shared memory
 *   values and a predefined port.
 * - Creates and populates a `diagnose_request_t` structure for the request
 *   with appropriate values.
 * - Sends an XML-RPC request using the provided format and method, then
 *   retrieves the authentication token from the server's response.
 * - Updates shared memory with the new authentication token and outputs it.
 *
 * Exceptions:
 * - Catches and outputs errors thrown by the XML-RPC client or any
 *   unexpected exceptions.
 */
diagnose::diagnose(std::string ssNodeIP) {
    char szPort[8];
    sprintf(szPort,"%d",VPA_PORT);

    m_ssNodeIP = ssNodeIP;
    m_ssMethod = "diagnose";
    m_ssFormat = "iiisiss";
    m_ssUrl = gpSh->m_pShMemng->szProtocol;
    m_ssUrl.append(gpSh->m_pShMemng->szRemoteAddr);
    m_ssUrl.append(":");
    m_ssUrl.append(szPort);
    m_ssUrl.append("/RPC2");

    diagnose_request_t request;
    strcpy(request.szRemoteHost,m_ssNodeIP.c_str());
    strcpy(request.szFormat,m_ssFormat.c_str());
           request.eReqFunc = DIAGNOSE_REQ_AUTH;
           request.eParm3Type = DIAGNOSE_TYPE_NONE;
           request.eParm4Type = DIAGNOSE_TYPE_NONE;
    strcpy(request.szAuth,VPA_RPC_PSK);

    string ssValueRetcode;
    try {
        string const serverUrl(m_ssUrl);
        string const methodName(m_ssMethod);
        xmlrpc_c::clientSimple diagnoseClient;
        xmlrpc_c::value result;
        diagnoseClient.call(
            m_ssUrl,
            m_ssMethod,
            m_ssFormat,
            &result,
            request.eReqFunc,
            request.iParm2,
            request.eParm3Type,
            request.szParm3,
            request.eParm4Type,
            request.szParm4,
            VPA_RPC_PSK);
        m_ssAuth = xmlrpc_c::value_string(result);
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    strcpy(gpSh->m_pShMemng->szRemoteAuth,m_ssAuth.c_str());
    std::cout << "Remote Auth Token is: " << m_ssAuth << std::endl;

}

/**
 * Executes a remote procedure call to a diagnostics server using XML-RPC
 * based on the input request parameters and returns the result as a string.
 *
 * @param request A reference to a `diagnose_request_t` structure containing
 *                the parameters required for the XML-RPC call, including
 *                function type, parameters, and authentication details.
 *
 * @return A string containing the response from the server if the call was
 *         successfully executed. Returns an empty string if an error occurs.
 *
 * @throws Handles and reports general exceptions and unexpected errors during
 *         the execution of the XML-RPC call.
 */
string diagnose::diagnoseCall(diagnose_request_t& request) {
    string ssValueRetcode;
    try {
        xmlrpc_c::clientSimple diagnoseClient;
        xmlrpc_c::value result;
        diagnoseClient.call(
            m_ssUrl,
            m_ssMethod,
            m_ssFormat,
            &result,
            request.eReqFunc,
            request.iParm2,
            request.eParm3Type,
            request.szParm3,
            request.eParm4Type,
            request.szParm4,
            m_ssAuth.c_str());
        ssValueRetcode = xmlrpc_c::value_string(result);
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }
    return ssValueRetcode;
}