#!/bin/sh
####################################################################
# /home/devo/public_html/fw/scripts/make-and-deliver.sh 2025-03-10 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.    #
####################################################################
clear
cd                      ~/public_html/fw/build
make
cp -v *.cgi             ~/public_html/fw/cgi-bin/
#cp -v fw                ~/public_html/fw/bin/
cp -v look              ~/public_html/fw/bin/
cp -v libmwfw*.a        ~/public_html/fw/lib/
rm -f                   ~/public_html/fw/bin/vpad
#cp -v vpad*             ~/public_html/fw/bin/
#cp -v xmlrpc*           ~/public_html/fw/bin/
cp -v vpa*              ~/public_html/fw/bin/
cp -v test*             ~/public_html/fw/bin/

ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem
