[![License:MIT](https://img.shields.io/badge/License-MIT-blue?style=plastic)](LICENSE)
[![C++ CI build](../../actions/workflows/build.yml/badge.svg)](../../actions/workflows/build.yml)

### uptime_cpp

Small C++ library for reading the system's uptime into a tidy struct.

## <sub>Description</sub>

Reads how long the system has been up. Linux uses `sysinfo()`; the library also
builds on macOS, FreeBSD, NetBSD, OpenBSD and Windows (Linux and macOS are the
tested ones). Requires C++17 or newer.

It exposes a single type, `uptime_t`:

```cpp
#include <iostream>
#include "uptime.hpp"

int main() {

    uptime_t uptime;                  // sample the current uptime

    std::cout << uptime << "\n";      // "2 days 3 hours 4 minutes 5 seconds"
    std::cout << uptime.days() << "d " << uptime.hours() << "h "
              << uptime.minutes() << "m " << uptime.seconds() << "s\n";

    uptime_t::DATA d = uptime.data(); // all parts in one snapshot
    return 0;
}
```

The default constructor throws `std::runtime_error` if the uptime cannot be read.

## <sub>Constructors</sub>

 - `uptime_t()` - the current system uptime
 - `uptime_t(unsigned long int seconds)` - a known uptime, in elapsed seconds
 - `uptime_t(std::chrono::seconds seconds)` - the same, as a chrono duration

## <sub>Members</sub>

 - `days()`, `hours()`, `minutes()`, `seconds()` - the uptime split into parts,
   each an `int`. `hours()`/`minutes()`/`seconds()` are the remainder within the
   next-bigger unit (so `hours()` is 0-23, `minutes()`/`seconds()` 0-59). Each
   call re-samples the clock.
 - `data()` - all four parts at once, as
   `struct DATA { int days, hours, minutes, seconds; }`; use this when you need a
   consistent breakdown.
 - `timestamp()` - the boot time as a unix timestamp (`unsigned long int`,
   seconds since the epoch).
 - `operator std::string()` - a human-readable string such as
   `"2 days 3 hours 4 minutes 5 seconds"` (singular/plural handled, and leading
   zero units are omitted).

`uptime_t` can be streamed to an `std::ostream`, both by value and by pointer;
it prints that same human-readable string.

### Notes
On C++20 and newer the split uses `std::chrono`'s `days`/`hours`/`minutes`
durations; on C++17 it falls back to equivalent integer math.

## <sub>Importing</sub>

 - clone this repository to sub directory `uptime`
 - in your makefile include `uptime/Makefile.inc`
 - link your binary with `$(UPTIME_OBJS)`
 - add an `objs` directory to the root of your project

Paths are modifiable, check the Makefiles. If you use some other build system,
like cmake, you are on your own.

## <sub>Example</sub>

Runnable example code is in [`main.cpp`](main.cpp); build with `make` and run `./example`.
