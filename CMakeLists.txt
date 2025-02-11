###########################################################################
# daphne.goodall.com:/home/doug/public_html/fw/CmakeLists.txt 2025/02/02  #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved.           #
###########################################################################
# 2025/02/09 03:19 dwg - added xmlrpc_inetd_server target to build        #
# 2025/02/02 02:31 use new library mwfw for most but highest level code.  #
# 2025/01/21 03:21 use statically linked libraries instead of shared ones #
# 2025/01/17 08:31 added link_directories for index.cgi for uuid_generate #
###########################################################################

cmake_minimum_required(VERSION 3.25.1)
project(fw)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)
include_directories(
        "."
		"/usr/local/include"
)

add_library(mwfw STATIC		cgicc.h
		mwfw.cpp			mwfw.h
		cgibind.cpp			cgibind.h
		cgihtml.cpp			cgihtml.h
		CLog.cpp			CLog.hpp
		CSysLog.cpp			CSysLog.hpp
		dashboard.cpp		dashboard.h
		environment.cpp		environment.h
		osIface.cpp			osIface.h
		password.cpp		password.h
		readCsv.cpp			readCsv.h
		schema.cpp			schema.h
		schemaCompiler.cpp	schemaCompiler.h
		shared.cpp			shared.h
		test.cpp			test.h
)

#add_executable(xmlrpc_client
#		xmlrpc_client.cpp
#)
#target_link_libraries(xmlrpc_client
#		libxmlrpc_client++.a
#		libxmlrpc_client.a
#		libxmlrpc++.a
#		libxmlrpc_util++.a
#		libxmlrpc.a
#		libxmlrpc_xmlparse.a
#		libxmlrpc_xmltok.a
#		libxmlrpc_util.a
#		pthread
#		curl
#		libxmlrpc_packetsocket.a
#)

add_executable(xmlrpc_inetd_server
		xmlrpc_inetd_server.cpp
)
target_link_libraries(xmlrpc_inetd_server
		libxmlrpc_server_abyss++.a
		libxmlrpc_server++.a
		libxmlrpc_abyss++.a
		libxmlrpc_server_abyss.a
		libxmlrpc_server.a
		libxmlrpc_abyss.a
		libxmlrpc++.a
		libxmlrpc_util++.a
		libxmlrpc.a
		libxmlrpc_xmlparse.a
		libxmlrpc_xmltok.a
		libxmlrpc_util.a
		ssl
		crypto
		pthread
)

########################################################
# fw is the command line version of the test framework #
########################################################
add_executable(fw
        main.cpp            main.h
        					shared.h
							shmemng.h
                            test.h
                            CLog.hpp
                            osIface.h
		                    environment.h
                            readCsv.h
                            schemaCompiler.h
		           			CSysLog.hpp
)
target_link_libraries(fw
		mwfw
		libcgicc.a        # libcgicc.so         use static library instead
)


#############################################
# fw-test4.cgi is the c++ compiled test CGI #
#############################################
add_executable(fw-test4.cgi
        fw-test4.cpp        fw-test4.h
)
target_link_libraries(fw-test4.cgi
		mwfw
		libcgicc.a        # libcgicc.so         use static library instead
)


##########################################################
# index.cgi is the starting CGI script for the framework #
##########################################################
add_executable(index.cgi    cgicc.h		mwfw.h
        index.cpp           index.h
                            CLog.hpp
                            osIface.h
                            shared.h
                            readCsv.h
                            cgihtml.h
                            schema.h
                            environment.h
                            schemaCompiler.h
							cgibind.h
               				dashboard.h
	            			test.h
							CSysLog.hpp
)
target_link_libraries(index.cgi
		mwfw
		libcgicc.a          # libcgicc.so       use static library instead

)


