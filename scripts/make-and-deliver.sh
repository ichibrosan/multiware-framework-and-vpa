#!/bin/sh
####################################################################
# /home/devo/public_html/fw/scripts/make-and-deliver.sh 2025-03-10 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.    #
####################################################################

clear
cd                      ~/public_html/fw/build
make

# CPI Scripts
cp -v *.cgi             ~/public_html/fw/cgi-bin/
cp -v bluerays          ~/public_html/fw/cgi-bin/bluerays.cgi

# Command Line Utilities (within the build env)
cp -v bluerays          ~/public_html/fw/bin/
cp -v example-*         ~/public_html/fw/bin/
cp -v installer         ~/public_html/fw/bin/
cp -v look              ~/public_html/fw/bin/
cp -v prefs*            ~/public_html/fw/bin/
cp -v vparpc*           ~/public_html/fw/bin/

# Command Line Utilities (globally from user's bin folder ~/bin)
cp -v bluerays          ~/bin
cp -v example-*         ~/bin/
cp -v installer         ~/bin
cp -v look              ~/bin
cp -v prefs*            ~/bin
cp -v vpa*              ~/bin

# Libraries
cp -v libmwfw*.a        ~/public_html/fw/lib/

# Remove current shared memory region
ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem

