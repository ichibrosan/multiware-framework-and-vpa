#################################################################
# /home/doug/public_html/fw/CmakeLists.txt 2025/02/19           #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. #
###########################################################################
# 2025-02-17 04:24 dwg - added xinetdctl to mwfw2 library                 #
# 2025/02/14 08:17 dwg - optimize, suspended possibly unnecessary headers #
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
        "/opt/xmlrpc-c/include"
)

#add_library( mwfw STATIC
#        mwfw.cpp			mwfw.h
#        cgibind.cpp		cgibind.h
#        cgihtml.cpp		cgihtml.h
#        CLog.cpp			CLog.hpp
#        CSysLog.cpp		CSysLog.hpp
#        dashboard.cpp		dashboard.h
#        environment.cpp	environment.h
#        osIface.cpp		osIface.h
#        password.cpp		password.h
#        readCsv.cpp		readCsv.h
#        schema.cpp			schema.h
#        schemaCompiler.cpp	schemaCompiler.h
#        shared.cpp			shared.h
#        test.cpp			test.h
#        config.cpp         config.h
#        cgicc.h
#)

# The purpose of mwfw2 is to replace mwfw. The difference being that in mwfw,
# responsibility for including all the object headers was on the application
# code, as was the definition of the global pointers. In mwfw2, the mwfw2.h
# will both include the object headers and define the gpXXX global object
# pointers, thereby cleaning up the cluttered application include situation.

add_library( mwfw2 STATIC
        mwfw2.cpp			mwfw2.h
        shared.cpp          shared.h
        cgibind.cpp		    cgibind.h
        cgihtml.cpp		    cgihtml.h
        CLog.cpp			CLog.hpp
        CSysLog.cpp		    CSysLog.hpp
        dashboard.cpp		dashboard.h
        environment.cpp	    environment.h
        osIface.cpp		    osIface.h
        password.cpp		password.h
        readCsv.cpp		    readCsv.h
        schema.cpp			schema.h
        schemaCompiler.cpp	schemaCompiler.h
        test.cpp			test.h
        config.cpp          config.h
		xinetdctl.cpp		xinetdctl.h			# 2025-02-17 04:22 dwg -
        cgicc.h

)

