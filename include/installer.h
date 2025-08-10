////////////////////////////////////////////////////////////////////
// ~/public_html/fw/install.h 2025-08-09 09:30 dwg -              //
// This file is part of MultiWare Engineering's VPA and FrameWork //
////////////////////////////////////////////////////////////////////
// This file is made available under the                          //
// Creative Commons CC0 1.0 Universal Public Domain Dedication.   //
////////////////////////////////////////////////////////////////////

#pragma once
#include "mwfw2.h"

class installer
{

private:
        window * m_pWin;
public:
        installer();
        bool is_devo_root();
        bool can_user_sudo();
        bool is_etc_installer();
        bool is_xinetd_installed();
        bool is_xinet_configured();
        bool is_apache2_installed();
        bool check_userdir_enabled();
        bool check_userdir_execcgi();
        bool check_dir_index_cgi();
        bool add_index_cgi_to_dir();
        bool check_apache2_servername();
        bool check_apache2_addtype();
        bool add_apache2_addtype();
        ~installer();
};

///////////////////////
// eof - installer.h //
///////////////////////