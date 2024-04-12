#pragma once

#include <ostream>
#include <chrono>

struct uptime_t {

	private:
		std::chrono::seconds tp;

		std::chrono::seconds _seconds() const;
		#if __cplusplus > 201803L
		std::chrono::days _days(std::chrono::seconds& seconds) const;
		std::chrono::hours _hours(std::chrono::seconds& seconds) const;
		std::chrono::minutes _minutes(std::chrono::seconds& seconds) const;
		#else
		int _days(std::chrono::seconds& seconds) const;
		int _hours(std::chrono::seconds& seconds) const;
		int _minutes(std::chrono::seconds& seconds) const;
		#endif

	public:

		struct DATA {
			int days, hours, minutes, seconds;
		};

		unsigned long int timestamp() const;

		int days() const;
		int hours() const;
		int minutes() const;
		int seconds() const;

		DATA data() const;

		operator std::string() const;

		uptime_t();
		uptime_t(const unsigned long int& seconds);
		uptime_t(const std::chrono::seconds& seconds);
};

std::ostream& operator <<(std::ostream& os, const uptime_t& ut);
std::ostream& operator <<(std::ostream& os, const uptime_t* ut);