##############################################################################
# diagnose.cgi is intended to be a diagnostic invoked by the Diagnose button #
##############################################################################
add_executable( diagnose.cgi
        diagnose.cpp
        #        		CLog.hpp
        #                osIface.h
        #                shared.h
        #		        readCsv.h
        #		        cgihtml.h
        #                schema.h
        #              	environment.h
        #                cgibind.h
        #				CSysLog.hpp
        #                config.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(diagnose.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


########################################################
# fw is the command line version of the test framework #
########################################################
add_executable( fw
                main.cpp
		#        		shared.h
#				shmemng.h
#                test.h
#                CLog.hpp
#                osIface.h
#		        environment.h
#                schemaCompiler.h
#		        CSysLog.hpp
#                config.h
)
target_link_libraries(fw
		mwfw2
		libcgicc.a        # libcgicc.so         use static library instead
        uuid.a            # uuid.so         use static library instead
)


#############################################
# fw-test4.cgi is the c++ compiled test CGI #
#############################################
add_executable( fw-test4.cgi
                fw-test4.cpp
		#                config.h
)
target_link_libraries(fw-test4.cgi
		mwfw2
		libcgicc.a        # libcgicc.so         use static library instead
        uuid.a            # uuid.so         use static library instead
)


##########################################################
# index.cgi is the starting CGI script for the framework #
##########################################################
add_executable( index.cgi
                index.cpp
#                index.h
#                cgicc.h
#                mwfw.h
#                CLog.hpp
#                osIface.h
#                shared.h
#                readCsv.h
#                cgihtml.h
#                schema.h
#                environment.h
#                schemaCompiler.h
#				cgibind.h
#               	dashboard.h
#	            test.h
#				CSysLog.hpp
#                config.h
)
target_link_libraries(index.cgi
		mwfw2
		libcgicc.a          # libcgicc.so       use static library instead
        uuid.a            # uuid.so         use static library instead
)


####################################################################
# journal.cgi is called as a result of pressing the Journal button #
####################################################################
add_executable( journal.cgi
        journal.cpp
		#                cgicc.h
        #		        shmemng.h
        #                shared.h
        #                CLog.hpp
        #                osIface.h
        #                environment.h
        #                cgibind.h
        #                schema.h
        #                cgihtml.h
        #                readCsv.h
        #                dashboard.h
        #		        CSysLog.hpp
        #                config.h
)
target_link_libraries(journal.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


############################################################################
# login.cgi is invoked by the index.csv as the processing cgi for the form #
############################################################################
add_executable( login.cgi
                login.cpp
#                login.h
#                cgicc.h
#                CLog.hpp
#		        osIface.h
#                shared.h
#                readCsv.h
#                cgihtml.h
#                schema.h
#               	environment.h
#                cgibind.h
#        		password.h
#				dashboard.h
#	            CSysLog.hpp
#                config.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(login.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


#####################################################################
#  logout.cgi is called as the result of pressing the Logout button #
#####################################################################
add_executable( logout.cgi
        logout.cpp
		#                cgicc.h
        #                CLog.hpp
        #                osIface.h
        #                shared.h
        #                readCsv.h
        #                cgihtml.h
        #                schema.h
        #                environment.h
        #                cgibind.h
        #	            CSysLog.hpp
        #                config.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(logout.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


######################################################################
# look is a command line program that displays shared segment values #
######################################################################
add_executable( look
        look.cpp
        #               cgicc.h
        #   			shmemng.h
        #               shared.h
        #               CLog.hpp
        #               osIface.h
        #       	    environment.h
        #	        	CSysLog.hpp
        #               config.h
)
target_link_libraries(look
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


###########################################################
# menu.cgi is intended to be a top level navigation point #
###########################################################
add_executable( menu.cgi
                menu.cpp
#                menu.h
#                cgicc.h
#                CLog.hpp
#                osIface.h
#                shared.h
#                readCsv.h
#                cgihtml.h
#                schema.h
#                environment.h
#                cgibind.h
#                dashboard.h
#		        CSysLog.hpp
#                config.h
)
target_link_libraries(menu.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


#####################################################################
# notesave.cgi is called as a result of pressing the Submit button  #
# in the journal entry page                                         #
#####################################################################
add_executable( notesave.cgi
                notesave.cpp
#                notesave.h
#                cgicc.h
#                shared.h
#                CLog.hpp
#                osIface.h
#              	environment.h
#                cgibind.h
#                dashboard.cpp
#                cgihtml.h
#    			readCsv.h
#	            schema.h
#	    		CSysLog.hpp
#                schema.h
#                config.h
)
target_link_libraries(notesave.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


#####################################################################
# noteload.cgi is called as a result of pressing the Submit button  #
# in the journal entry page                                         #
#####################################################################
add_executable( noteload.cgi
		        noteload.cpp
#                noteload.h
#                cgicc.h
#		        shared.h
#		        CLog.hpp
#		        osIface.h
#		        environment.h
#		        cgibind.h
#		        cgihtml.h
#		        readCsv.h
#		        schema.h
#		        CSysLog.hpp
#                config.h
)
target_link_libraries(noteload.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


#####################################################################
# render.cgi is a generic CGI script used to load specified schemas #
#####################################################################
add_executable( render.cgi
                render.cpp
#                cgicc.h
#                shmemng.h
#                shared.h
#                CLog.hpp
#                osIface.h
#                environment.h
#                cgibind.h
#                schema.h
#                cgihtml.h
#                readCsv.h
#                dashboard.h
#		        CSysLog.hpp
#                config.h
)
target_link_libraries(render.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


######################################################################
# vpad is a command line program #
######################################################################
add_executable( vpad
        vpad.cpp
		#                cgicc.h
        #				 shmemng.h
        #                shared.h
        #                CLog.hpp
        #                osIface.h
        #                environment.h
        #	             CSysLog.hpp
        #                schema.h
        #		         cgihtml.h
        #	             readCsv.h
        #		         cgibind.h
        #                config.h
)
target_link_libraries(vpad
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
)


add_executable(xmlrpc_client
        xmlrpc_client.cpp
        config.cpp	        config.h
        CSysLog.cpp			CSysLog.hpp
        shared.cpp          shared.h
)
link_directories(
        /opt/xmlrpc-c/src/cpp
        /opt/xmlrpc-c/src
        /opt/xmlrpc-c/lib/libutil++
        /opt/xmlrpc-c/lib/expat/xmlparse
        /opt/xmlrpc-c/lib/expat/xmltok
        /opt/xmlrpc-c/lib/libutil
)
target_link_libraries(xmlrpc_client
		mwfw2
        libxmlrpc_client++.a
        libxmlrpc_client.a
        libxmlrpc++.a
        libxmlrpc_util++.a
        libxmlrpc.a
        libxmlrpc_xmlparse.a
        libxmlrpc_xmltok.a
        libxmlrpc_util.a
        pthread
        libcurl.so.4.8.0
        libxmlrpc_packetsocket.a
        uuid.a            # uuid.so         use static library instead
		libcgicc.a
)


add_executable(xmlrpc_inetd_server
        xmlrpc_inetd_server.cpp
        config.cpp	        config.h
        CSysLog.cpp			CSysLog.hpp
        shared.cpp          shared.h
)
target_link_libraries(xmlrpc_inetd_server
		mwfw2
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
        uuid.a            # uuid.so         use static library instead
		libcgicc.a
		libcurl.so.4.8.0
)


###############
# end-of-file #
###############
