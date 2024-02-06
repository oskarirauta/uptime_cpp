#include <iostream>
#include "uptime.hpp"

int main(int argc, char **argv) {

	std::cout << "uptime_cpp test" << std::endl;

	uptime_t *uptime;

	try {
		uptime = new uptime_t();

	} catch ( const std::runtime_error& e ) {

		throw e;
	}

	std::cout << "\n" << uptime << std::endl;
	delete uptime;

	return 0;
}
