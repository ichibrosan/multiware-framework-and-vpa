#!/bin/sh
###########################################################################################
# daphne.goodall.com:/home/doug/public_html/fw/scripts/remove-shared-memory.sh 2025-02-19 #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.                           #
###########################################################################################
# Remove all shared memory regions used by the Goodall Multiware Framework.
# Used when we make changes to the schema of the shared region (size).
ipcrm --shmem-key 0x00005164 2> /tmp/ipcrm#5164.stderr # MultiWare Main ShMem
ipcrm --shmem-key 0x00005165 2> /tmp/ipcrm#5165.stderr # vpad control/status
ipcrm --shmem-key 0x00005167 2> /tmp/ipcrm#5167.stderr # admin  user descriptor
ipcrm --shmem-key 0x00005168 2> /tmp/ipcrm#5168.stderr # doug   user descriptor
ipcrm --shmem-key 0x00005169 2> /tmp/ipcrm#5169.stderr # marcus user descriptor
