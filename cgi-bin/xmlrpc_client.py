#!/usr/bin/python3
######################################################################
# /home/devo/public_html/fw/cgi-bin/tester.py 2025-03-31 17:05 dwg - #
# Copyright (c) 2020-2025 Douglas Goodall., All Rights Reserved.     #
######################################################################

import xmlrpc.client
print("Content-Type: text/plain\n\n")

AUTHFUNC=2
VERS=1
PSK="348bcdbe62fead7028c8010490b27332"
SERVER_URL="http://127.0.0.1:5164/RPC2"
with xmlrpc.client.ServerProxy(SERVER_URL) as proxy:
    AUTHTOK = proxy.diagnose(AUTHFUNC,0,0,"",0,"",PSK)
    VERSION = proxy.diagnose(VERS,0,0,"",0,"",AUTHTOK)
    print(VERSION)
    DASHBOARD = proxy.diagnose(1,0,0,"",0,"",AUTHTOK)
