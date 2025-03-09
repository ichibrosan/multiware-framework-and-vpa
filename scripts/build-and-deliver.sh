#!/bin/bash
#####################################################################
# /home/devo/public_html/fw/scripts/build-and-deliver.sh 2025-03-09 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.     #
#####################################################################
clear
cp -v /etc/xinetd.d/vpa ~/public_html/fw/doc/
rm -r -f                ~/public_html/fw/build
mkdir                   ~/public_html/fw/build
cd                      ~/public_html/fw/build
cmake ..
make
cp -v *.cgi             ~/public_html/fw/cgi-bin/
cp -v fw                ~/public_html/fw/bin/
cp -v look              ~/public_html/fw/bin/
cp -v libmwfw*.a        ~/public_html/fw/bin/
rm -f                   ~/public_html/fw/bin/vpad
cp -v vpad*             ~/public_html/fw/bin/
cp -v xmlrpc*           ~/public_html/fw/bin/
cp -v prefs*            ~/public_html/fw/bin/

