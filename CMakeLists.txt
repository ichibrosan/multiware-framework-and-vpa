####################################################################
## ~/public_html/fw/CMakeLists.txt 2025-08-07 02:56 dwg -         ##
## This file is part of MultiWare Engineering's VPA and FrameWork ##
####################################################################
## This file is made available under the                          ##
## Creative Commons CC0 1.0 Universal Public Domain Dedication.   ##
####################################################################

## 2025-08-07 02:56 dwg - regarding cmake version to by used
## The CLion 2025.2 update alleges to have installed cmake 4.0.2 and in fact
## it is at /home/doug/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake --build /home/doug/public_html/fw/cmake-build-debug --target all -j 30
## but is is not detected/used by the IDE.
#cmake_minimum_required(VERSION 4.0.2)
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
        cliLogin.cpp include/cliLogin.h
        CLog.cpp include/CLog.h
        config.cpp include/config.h
        crtbind.cpp include/crtbind.h
        CSysLog.cpp include/CSysLog.h
        dashboard.cpp include/dashboard.h
        dotconfig.cpp include/dotconfig.h
        environment.cpp include/environment.h
        ichibrosan.cpp include/ichibrosan.h
        iHex.cpp include/iHex.h
        installer.cpp include/installer.h
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
        vparpc.cpp include/vparpc.h
        window.cpp include/window.h
        xinetdctl.cpp include/xinetdctl.h
        #        cliLogin.cpp include/cliLogin.h
)


###############################################################################
# The installer program is built using a special version of the mwfw2 library #
# customized for use by the installer. It doesn't need all the bells and      #
# whistles and doesn't need to instantiate the kitchen sink as does the mwfw2 #
# library.                                                                    #
###############################################################################
add_library(mwfw2inst STATIC
        mwfw2.cpp include/mwfw2.h
       include/cgicc.h include/version.h
        cfgini.cpp include/cfgini.h
       cgibind.cpp include/cgibind.h
       cgihtml.cpp include/cgihtml.h
       checkAuth.cpp include/checkAuth.h
       cliLogin.cpp include/cliLogin.h
       CLog.cpp include/CLog.h
        config.cpp include/config.h
        crtbind.cpp include/crtbind.h
        CSysLog.cpp include/CSysLog.h
       dashboard.cpp include/dashboard.h
        dotconfig.cpp include/dotconfig.h
        environment.cpp include/environment.h
        ichibrosan.cpp include/ichibrosan.h
       iHex.cpp include/iHex.h
        installer.cpp include/installer.h
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
       vparpc.cpp include/vparpc.h
        window.cpp include/window.h
        xinetdctl.cpp include/xinetdctl.h
       cliLogin.cpp include/cliLogin.h
)

add_executable(about.cgi about.cpp)
target_link_libraries(about.cgi PRIVATE mwfw2 cgicc uuid)

add_executable(       epstein epstein.cpp)
target_link_libraries(epstein PRIVATE mwfw2 cgicc pthread uuid)


add_executable(admin.cgi admin.cpp
        ichibrosan.cpp
        include/ichibrosan.h
        include/installer.h)
target_link_libraries(admin.cgi PRIVATE mwfw2 cgicc uuid)

add_executable(bluerays bluerays.cpp)
target_link_libraries(bluerays PRIVATE mwfw2)


add_executable(discovery_inetd_server discovery_inetd_server.cpp)
target_link_libraries(discovery_inetd_server PRIVATE mwfw2 cgicc pthread uuid)



add_executable(example-cfgini example-cfgini.cpp)
target_link_libraries(example-cfgini PRIVATE mwfw2 cgicc uuid)

add_executable(       example-discovery-client example-discovery-client.cpp)
target_link_libraries(example-discovery-client PRIVATE mwfw2)

add_executable(       example-discovery-server example-discovery-server.cpp)
target_link_libraries(example-discovery-server PRIVATE mwfw2 cgicc uuid)

add_executable(       example-osrelease example-osrelease.cpp)
target_link_libraries(example-osrelease PRIVATE mwfw2 cgicc uuid)

add_executable(       example-semigraphics example-semigraphics.cpp)
target_link_libraries(example-semigraphics PRIVATE mwfw2 cgicc pthread uuid)

add_executable(       example-shared-memory example-shared-memory.cpp)
target_link_libraries(example-shared-memory PRIVATE mwfw2 cgicc pthread uuid)

add_executable(       example-vparpc-client example-vparpc-client.cpp CVpaRpc.cpp)
target_link_libraries(example-vparpc-client PRIVATE mwfw2 pthread uuid cgicc)

add_executable(       index.cgi index.cpp)
target_link_libraries(index.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(init_xinetd_vpa init_xinetd_vpa.cpp
        CServices.cpp        include/CServices.h
        include/xinetdcfg.h  xinetdcfg.cpp
)
target_link_libraries(init_xinetd_vpa PRIVATE mwfw2 cgicc pthread uuid)

add_executable(installer installer.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
        cliLogin.cpp include/cliLogin.h
        include/installer.h
)
target_link_libraries(installer PRIVATE mwfw2inst cgicc pthread uuid)


add_executable(iphone.cgi iPhone.cpp)
target_link_libraries(iphone.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(login.cgi login.cpp)
target_link_libraries(login.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(logout.cgi logout.cpp)
target_link_libraries(logout.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(look look.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
        cliLogin.cpp include/cliLogin.h
)
target_link_libraries(look PRIVATE mwfw2 cgicc pthread uuid)

add_executable(menu.cgi menu.cpp)
target_link_libraries(menu.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(prefs.cgi prefs.cpp)
target_link_libraries(prefs.cgi PRIVATE mwfw2 cgicc uuid)

add_executable(prefs-action.cgi prefs-action.cpp)
target_link_libraries(prefs-action.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(render.cgi render.cpp)
target_link_libraries(render.cgi PRIVATE mwfw2 cgicc pthread uuid)

add_executable(structures structures.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
)
target_link_libraries(structures PRIVATE mwfw2 cgicc pthread uuid)

add_executable(view_shared view_shared.cpp)
target_link_libraries(view_shared PRIVATE mwfw2 pthread uuid cgicc)

add_executable(vparpc_client
        vparpc_client.cpp include/vparpc_client.h
        CVpaRpc.cpp include/CVpaRpc.h)
target_link_libraries(vparpc_client PRIVATE mwfw2 pthread uuid cgicc)

add_executable(vparpc_server vparpc_server.cpp include/vparpc_server.h)
target_link_libraries(vparpc_server PRIVATE mwfw2 pthread cgicc uuid)

add_executable(vparpc_inetd_server vparpc_inetd_server.cpp)
target_link_libraries(vparpc_inetd_server PRIVATE mwfw2 uuid cgicc)

add_executable(vpautil vpautil.cpp
        CServices.cpp include/CServices.h
        include/xinetdcfg.h
        xinetdcfg.cpp
        cliLogin.cpp include/cliLogin.h
)
target_link_libraries(vpautil PRIVATE mwfw2 cgicc pthread uuid)

#add_subdirectory(Google_tests)

###############
# end-of-file #
###############