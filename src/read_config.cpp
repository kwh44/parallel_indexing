#include <iostream>
#include "read_config.hpp"

void read_config_data(std::ifstream &file, config_data_t &container) {
	auto container_copy(container); // save container state
	std::ios::fmtflags flags(file.flags()); // Save stream state
	file.exceptions(std::ifstream::failbit); // Enable exception on fail
	try {
		file >> container.input_file_name;
		file >> container.output_alphabet_order;
		file >> container.output_count_order;
		file >> container.thread_num;
	} catch(...) {
		container = container_copy;
		file.flags(flags);
		throw;
	}
}