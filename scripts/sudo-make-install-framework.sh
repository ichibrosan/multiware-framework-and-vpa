#!/bin/bash
#####################################################################
# /home/devo/public_html/fw/scripts/sudo-make-install.sh 2025-07-12 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.     #
#####################################################################
clear

####################
# Build everything #
####################
rm -r -f                ~/public_html/fw/build
mkdir -p                ~/public_html/fw/build
cd                      ~/public_html/fw/build
cmake ..
make

########################################
# Remove current shared memory segment #
########################################
ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem

###############################
# Install Phase - CGI Scripts #
###############################
cp -v *.cgi             ~/public_html/fw/cgi-bin/

###############################################
# Install Phase - Local Command line programs #
###############################################
cp -v example-*         ~/public_html/fw/bin/
cp -v installer         ~/public_html/fw/bin/
cp -v look              ~/public_html/fw/bin/
cp -v vpa*              ~/public_html/fw/bin/

###############################################
# Install Phase - Global Command line programs #
###############################################
cp -v example-*         ~/bin
cp -v installer         ~/bin/multiware-installer
cp -v look              ~/bin
cp -v vpa*              ~/bin

###############################################
# Install Phase - Install Source Tree Library #
###############################################
cp -v libmwfw*.a        ~/public_html/fw/lib/


######################################################################
# Install Phase - Install /usr/local/include/multiware/mwfw2 headers #
######################################################################
cd                        ~/public_html/fw
sudo rm -r -f             /usr/local/include/multiware/mwfw2
sudo mkdir -p             /usr/local/include/multiware/mwfw2
sudo cp -v -r include/*.h /usr/local/include/multiware/mwfw2/

#######################################################################
# Install Phase - Install /usr/local/lib/multiware/mwfw2 library file #
#######################################################################
cd                      ~/public_html/fw/build
sudo rm -r -f           /usr/local/lib
sudo mkdir -p           /usr/local/lib/multiware/mwfw2
sudo cp -v libmwfw*.a   /usr/local/lib/multiware/mwfw2/


########################################
# eof - sudo-make-install-framework.sh #
########################################
