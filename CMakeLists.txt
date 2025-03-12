#################################################################
# /home/devo/public_html/fw/CmakeLists.txt 2025/02/19           #
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
		"include"
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
        mwfw2.cpp			include/mwfw2.h
        shared.cpp          include/shared.h
        cgibind.cpp		    include/cgibind.h
        cgihtml.cpp		    include/cgihtml.h
        CLog.cpp			include/CLog.hpp
        CSysLog.cpp		    include/CSysLog.hpp
        dashboard.cpp		include/dashboard.h
        environment.cpp	    include/environment.h
        osIface.cpp		    include/osIface.h
        password.cpp		include/password.h
        readCsv.cpp		    include/readCsv.h
        schema.cpp			include/schema.h
        schemaCompiler.cpp	include/schemaCompiler.h
        test.cpp			include/test.h
        config.cpp          include/config.h
		xinetdctl.cpp		include/xinetdctl.h
		include/cgicc.h		include/version.h
		rpcbind.cpp			include/rpcbind.h
		stylist.cpp			include/stylist.h
)

##############################################################################
# diagnose.cgi is intended to be a diagnostic invoked by the Diagnose button #
##############################################################################
add_executable( diagnose.cgi
        diagnose.cpp		include/version.h
		rpcbind.cpp			include/rpcbind.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(diagnose.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
		libcurl.so.4.8.0
		libxmlrpc_client++.a
		libxmlrpc_client.a
		libxmlrpc++.a
		libxmlrpc_util++.a
		libxmlrpc.a
		libxmlrpc_xmlparse.a
		libxmlrpc_xmltok.a
		libxmlrpc_util.a
		pthread
		libxmlrpc_packetsocket.a

)


########################################################
# fw is the command line version of the test framework #
########################################################
add_executable( fw
                main.cpp		include/version.h
		rpcbind.cpp				include/rpcbind.h
)
target_link_libraries(fw
		mwfw2
		libcgicc.a        # libcgicc.so         use static library instead
        uuid.a            # uuid.so         use static library instead
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
)


#############################################
# fw-test4.cgi is the c++ compiled test CGI #
#############################################
add_executable( fw-test4.cgi
                fw-test4.cpp
		include/version.h
		rpcbind.cpp		include/rpcbind.h
)
target_link_libraries(fw-test4.cgi
		mwfw2
		libcgicc.a        # libcgicc.so         use static library instead
        uuid.a            # uuid.so         use static library instead
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

)


##########################################################
# index.cgi is the starting CGI script for the framework #
##########################################################
add_executable( index.cgi
                index.cpp		include/version.h
		rpcbind.cpp				include/rpcbind.h
)
target_link_libraries(index.cgi
		mwfw2
		libcgicc.a          # libcgicc.so       use static library instead
        uuid.a            # uuid.so         use static library instead
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
)


####################################################################
# journal.cgi is called as a result of pressing the Journal button #
####################################################################
add_executable( journal.cgi
        journal.cpp		include/version.h
		rpcbind.cpp		include/rpcbind.h
)
target_link_libraries(journal.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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

)


############################################################################
# login.cgi is invoked by the index.csv as the processing cgi for the form #
############################################################################
add_executable( login.cgi
                login.cpp		include/version.h
		rpcbind.cpp				include/rpcbind.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(login.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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

)


#####################################################################
#  logout.cgi is called as the result of pressing the Logout button #
#####################################################################
add_executable( logout.cgi
        logout.cpp		include/version.h
		rpcbind.cpp		include/rpcbind.h
)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(logout.cgi
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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
)


######################################################################
# look is a command line program that displays shared segment values #
######################################################################
add_executable( look
        look.cpp		include/version.h
		rpcbind.cpp		include/rpcbind.h
)
target_link_libraries(look
        mwfw2
        libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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
)


###########################################################
# menu.cgi is intended to be a top level navigation point #
###########################################################
add_executable( menu.cgi
                menu.cpp		include/version.h
		rpcbind.cpp				include/rpcbind.h
)
target_link_libraries(menu.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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
)


#####################################################################
# notesave.cgi is called as a result of pressing the Submit button  #
# in the journal entry page                                         #
#####################################################################
add_executable( notesave.cgi
                notesave.cpp	include/version.h
		rpcbind.cpp				include/rpcbind.h
)
target_link_libraries(notesave.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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
)

#####################################################################
add_executable( noteload.cgi
		        noteload.cpp		include/version.h
		rpcbind.cpp					include/rpcbind.h
)
target_link_libraries(noteload.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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

)

add_executable(prefs-action.cgi
		prefs-action.cpp
		config.cpp	        include/config.h
		CSysLog.cpp			include/CSysLog.hpp
		shared.cpp          include/shared.h
		include/version.h
		rpcbind.cpp			include/rpcbind.h
		include/webcolors.h
		include/diagnoseMethod.h
)
target_link_directories(prefs-action.cgi PRIVATE
		/opt/xmlrpc-c/src/cpp
		/opt/xmlrpc-c/src
		/opt/xmlrpc-c/lib/libutil++
		/opt/xmlrpc-c/lib/expat/xmlparse
		/opt/xmlrpc-c/lib/expat/xmltok
		/opt/xmlrpc-c/lib/libutil
)
target_link_libraries(prefs-action.cgi
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





add_executable(query_remote.cgi
		queryremote.cpp
		config.cpp	        include/config.h
		CSysLog.cpp			include/CSysLog.hpp
		shared.cpp          include/shared.h
		include/version.h
		rpcbind.cpp			include/rpcbind.h
		include/webcolors.h
		include/diagnoseMethod.h
)
target_link_directories(query_remote.cgi PRIVATE
		/opt/xmlrpc-c/src/cpp
		/opt/xmlrpc-c/src
		/opt/xmlrpc-c/lib/libutil++
		/opt/xmlrpc-c/lib/expat/xmlparse
		/opt/xmlrpc-c/lib/expat/xmltok
		/opt/xmlrpc-c/lib/libutil
)
target_link_libraries(query_remote.cgi
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



#####################################################################
# render.cgi is a generic CGI script used to load specified schemas #
#####################################################################
add_executable( render.cgi
                render.cpp		include/version.h
		rpcbind.cpp				include/rpcbind.h
								include/webcolors.h
)
target_link_libraries(render.cgi
		mwfw2
		libcgicc.a        # libcgicc.so     use static library instead
        uuid.a            # uuid.so         use static library instead
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

)



add_executable(xmlrpc_client
        xmlrpc_client.cpp
        config.cpp	        include/config.h
        CSysLog.cpp			include/CSysLog.hpp
        shared.cpp          include/shared.h
							include/version.h
		rpcbind.cpp			include/rpcbind.h
							include/webcolors.h
							include/diagnoseMethod.h
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
        config.cpp	        include/config.h
        CSysLog.cpp			include/CSysLog.hpp
        shared.cpp          include/shared.h
							include/version.h
		rpcbind.cpp			include/rpcbind.h
							include/diagnoseMethod.h
)
target_link_directories(xmlrpc_inetd_server PRIVATE
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/src/cpp
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/src
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/lib/abyss++
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/lib/libutil++
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/lib/expat/xmlparse
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/lib/expat/xmltok
		/opt/multiware/Dougs-Networking-Prerequisites/xmlrpc-c/lib/libutil
)

target_link_libraries(xmlrpc_inetd_server
		mwfw2
		libxmlrpc_client++.a
		libxmlrpc_client.a
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

##################################
# vpad is a command line program #
##################################
add_executable( vpad
		vpad.cpp		include/version.h
						include/webcolors.h
)
link_directories(
		/opt/xmlrpc-c/src/cpp
		/opt/xmlrpc-c/src
		/opt/xmlrpc-c/lib/libutil++
		/opt/xmlrpc-c/lib/expat/xmlparse
		/opt/xmlrpc-c/lib/expat/xmltok
		/opt/xmlrpc-c/lib/libutil
)
target_link_libraries(vpad
		mwfw2
		libxmlrpc_server_abyss++.a
		libxmlrpc_server++.a
		libxmlrpc_abyss++.a
		libxmlrpc_server_abyss.a
		libxmlrpc_server.a
		libxmlrpc_abyss.a
		ssl
		crypto
		libxmlrpc++.a
		libxmlrpc_util++.a
		libxmlrpc.a
		libxmlrpc_xmlparse.a
		libxmlrpc_xmltok.a
		libxmlrpc_util.a
		pthread
		libcgicc.a
		uuid.a            # uuid.so         use static library instead

		libxmlrpc_client++.a
		libxmlrpc_client.a
		libcurl.so.4.8.0
		libxmlrpc_packetsocket.a

)

add_executable( prefs.cgi
		prefs.cpp
)
link_directories(
		/opt/xmlrpc-c/src/cpp
		/opt/xmlrpc-c/src
		/opt/xmlrpc-c/lib/libutil++
		/opt/xmlrpc-c/lib/expat/xmlparse
		/opt/xmlrpc-c/lib/expat/xmltok
		/opt/xmlrpc-c/lib/libutil
)
target_link_libraries(prefs.cgi
		mwfw2
		libcgicc.a
		uuid.a            # uuid.so         use static library instead
)


###############
# end-of-file #
###############
