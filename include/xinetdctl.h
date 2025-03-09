//
// Created by doug on 2/17/25.
//

#ifndef XINETDCTL_H
#define XINETDCTL_H

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

class xinetdctl {
public:
    xinetdctl();
    void trigger(int iPort);
};



#endif //XINETDCTL_H
