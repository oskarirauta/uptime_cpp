### uptime_cpp
small library for retrieving Linux uptime in a nice struct

[![C++ CI build](https://github.com/oskarirauta/uptime_cpp/actions/workflows/build.yml/badge.svg)](https://github.com/oskarirauta/uptime_cpp/actions/workflows/build.yml)

### Description
First release was linux only due to sysinfo; new version should be more portable
and is tested to work on Linux and OS X. Developer does not have other systems
available for testing currently.

makes a struct uptime_t available with following constructors:

 - uptime_t() - updates to current uptime
 - uptime_t(seconds) - seconds may be chrono::seconds or unsigned long int, sets timepoint automatically

functions available are following:
 - days()
 - hours()
 - minutes()
 - seconds()
 - data()

all returning value corresponding to function's name as int except data which results in a
struct holding all values.

both uptime_t and uptime_t::DATA support ostream redirection.

### Depencies
relatively new compiler; atleast --std=c++20 because chrono::days wasn't available earlier than that

### Importing

 - clone this repository to sub directory uptime
 - in your makefile include uptime/Makefile.inc
 - link your binary with $(UPTIME_OBJS)

objs directory must exist in your main build directory or defaults have to be changed.
Check provided example. If you use some other kind of system, like cmake- you are on your own.

### Example
small example is included

### License
MIT