############################################################################
# login.cgi is invoked by the index.csv as the processing cgi for the form #
############################################################################
add_executable(login.cgi    cgicc.h
        login.cpp           login.h
                            CLog.hpp
		                    osIface.h
                            shared.h
                            readCsv.h
                            cgihtml.h
                            schema.h
               				environment.h
                            cgibind.h
        					password.h
							dashboard.h
	            			CSysLog.hpp
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(login.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


###########################################################
# menu.cgi is intended to be a top level navigation point #
###########################################################
add_executable(menu.cgi     cgicc.h
        menu.cpp            menu.h
                            CLog.hpp
                            osIface.h
                            shared.h
                            readCsv.h
                            cgihtml.h
                            schema.h
                            environment.h
                            cgibind.h
                            dashboard.h
		           			CSysLog.hpp
)
target_link_libraries(menu.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)


#####################################################################
#  logout.cgi is called as the result of pressing the Logout button #
#####################################################################
add_executable(logout.cgi   cgicc.h
        logout.cpp          logout.h
                            CLog.hpp
                            osIface.h
                            shared.h
                            readCsv.h
                            cgihtml.h
                            schema.h
                            environment.h
                            cgibind.h
	            			CSysLog.hpp
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(logout.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


##############################################################################
# diagnose.cgi is intended to be a diagnostic invoked by the Diagnose button #
##############################################################################
add_executable(diagnose.cgi
        diagnose.cpp        diagnose.h
        		            CLog.hpp
                            osIface.h
                             shared.h
		                    readCsv.h
		                   	cgihtml.h
                            schema.h
              				environment.h
                   			cgibind.h
							CSysLog.hpp
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(diagnose.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


######################################################################
# look is a command line program that displays shared segment values #
######################################################################
add_executable(look         cgicc.h
        look.cpp            look.h
							shmemng.h
                            shared.h
                            CLog.hpp
                            osIface.h
             			    environment.h
	            			CSysLog.hpp
)
target_link_libraries(look
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)

######################################################################
# vpad is a command line program #
######################################################################
add_executable(vpad         cgicc.h
        vpad.cpp            vpad.h
							shmemng.h
                            shared.h
                            CLog.hpp
                            osIface.h
                            environment.h
	            			CSysLog.hpp
                            schema.h
		                    cgihtml.h
	            	        readCsv.h
		                    cgibind.h
)
target_link_libraries(vpad
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)



####################################################################
# journal.cgi is called as a result of pressing the Journal button #
####################################################################
add_executable(journal.cgi  cgicc.h
        journal.cpp         journal.h
							shmemng.h
                            shared.h
                            CLog.hpp
                            osIface.h
                            environment.h
                            cgibind.h
                            schema.h
                            cgihtml.h
                            readCsv.h
                            dashboard.h
		           			CSysLog.hpp
)
target_link_libraries(journal.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)


#####################################################################
# notesave.cgi is called as a result of pressing the Submit button  #
# in the journal entry page                                         #
#####################################################################
add_executable(notesave.cgi cgicc.h
        notesave.cpp        notesave.h
                            shared.h
                            CLog.hpp
                            osIface.h
              			    environment.h
                            cgibind.h
                    		dashboard.h
		                    cgihtml.h
							readCsv.h
		                    schema.h
		           			CSysLog.hpp
                            schema.h
)
target_link_libraries(notesave.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)

#####################################################################
# noteload.cgi is called as a result of pressing the Submit button  #
# in the journal entry page                                         #
#####################################################################
add_executable(noteload.cgi cgicc.h
		noteload.cpp        noteload.h
		                    shared.h
		                    CLog.hpp
		                    osIface.h
		                    environment.h
		                    cgibind.h
		                    cgihtml.h
		                    readCsv.h
		                    schema.h
		           			CSysLog.hpp
)
target_link_libraries(noteload.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)

#####################################################################
# render.cgi is a generic CGI script used to load specified schemas #
#####################################################################
add_executable(render.cgi   cgicc.h
        render.cpp          shmemng.h
                            shared.h
                            CLog.hpp
                            osIface.h
                            environment.h
                            cgibind.h
                            schema.h
                            cgihtml.h
                            readCsv.h
                            dashboard.h
		           			CSysLog.hpp
)
target_link_libraries(render.cgi
		mwfw
		libcgicc.a        # libcgicc.so     use static library instead
)



###############
# end-of-file #
###############
