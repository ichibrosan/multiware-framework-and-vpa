////////////////////////////////////////////////////////////////////////
// /home/devo/public_html/fw/dotconfig.h   2025/04/28                 //
// Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved. //
////////////////////////////////////////////////////////////////////////

#ifndef DOTCONFIG_H
#define DOTCONFIG_H



class dotconfig {
    bool m_bCTOR;
public:
    dotconfig();
    bool isConfigDir();
    bool assureConfigDir();
    bool isLicenseUUID();
};



#endif //DOTCONFIG_H
