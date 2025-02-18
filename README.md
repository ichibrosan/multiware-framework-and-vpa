daphne.goodall.com:/home/doug/public_html/fw/README.md 2025/02/09

Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.

2025-02-18 14:29 - mf
fixed the hardcoded paths in environment

couldn't test it as I didn't have the vpa xinetd service file setup correctly.

2025002-18 01:52 dwg - I had an epiphany about the way things are working.
Each executable is calling the environment class to setup the shared
with all its valuable constructs. Actually the environment constructor
only needs to be called when the shared instantiates for the first time
(use of the create flag). After that the shared is already populated and
all you need to do is use it. One way to optimize this, is to make each
init call in the environment constructor conditional on the value of the
associated shared data. For instance, if the szIface variable is empty,
go ahead and call set_iface(). If szIP is empty, call set(ip()...
This will hugely speed up the cgi scripts and utilities and save a lot of 
machine cycles.

2025-02-17 19:16 dwg/mf - patched up things in environment
regarding temp paths and gen of scripts, needs work to make automatic.

2025-02-17 04:25 dwg - added xinetdctl::trigger(port) function
See new vpa file in doc folder and inetd-netstat-redirect.sh in scripts
Add new entries at end of /etc/services file
# Add services for Goodall Multiware Framework
vpad-start	65353/tcp
vpa-netstat	65354/tcp
vpa-ip		65355/tcp
vpa-curl    65356/tcp

2025-02-17 04:25 dwg - added xinetdctl::trigger(port) function
to trigger xinetd controlled scripts:
#define VPA_PORT          5164    // services: vpa/tcp vpa-disc/udp
#define VPAD_START_PORT  65353    // services: vpad-start
#define VPA_NETSTAT_PORT 65354    // services: vpa-netstat
#define VPA_IP_PORT      65355    // services: vpa-ip


2025-02-16 19:30 mf - Added in a meta line generator into the html class.
Began adding facilities to modify css filenames according to their modified 
date time, but halted the progress in order to add in the meta line generator 
to send out information to cease caching altogether, as html files get
generated automatically. Renamed default_styles.css to default.css, and updated
the relevant references accordingly.

2025-02-15 17:30 mf - fixups on contenttype emitters, 
and putting the journal styles into the default stylesheet. Some attempts on
test4.

2025-02-13 20:45 dwg - added szUser and szRpcUuid to +shmvars 
display, enhanced xmlrpc_client and xmlrpc_inetd_server to use 
shared::szRpcUuid as auth token in xmlrpc calls.

2025-02-13 17:12 dwg - About the Broken curl code in github
Last night in the middle of the night, my copy of xmlrpc_client and xmlrpc_inet_server
stopped working and started spouting weird error messages. After hours of horror, I 
discovered that the maintainers of the curl distribution just pushed changes into the
curl/curl repository at github the break xmlrpc-c compatibility. After much heartache,
identified a version that still works which I have names good-curl.tgz. To reproduce
our working infrastructure, you have to configure build and install the good-curl,
then build and install the xmlrpc module, then rebuild our project. Whew!!

2025-02-12 07:18 dwg - extracted diagnoseMethod.h from xmlrpc_inetd_server.cpp
The xmlrpc-c hooks and xinetd integration is working beautifully. :-)

2025-02-10 23:15 mf - added function gen_vpa_script to environment .cpp and .h,
and placed it at the bottom of the environment class constructor. 

2025-02-09 04:19 dwg - added xmlrpc_client module to project

2025-02-09 03:30 dwg - added xmlrpc_inetd_server module to project

2025-02-08 18:30 dwg - added new schema element types to support schema
configured drop down boxes, "select", "selectopt" & "selectend".

2025-02-08 18:08 mf -
modified the naming conventions of the existing html select element functions
and schema implementations to make room for new ones by dwg.

2025-02-08 12:40 dwg - 
add image to dashboard is avatar exists

2025-02-07 20:34 dwg - fix bug in std::string environment::get_ip(bool bDebug)
that caused infinite loop if target interface in "ip a" was number 10 or more.
Fixed with some modern find magic, thanks Marcus.

2025-02-07 11:13 dwg - updated ROW_META_DATA and ROW_DATA_HDR in all schemas.

2025-02-07 08:30 dwg - fixed bug in noteload (spurious tail data) and
updated code and doc.

2025-02-06 20:39 mf - fixed journal by fixing the preprocessor, to use
ROW_META_DATA instead of ROW_META_HDR.

2025-02-06 20:26 mf - changed some variable names to make it more standard,
modified a couple for loops to only have < instead of <=, and did some
work on noteload. many of these changes were within the schema preprocessor.

2025-02-06 19:23 mf - fixed up noteload and modified the journal schema to
generate the iframe again.

2025-20-06 14:03 mf - made the schema meta data uniform across all used
schemas.

2025-02-06 03:32 dwg - enhancement to vpad to increment the uptime counter 
in the shared data every second. Removed superfluous debug logging in the
environment module.

2025-02-05 19:30 dwg - enhancement to dashboard so that xinetd can
start the vpad using the scripts/start-vpad.sh script. Remember to 
install xinetd (apt install xinetd) and enable it (systemctl enable xinetd)
and start it (systemctl start xinetd). See config in doc.

2025-02-04 13:23 dwg - 
Rehosted project as ichibrosan/Virtual-Protocol-Adapter

2025-02-04 12:00 mf -
Reverted CMakeList header changes, and added in some header files where
appropriate.

2025-02-02 16:13 mf -
Fixed the CMakeLists.txt so there's no redundant sources.
It appears the issue was the order the libraries were linked,
once I placed the mwfw library above the other linked libraries,
it worked like a charm.

2025/02/02 16:06 mf - 
edited the row meta data, style column for the journal schema, to
fix the journal page.

