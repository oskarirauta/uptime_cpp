#pragma once

#include <ostream>
#include <chrono>

struct uptime_t {

	private:
		std::chrono::seconds tp;

		int _days;
		int _hours;
		int _minutes;
		int _seconds;

	public:

		unsigned long int timestamp() const;

		int days() const;
		int hours() const;
		int minutes() const;
		int seconds() const;

		void update();
		void update(const unsigned long int& seconds);
		void update(const std::chrono::seconds& seconds);

		uptime_t();
		uptime_t(const unsigned long int& seconds);
		uptime_t(const std::chrono::seconds& seconds);
};

std::ostream& operator <<(std::ostream& os, const uptime_t& ut);
