#!/bin/bash
##########################################################################
# /home/devo/public_html/fw/scripts/inetd-netstat-redirect.sh 2025-02-19 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.          #
##########################################################################
curl http://127.0.0.1 > ~/public_html/fw/tmp/http.stdout 2> ~/public_html/fw/tmp/http.stderr
