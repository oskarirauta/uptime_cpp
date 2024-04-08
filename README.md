[![License:MIT](https://img.shields.io/badge/License-MIT-blue?style=plastic)](LICENSE)
[![C++ CI build](../../actions/workflows/build.yml/badge.svg)](../../actions/workflows/build.yml)
### uptime_cpp

small library for retrieving Linux uptime in a nice struct

## <sub>Description</sub>

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

### Notes
Library utilises std::chrono's durations days, hours and minutes when built with c++20 standard
or newer, but has legacy functions available for older standards, such as c++17.

## <sub>Importing</sub>

 - clone this repository to sub directory uptime
 - in your makefile include uptime/Makefile.inc
 - link your binary with $(UPTIME_OBJS)
 - add objs directory to root of your project

Paths are modifiable, check Makefiles.
If you use some other kind of system, like cmake- you are on your own.

## <sub>Example</sub>

example code is provided
