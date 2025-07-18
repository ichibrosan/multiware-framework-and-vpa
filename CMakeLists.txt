#################################################################
# /home/devo/public_html/fw/CmakeLists.txt 2025/07/04 01:57 dwg #
# Copyright (c) 2025 Douglas Wade Goodall. All Rights Reserved. #
###########################################################################
# 2025-07-04 01:57 dwg - xmlrpc has been deprecated in favor of vparpc    #
# 2025-03-14 12:07 dwg - suspend diagnose.cgi compilation                 #
# 2025-02-17 04:24 dwg - added xinetdctl to mwfw2 library                 #
# 2025/02/14 08:17 dwg - optimize, suspended possibly unnecessary headers #
# 2025/02/09 03:19 dwg - added xmlrpc_inetd_server target to build        #
# 2025/02/02 02:31 use new library mwfw for most but highest level code.  #
# 2025/01/21 03:21 use statically linked libraries instead of shared ones #
# 2025/01/17 08:31 added link_directories for index.cgi for uuid_generate #
###########################################################################

cmake_minimum_required(VERSION 3.25.1)
project(fw)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)

include_directories("include")

# The purpose of mwfw2 is to replace mwfw. The difference being that in mwfw,
# responsibility for including all the object headers was on the application
# code, as was the definition of the global pointers. In mwfw2, the mwfw2.h
# will both include the object headers and define the gpXXX global object
# pointers, thereby cleaning up the cluttered application include situation.


add_library(mwfw2 STATIC
        mwfw2.cpp include/mwfw2.h
        include/cgicc.h include/version.h
        cfgini.cpp include/cfgini.h
        cgibind.cpp include/cgibind.h
        cgihtml.cpp include/cgihtml.h
        checkAuth.cpp include/checkAuth.h
        CLog.cpp include/CLog.h
        config.cpp include/config.h
        crtbind.cpp include/crtbind.h
        CSysLog.cpp include/CSysLog.h
        dashboard.cpp include/dashboard.h
        dotconfig.cpp include/dotconfig.h
        environment.cpp include/environment.h
        iHex.cpp include/iHex.h
        mutations.cpp include/mutations.h
        osIface.cpp include/osIface.h
        password.cpp include/password.h
        readCsv.cpp include/readCsv.h
        semigraphics.cpp include/semigraphics.h
        shared.cpp include/shared.h
        shMemMutex.cpp include/shMemMutex.h
        shMemMgr.cpp include/shMemMgr.h
        schema.cpp include/schema.h
        schemaCompiler.cpp include/schemaCompiler.h
        stylist.cpp include/stylist.h
        test.cpp include/test.h
        vparpc.cpp include/vparpc.h
        window.cpp include/window.h
        xinetdctl.cpp include/xinetdctl.h
        #        cliLogin.cpp include/cliLogin.h
)

add_executable(fw-test4.cgi fw-test4.cpp
        include/cfgini.h
        cfgini.cpp
        include/checkAuth.h)
target_link_libraries(fw-test4.cgi mwfw2 cgicc pthread uuid)

add_executable(index.cgi index.cpp)
target_link_libraries(index.cgi mwfw2 cgicc pthread uuid)

add_executable(init_xinetd_vpa init_xinetd_vpa.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
)
target_link_libraries(init_xinetd_vpa mwfw2 cgicc pthread uuid)


add_executable(login.cgi login.cpp)
target_link_libraries(login.cgi mwfw2 cgicc pthread uuid)

add_executable(logout.cgi logout.cpp)
target_link_libraries(logout.cgi mwfw2 cgicc pthread uuid)

add_executable(look look.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
        cliLogin.cpp include/cliLogin.h
)
target_link_libraries(look mwfw2 cgicc pthread uuid)

add_executable(menu.cgi menu.cpp)
target_link_libraries(menu.cgi mwfw2 cgicc pthread uuid)

add_executable(prefs.cgi prefs.cpp)
target_link_libraries(prefs.cgi mwfw2 cgicc uuid)

add_executable(prefs-action.cgi prefs-action.cpp)
target_link_libraries(prefs-action.cgi mwfw2 cgicc pthread uuid)

add_executable(render.cgi render.cpp)
target_link_libraries(render.cgi mwfw2 cgicc pthread uuid)

add_executable(structures structures.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
)
target_link_libraries(structures mwfw2 cgicc pthread uuid)


add_executable(testdiscclient testdiscclient.cpp)
target_link_libraries(testdiscclient mwfw2)

add_executable(testdiscserver testdiscserver.cpp)
target_link_libraries(testdiscserver mwfw2)


add_executable(vpalogin vpalogin.cpp CVpaRpc.cpp include/CVpaRpc.h
        include/checkAuth.h
        checkAuth.cpp)
target_link_libraries(vpalogin mwfw2 cgicc pthread uuid)


add_executable(vparpc_client
        vparpc_client.cpp include/vparpc_client.h
        CVpaRpc.cpp include/CVpaRpc.h)
target_link_libraries(vparpc_client mwfw2 pthread uuid cgicc)

add_executable(vparpc_server vparpc_server.cpp include/vparpc_server.h)
target_link_libraries(vparpc_server mwfw2 pthread cgicc uuid)

add_executable(vparpc_inetd_server vparpc_inetd_server.cpp)
target_link_libraries(vparpc_inetd_server mwfw2 uuid cgicc)

add_executable(vpautil vpautil.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
        cliLogin.cpp include/cliLogin.h
)
target_link_libraries(vpautil mwfw2 cgicc pthread uuid)


###############
# end-of-file #
###############
