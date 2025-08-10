#!/bin/bash
#####################################################################
# /home/devo/public_html/fw/scripts/build-and-deliver.sh 2025-03-10 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.     #
#####################################################################
clear
rm -r -f                ~/public_html/fw/build
mkdir                   ~/public_html/fw/build
cd                      ~/public_html/fw/build
cmake ..
make
cp -v *.cgi             ~/public_html/fw/cgi-bin/
cp -v installer         ~/public_html/fw/bin/
cp -v look              ~/public_html/fw/bin/
cp -v libmwfw*.a        ~/public_html/fw/lib/
rm -f                   ~/public_html/fw/bin/vpad
cp -v vparpc*           ~/public_html/fw/bin/
cp -v prefs*            ~/public_html/fw/bin/
cp -v example-*         ~/public_html/fw/bin/

ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem
cp -v example-*         ~/bin/
cp -v installer         ~/bin
cp -v look              ~/bin
cp -v vpa*              ~/bin
