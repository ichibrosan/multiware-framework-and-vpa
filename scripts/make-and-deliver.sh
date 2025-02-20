#!/bin/sh
####################################################################
# /home/devo/public_html/fw/scripts/make-and-deliver.sh 2025-02-19 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.    #
####################################################################
clear
cp -v /etc/xinetd.d/vpa ~/public_html/fw/doc/
#rm -r -f ~/public_html/fw/build
#mkdir    ~/public_html/fw/build
cd       ~/public_html/fw/build
#cmake ..
make
cp -v *.cgi ~/public_html/fw/cmake-build-debug/
cp -v fw    ~/public_html/fw/cmake-build-debug/
cp -v look  ~/public_html/fw/cmake-build-debug/
cp -v libmwfw*.a ~/public_html/fw/cmake-build-debug/
rm -f       ~/public_html/fw/cmake-build-debug/vpad
cp -v vpad  ~/public_html/fw/cmake-build-debug/
cp -v xmlrpc*   ~/public_html/fw/cmake-build-debug/
