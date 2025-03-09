#!/bin/bash
# deploy-executables-to-dante.sh

SOURCE=/home/devo/public_html/fw/cgi-bin
TARGET=doug@dante.goodall.com:/home/doug/public_html/fw/cgi-bin/
echo Copying CGI scripts from $SOURCE
echo Writing CGI scripts to   $TARGET
scp $SOURCE/*.cgi $TARGET

SOURCE=/home/devo/public_html/fw/bin
TARGET=doug@dante.goodall.com:/home/doug/public_html/fw/bin/
echo Copying CGI scripts from $SOURCE
echo Writing CGI scripts to   $TARGET
scp $SOURCE/* $TARGET

SOURCE=/home/devo/public_html/fw/lib
TARGET=doug@dante.goodall.com:/home/doug/public_html/fw/lib/
echo Copying CGI scripts from $SOURCE
echo Writing CGI scripts to   $TARGET
scp $SOURCE/*.a $TARGET


