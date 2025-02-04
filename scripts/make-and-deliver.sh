#!/bin/sh
# daphne.goodall.com:/home/doug/public_html/fw/scripts/make-and-deliver.sh
# copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.
clear
#rm -r -f ~/public_html/fw/build
#mkdir    ~/public_html/fw/build
cd       ~/public_html/fw/build
#cmake ..
make
cp -v *.cgi ~/public_html/fw/cmake-build-debug/
cp -v fw    ~/public_html/fw/cmake-build-debug/
cp -v look  ~/public_html/fw/cmake-build-debug/
cp libmwfw.a ~/public_html/fw/cmake-build-debug/
