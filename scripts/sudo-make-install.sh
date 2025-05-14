#!/bin/bash
#####################################################################
# /home/devo/public_html/fw/scripts/sudo-make-install.sh 2025-05-13 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.     #
#####################################################################
clear

## Make Phase
#rm -r -f                ~/public_html/fw/build
#mkdir                   ~/public_html/fw/build
#cd                      ~/public_html/fw/build
#cmake ..
#make
#cp -v *.cgi             ~/public_html/fw/cgi-bin/
#cp -v fw                ~/public_html/fw/bin/
#cp -v look              ~/public_html/fw/bin/
#cp -v libmwfw*.a        ~/public_html/fw/lib/
#rm -f                   ~/public_html/fw/bin/vpad
#cp -v vpad*             ~/public_html/fw/bin/
#cp -v xmlrpc*           ~/public_html/fw/bin/
#cp -v prefs*            ~/public_html/fw/bin/
#ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem

# Install Phase
cd                      ~/public_html/fw
sudo mkdir -p /usr/local/include/multiware/mwfw2
sudo cp -v include/mwfw2.h           /usr/local/include/multiware/mwfw2/
sudo cp -v include/mutations.h       /usr/local/include/multiware/mwfw2/
sudo cp -v include/crtbind.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/semigraphics.h    /usr/local/include/multiware/mwfw2/
sudo cp -v include/window.h          /usr/local/include/multiware/mwfw2/
sudo cp -v include/dotconfig.h       /usr/local/include/multiware/mwfw2/
sudo cp -v include/shared.h          /usr/local/include/multiware/mwfw2/
sudo cp -v include/shMemMutex.h      /usr/local/include/multiware/mwfw2/
sudo cp -v include/shMemMgr.h        /usr/local/include/multiware/mwfw2/
sudo cp -v include/cgibind.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/cgihtml.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/CLog.hpp          /usr/local/include/multiware/mwfw2/
sudo cp -v include/CSysLog.hpp       /usr/local/include/multiware/mwfw2/
sudo cp -v include/dashboard.h       /usr/local/include/multiware/mwfw2/
sudo cp -v include/environment.h     /usr/local/include/multiware/mwfw2/
sudo cp -v include/osIface.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/password.h        /usr/local/include/multiware/mwfw2/
sudo cp -v include/readCsv.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/schema.h          /usr/local/include/multiware/mwfw2/
sudo cp -v include/schemaCompiler.h  /usr/local/include/multiware/mwfw2/
sudo cp -v include/test.h            /usr/local/include/multiware/mwfw2/
sudo cp -v include/config.h          /usr/local/include/multiware/mwfw2/
sudo cp -v include/xinetdctl.h       /usr/local/include/multiware/mwfw2/
sudo cp -v include/version.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/stylist.h         /usr/local/include/multiware/mwfw2/
sudo cp -v include/iHex.h            /usr/local/include/multiware/mwfw2/
sudo cp -v include/diagnose.h        /usr/local/include/multiware/mwfw2/
sudo cp -v include/vpadiscclient.h   /usr/local/include/multiware/mwfw2/
sudo cp -v include/vpadiscserver.h   /usr/local/include/multiware/mwfw2/

cd                      ~/public_html/fw/build
sudo mkdir -p /usr/local/lib/multiware/mwfw2
sudo cp -v libmwfw*.a   /usr/local/lib/multiware/mwfw2/