2025/02/02 02:47 dwg - 
CMakeLists.txt enhanced for library build. Several small aberrations
still exist I am having trouble resolving. Several of the target have 
one or more redundant sources remaining and I can't explain why. But
it is much faster nonetheless.

2025/01/31 18:55 mf -
fixed the issue with ip being sourced after img_root, journal_root, 
styles_root, and cgi_root.

2025/01/31 sometime after about 01:00 mf -
Major revisions:

added a preprocessor to the schema processor to allow for passing down
values via a std::vector<std::vector<std::string>> array ala JSON data
structures, except with only a Key:Value pair.
This value is by default = {} within gen_from_schema, so only the handle
is required to call that function. Passing in values is completely
optional, and probably should only be done if required.
the key:value pair works from the schema. the syntax is "passed:VALUE".
passed: is what the preprocessor looks for in the schema cell to know
to pull from the vector vector string array.
additionally this preprocessor can insert values from html form submits,
by using the syntax "from:VALUE". from: is what the preprocessor looks for
in the schema cell to know to pull from the form data that was submitted
to the page.

added xahref, an ahref alternative that allows for passing in a class
to the element for css integration.

added various functions to print out html elements: open/close form/div,
button, iframe, and probably some others. Definitely made changes to the
text element as well.

edited the schema metadata line to allow for more precise targeting of 
the default form, whether or not to put a submit button
by default at the end of generating a schema via a boolean value, as well as 
changing the css stylesheet that the page loads with.

2025/01/26 09:39 dwg - 
login display toggles working perfectly now. Some code will need to be 
migrated to other CGI scripts.

2025/01/25 02:19 dwg - 
Fixed logout shared creds clearing bug.
Added dashboard navigation button enablement with or'ed options

2025/01/24 04:26 dwg -
Added usercreds vector support in shared with code mods in login, logout, 
dashboard, shmemng, and CMakeLists.txt. One open bug, logout isn't clearing 
the associated creds vector properly. TBD

2025/01/22 15:24 mf - 
Added test.h, test.cpp to the required build for index in the CMakeLists.txt
file.
Modified the test class to pass the bCGI variable from top-level code to member 
functions.
Replaced many ~getenv("LOGNAME")~ calls with ~gpSh-\>m\_ShMemng-\>szUser~ in
test.cpp, and osiface.cpp.
Changed test3 so if bCGI is true it returns true without running the
procedure.
Modified index.cpp so a new test class is made when index.cgi is run.
- Marcus Franklin 15:24 2025-01-22

2025/01/22 03:35 dwg - About the anti-hacking measure... lines 39-42
* code added to login.cpp assures that you can only call login from index
or login itself. Any other caller is illegal and causes the login script
to abort with a Synchronization Error. FYI, Synchronization Error is what
you used to get in 1984 if you had a copy of CP/M that had been pirated and
had a bogus serial number. When a customer called up and asked what a 
Synchronization error was, they were busted. In the MultiWare framework, we
use this check to detect if someone is poking at out CGIs trying to log in.
If you want to test the feature, login and go to the Render(exp), then click
on the Bogus Login button

2025/01/22 03:06 dwg - 
* display of shared variable, environment variables, and schema in login.cgi
is now conditional on the auth level of the user. admin gets it, user does not.

2025/01/22 01:46 dwg - 
* suspended display of shared variables, and environment variable, and
schema in the index.cgi script, because unauthenticated users shouldn't
see the internal data structures of the framework.

-------------------------------------------------------------------------
2025/01/21 21:14 dwg - 
* added script/remove-shared-memory.sh to remove all existing shared
memory regions used for Goodall Multiware Framework. Use this when you 
make changes to the schema of the shared region and the size changes.

2025/01/21 20:00 dwg - 
* added images/btn_render.png - This  button just says "Render" on it. 
* In the schemas/menu.csv (line 6) - I left the imglink pointing to the 
btn_render_exp.png  so you would know that when you pressed it, you would 
go to the experimental.csv.
* There is some new code I am trying to get working in the look program
to display the start and completed times for the self test. In case you are
not familiar with time in Unix/Linux, the way you handle time is to create
a time_t variable which is really just a glorified long. Then, when you use
the time() function and pass it the ptr to your time_t variable, it stores
a value in the variable which is the number of seconds since some date around
1984 (birth of Unix). Then you use the strftime function to convert the time_t
variable to a formatted string. I was having trouble compiling my strftime
code, so I will keep working on that, so look can tell you the start and
completion times for the self-test code.

-------------------------------------------------------------------------



The framework is coming along very nicely. 

The design is working overall though I am uncertain how I feel about the use 
of the global class pointers. In general globals are frowned upon, but these 
pointers are used to access general services that are mostly stateless.

A major exception to the statelessness is the readCsv object whose member data
stores the most recent Csv file read. The same with the schema object because 
it uses the readCsv object.

A possible solution to this would be to not access the readCsv and schema 
objects though global pointers and make local instances of them as required, 
to be deleted in their time, with their associated data.

One excellent development has been the use of the __FILE__ macro to locate
the development environment during runtime. Placing the developmnent 
environment in the USERDIR ( $HOME/public_html/fw ) works very well because
folders in the development environment are within the usable web server data,
both for HTML and CGI access.

/var/www/html has protection issues due to file ownership, especially the
default cgi-bin directory that usually is in /usr/lib/cgi-bin/. 

<p>Our setup for the framework executes CGI scripts from two places...
<ul>/home/$USER/public_html/fw/cmake-build-debug</ul>
<ul>/home/$USER/public_html/fw/cgi-bin/</ul></p>

<p> Our setup for the framework serves HTML pages from one place...
<ul>/home/$USER/public_html/fw/html/</ul></p>
