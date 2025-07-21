#!/bin/sh
####################################################################
# /home/devo/public_html/fw/scripts/make-and-deliver.sh 2025-03-10 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.    #
####################################################################
clear
cd                      ~/public_html/fw/build
make
cp -v *.cgi             ~/public_html/fw/cgi-bin/
cp -v look              ~/public_html/fw/bin/
cp -v libmwfw*.a        ~/public_html/fw/lib/
rm -f                   ~/public_html/fw/bin/vpad
cp -v vpa*              ~/public_html/fw/bin/
cp -v test*             ~/public_html/fw/bin/
ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem

cp -v cartoonizer       ~/bin
cp -v look              ~/bin
cp -v password-util     ~/bin
cp -v vpa*              ~/bin
