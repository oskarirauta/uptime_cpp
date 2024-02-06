### uptime_cpp
small library for retrieving Linux uptime in a nice struct

[![C++ CI build](https://github.com/oskarirauta/uptime_cpp/actions/workflows/build.yml/badge.svg)](https://github.com/oskarirauta/uptime_cpp/actions/workflows/build.yml)

### Description

Since this uses sysinfo; this works only with Linux

makes a struct available with following methods:

 - update() - updates to current uptime
 - update(seconds) - seconds may be chrono::seconds or unsigned long int, sets timepoint automatically

constructors have same parameters.

functions available are following:
 - days()
 - hours()
 - minutes()
 - seconds()

all returning value corresponding to function's name as int

### Depencies
relatively new compiler; atleast --std=c++20 because chrono::days wasn't available earlier than that

### Importing

 - clone this repository to sub directory uptime
 - in your makefile include uptime/Makefile.inc
 - link your binary with $(UPTIME_OBJS)

objs directory must exist in your main build directory or defaults have to be changed.
Check provided example. If you use some other kind of system, like cmake- you are on your own.

### Example
included

### License
MIT
