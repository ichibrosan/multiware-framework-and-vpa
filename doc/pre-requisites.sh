#!/bin/sh
# pre-requisites.sh 2024/06/27 19:20 dwg - 
# Copyright (c) 2024 Douglas Goodall. All Rights Reserved.
#
#Make sure we are generally up to date
sudo apt update  -y
sudo apt upgrade -y

# Install vim to avoid annoying cursor keystrokes
sudo apt install -y vim

# install pre-requisites that curl needs
sudo apt install -y flex bison

# Install git so we can fetch curl from GitHub
sudo apt install -y git

# Install the GitHub command line client
sudo apt install -y gh

# Install cmake because it is generally used
sudo apt install cmake

# curl also needs ssl stuff
sudo apt install -y libssl-dev

# one time auth step to allow github client to function
gh auth login

# fetch the curl source code
gh repo clone curl/curl

# tar it up for later
tar cvfz curl.tgz ./curl

# prepare to built it
cd curl

# create a build directory like usual for cmake
mkdir -p build

# go there
cd build

# make sure it is empty
rm -r -f *

# invoke like usual to create Makefile
cmake ..

# execute the Makefile
make

# install the results
sudo make install

# back out of the build folder
cd ..

# back out of the curl folder
cd ..

# LETS INSTALL XMLRPC-C
# Install subversion so we can fetch source from SourceForge
sudo apt install -y subversion
# Set the repository variable
REPOS=http://svn.code.sf.net/p/xmlrpc-c/code/advanced
# Invoke subversion to fetch source tree of xmlrpc-c
svn checkout $REPOS xmlrpc-c
# tar it up for later
tar cvfz xmlrpc-c.tgz ./xmlrpc-c
# Enter the xmlrpc-c source tree
cd xmlrpc-c
# do the steps
./configure
make
sudo make install
# Back out of the xmlrpc-c source tree
cd ..

# LETS INSTALL THE LIBPCAP
# Remove any old code
rm -r -f libpcap*
# Fetch the source code using wget
wget https://www.tcpdump.org/release/libpcap-1.10.4.tar.xz
# tar it up for later
tar -xf libpcap-1.10.4.tar.xz
# Enter the source tree
cd libpcap-1.10.4
# do the steps
./configure
make 
sudo make install
# Back out of the source tree
cd ..

# LETS INSTALL TCPDUMP
# Remove any old code
rm -r -f tcpdump*
# Fetch the source code using wget
wget https://www.tcpdump.org/release/tcpdump-4.99.4.tar.xz
# tar it up for later
tar -xf tcpdump-4.99.4.tar.xz
# Enter the source tree
cd tcpdump-4.99.4
# do the steps
./configure
make
sudo make install
# back out of the source tree
cd ..

# Display the resulting files
ls -C


