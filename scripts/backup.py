#!/usr/bin/python3
##############################################################################
# daphne.goodall.com:/home/doug/public_html/backup.py 2025/01/10 17:58 dwg - # 
# Copyright (c) 2020-2025 Douglas Wade Goodall. All Rights Reserved.         #
##############################################################################

import os
import sys

host = "daphne"
os.system("date +%H%M >time.txt")
fd = open("time.txt","r")
data = fd.read()
fd.close()
time = data[0] + data[1] + data[2] + data[3]

# place ther date and time in a file called date.txt
os.system("date > date.txt")

# open the file using fd as file descriptor
fd = open("date.txt","r")

# read the dfate and time into string called data
data = fd.read()

# close the file
fd.close()

# isolate the time/date components into string vars
day = data[0] + data[1] + data[2]
month = data[4] + data[5] + data[6]
day = data[8]+data[9]
if day[0] == ' ':
    day = "0"+data[9]
year = data[27] + data[28] + data[29] + data[30]
#time = data[11] + data[12] + data[14] + data[15]
# convert named months into numbered months
if month == "Jan":
    monthnum = "01"
if month == "Feb":
    monthnum = "02"
if month == "Mar":
    monthnum = "03"
if month == "Apr":
    monthnum = "04"
if month == "May":
    monthnum = "05"
if month == "Jun":
    monthnum = "06"
if month == "Jul":
    monthnum = "07"
if month == "Aug":
    monthnum = "08"
if month == "Sep":
    monthnum = "09"
if month == "Oct":
    monthnum = "10"
if month == "Nov":
    monthnum = "11"
if month == "Dec":
    monthnum = "12"

# build filename of temporary archive file
tempspec = "fw-" + year + "-" + monthnum + "-" + day + "-" + time + ".tgz"

# Create single file archive of current system
command = "tar cfzv " + tempspec + " ./fw" 
os.system(command)
# copy archive file to Robot over network if desired
#command = "cp " + tempspec + " /media/doug/UsbHD1/fw-backups/"
#print(command)
os.system(command)

#############
#### EOF ####
#############
