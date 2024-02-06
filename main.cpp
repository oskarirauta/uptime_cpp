#include <iostream>
#include "uptime.hpp"

int main(int argc, char **argv) {

	std::cout << "uptime_cpp test" << std::endl;

	uptime_t uptime;

	std::cout << "\n" << uptime << std::endl;

	return 0;
}
