#include <stdexcept>
#include <cstring>
#include <string>
#include "uptime.hpp"

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <sys/sysinfo.h>
#elif __NetBSD__
#include <cstdio>
#elif __FreeBSD__ || __APPLE__
#include <time.h>
#elif __OpenBSD__
#include <stdio.h>
#include <time.h>
#include <sys/sysctl.h>
#else
#error Not supported platform
#endif

#ifdef __APPLE__
#define GETTIME_OPTION CLOCK_MONOTONIC_RAW
#elif __FreeBSD__
#define GETTIME_OPTION CLOCK_UPTIME_PRECISE
#endif


#ifdef _WIN32
static uint64_t getUptime(void) {
	return ::GetTickCount();
}

#elif __NetBSD__
static uint64_t getUptime(void) {

	FILE* file;
	if ( file = std::fopen("/proc/uptime", "r"); file == nullptr )
		throw std::runtime_error("failed to retrieve uptime with sysinfo, reason: " + std::string(std::strerror(errno)));

	double uptime;
	std::fscanf(file, "%lf", &uptime);
	std::fclose(file);

	return uptime * 1000;
}

#elif __FreeBSD__ || __APPLE__
static uint64_t getUptime(void) {

	struct timespec time_spec;

	if ( clock_gettime(GETTIME_OPTION, &time_spec) != 0 )
		throw std::runtime_error("failed to retrieve uptime with sysinfo, reason: " + std::string(std::strerror(errno)));

	uint64_t uptime = time_spec.tv_sec * 1000 + time_spec.tv_nsec / 1000000;
	return uptime;
}

#elif __OpenBSD__
static uint64_t getUptime(void) {

	struct timeval time_val;
	size_t len = sizeof(time_val);
	int mib[2] = { CTL_KERN, KERN_BOOTTIME };

	if ( sysctl(mib, 2, &time_val, &len, nullptr, 0) != 0 )
		throw std::runtime_error("failed to retrieve uptime with sysinfo, reason: " + std::string(std::strerror(errno)));

	uint64_t boottime = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
	uint64_t now = (uint64_t)time(nullptr) * 1000;

	return now - boottime;
}
#elif __linux__
static uint64_t getUptime(void) {

	struct sysinfo s_info;
	if ( auto err = ::sysinfo(&s_info); err != 0 )
		throw std::runtime_error("failed to retrieve uptime with sysinfo, reason: " + std::string(std::strerror(errno)));

	return s_info.uptime * 1000;
}
#endif

uptime_t::uptime_t() {

	std::chrono::milliseconds uptime;
	try { uptime = std::chrono::milliseconds(getUptime()); }
	catch ( const std::runtime_error& e ) { throw e; }

	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch());

	this -> tp = now - std::chrono::duration_cast<std::chrono::seconds>(uptime);
}

uptime_t::uptime_t(const unsigned long int& ts) {

	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch());

	this -> tp = now - std::chrono::seconds(ts);
}

uptime_t::uptime_t(const std::chrono::seconds& ts) {

	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch());

	this -> tp = now - ts;
}

unsigned long int uptime_t::timestamp() const {

	return this -> tp.count();
}

[[maybe_unused]]
std::chrono::seconds uptime_t::_seconds() const {

	std::chrono::seconds now = std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch());
	return now - this -> tp;
}

[[maybe_unused]]
std::chrono::days uptime_t::_days(std::chrono::seconds& seconds) const {

	std::chrono::days days = std::chrono::duration_cast<std::chrono::days>(seconds);
	seconds -= days;
	return days;
}

[[maybe_unused]]
std::chrono::hours uptime_t::_hours(std::chrono::seconds& seconds) const {

	std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(seconds);
	seconds -= hours;
	return hours;
}

[[maybe_unused]]
std::chrono::minutes uptime_t::_minutes(std::chrono::seconds& seconds) const {

	std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
	seconds -= minutes;
	return minutes;
}

int uptime_t::days() const {

	std::chrono::seconds seconds = this -> _seconds();
	return this -> _days(seconds).count();
}

int uptime_t::hours() const {

	std::chrono::seconds seconds = this -> _seconds();
	this -> _days(seconds);
	return this -> _hours(seconds).count();
}

int uptime_t::minutes() const {

	std::chrono::seconds seconds = this -> _seconds();
	this -> _days(seconds);
	this -> _hours(seconds);
	return this -> _minutes(seconds).count();
}

int uptime_t::seconds() const {

	std::chrono::seconds seconds = this -> _seconds();
	this -> _days(seconds);
	this -> _hours(seconds);
	this -> _minutes(seconds);
	return seconds.count();
}

uptime_t::DATA uptime_t::data() const {

	std::chrono::seconds seconds = this -> _seconds();
	std::chrono::days days = this -> _days(seconds);
	std::chrono::hours hours = this -> _hours(seconds);
	std::chrono::minutes minutes = this -> _minutes(seconds);

	return { (int)days.count(), (int)hours.count(), (int)minutes.count(), (int)seconds.count() };
}

std::ostream& operator <<(std::ostream& os, const uptime_t::DATA& data) {

	if ( data.days > 0 )
		os << data.days << " days ";

	os << data.hours << " hours " << data.minutes << " minutes " << data.seconds << " seconds";
	return os;
}

std::ostream& operator <<(std::ostream& os, const uptime_t& ut) {

	os << ut.data();
	return os;
}

std::ostream& operator <<(std::ostream& os, const uptime_t* ut) {

	os << ut -> data();
	return os;
}

