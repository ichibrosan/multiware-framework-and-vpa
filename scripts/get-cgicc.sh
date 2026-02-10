#!/bin/bash

sudo apt -y install flex

sudo apt -y install bison

sudo rm -r -f autoconf*
wget https://ftp.gnu.org/pub/gnu/autoconf/autoconf-2.72.tar.gz
gunzip autoconf-2.72.tar.gz
tar xovf autoconf-2.72.tar
cd autoconf-2.72
./configure
make
sudo make install
cd ..

sudo rm -r -f cgicc*
wget https://ftp.gnu.org/pub/gnu/cgicc/cgicc-3.2.20.tar.gz
gunzip cgicc-3.2.20.tar.gz
tar xovf cgicc-3.2.20.tar
cd cgicc-3.2.20
./configure
make
sudo make install
cd ..

