////////////////////////////////////////////////////////////////////
// ~/public_html/fw/xinetdctl.h 2025-07-16 08:08 dwg -            //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////

#pragma once

/*
 * See /etc/services for assigned and dynamic port definitions
 */
#define VPA_PORT          5164    // services: vpa/tcp vpa-disc/udp
#define VPAD_START_PORT  65353    // services: vpad-start
#define VPA_NETSTAT_PORT 65354    // services: vpa-netstat
#define VPA_IP_PORT      65355    // services: vpa-ip
#define VPA_CURL_PORT    65356    // services: vpa-curl
#define VPA_HTTP_PORT    65357    // services: vpa-http
#define VPA_HTTPS_PORT   65358    // services: vpa-https
#define VPA_IPCS_PORT    65359    // services: vpa-ipcs

class xinetdctl
{
public:
    xinetdctl();
    void trigger(int iPort);
};

///////////////////////
// eof - xinetdctl.h //
///////////////////////
