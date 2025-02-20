#!/bin/sh
#################################################################
# /home/devo/public_html/fw/scripts/run-doxygen.sh 2025-02-19   #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. #
#################################################################
cd ~/public_html/fw/
doxygen ~/public_html/fw/doc/Doxyfile
firefox html/index.html
