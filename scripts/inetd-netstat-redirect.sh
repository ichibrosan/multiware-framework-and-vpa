#!/bin/bash
##########################################################################
# /home/devo/public_html/fw/scripts/inetd-netstat-redirect.sh 2025-02-19 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.          #
##########################################################################
netstat -r > ~/public_html/fw/tmp/netstat.stdout 2> ~/public_html/fw/tmp/netstat.stderr
