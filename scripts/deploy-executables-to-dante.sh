#!/bin/bash
# deploy-executables-to-dante.sh
SOURCE=/home/devo/public_html/fw/cmake-build-debug
TARGET=doug@dante.goodall.com:/home/doug/public_html/fw/cgi-bin/
echo Copying CGI scripts from $SOURCE
echo Writing CGI scripts to   $TARGET
scp $SOURCE/*.cgi $TARGET
