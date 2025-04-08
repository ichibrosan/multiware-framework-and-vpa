daphne.goodall.com:/home/devo/public_html/fw/README.md 2025/02/09

Copyright (c) 2021-2025 Douglas Wade Goodall. All Rights Reserved.

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
the development environment during runtime. Placing the development 
environment in the USERDIR ( $HOME/public_html/fw ) works very well because
folders in the development environment are within the usable web server data,
both for HTML and CGI access.

/var/www/html has protection issues due to file ownership, especially the
default cgi-bin directory that usually is in /usr/lib/cgi-bin/. 

<p>Our setup for the framework executes CGI scripts from two places...
<ul>/home/$USER/public_html/fw/cmake-build-debug</ul>
<ul>/home/$USER/public_html/fw/cgi-bin/</ul>

<p> Our setup for the framework serves HTML pages from one place...
<ul>/home/$USER/public_html/fw/html/</ul>
