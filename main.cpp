#include <iostream>
#include "uptime.hpp"

int main() {

	std::cout << "uptime_cpp test" << std::endl;

	try {
		uptime_t uptime;
		std::cout << "\n" << uptime << std::endl;
	} catch ( const std::runtime_error& e ) {
		std::cerr << "error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
