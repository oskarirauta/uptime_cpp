#include <stdexcept>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "uptime.hpp"

uptime_t::uptime_t() {

	try {
		this -> update();
	} catch ( const std::runtime_error& e ) {
		throw e;
	}
}

uptime_t::uptime_t(const unsigned long int& seconds) {

	this -> update(seconds);
}

uptime_t::uptime_t(const std::chrono::seconds& seconds) {

	this -> update(seconds);
}

void uptime_t::update() {

	struct sysinfo s_info;
	if ( auto err = ::sysinfo(&s_info); err != 0 )
		throw std::runtime_error("failed to retrieve uptime with sysinfo, error code: " + std::to_string(err));

	this -> update(s_info.uptime);
}

void uptime_t::update(const unsigned long int& seconds) {

	this -> tp = std::chrono::seconds(seconds);
	std::chrono::seconds _secs(seconds);

	auto _days = std::chrono::duration_cast<std::chrono::days>(_secs);
	_secs -= _days;

	auto _hours = std::chrono::duration_cast<std::chrono::hours>(_secs);
	_secs -= _hours;

	auto _minutes = std::chrono::duration_cast<std::chrono::minutes>(_secs);
	_secs -= _minutes;

	this -> _days = _days.count();
	this -> _hours = _hours.count();
	this -> _minutes = _minutes.count();
	this -> _seconds = _secs.count();
}

void uptime_t::update(const std::chrono::seconds& seconds) {

	this -> update(seconds.count());
}

unsigned long uptime_t::timestamp() const {

	return this -> tp.count();
}

int uptime_t::days() const {

	return this -> _days;
}

int uptime_t::hours() const {

	return this -> _hours;
}

int uptime_t::minutes() const {

	return this -> _minutes;
}

int uptime_t::seconds() const {

	return this -> _seconds;
}

std::ostream& operator <<(std::ostream& os, const uptime_t& ut) {

	if ( ut.days() > 0 )
		os << ut.days() << " days ";

	os << ut.hours() << " hours " << ut.minutes() << " minutes " << ut.seconds() << " seconds";
	return os;
}
