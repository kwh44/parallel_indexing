#include <iostream>
#include "read_config.hpp"
#include "measure_time.hpp"
#include "read_from_file.hpp"

int main(int argc, char **argv) {
    // help info
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "Description\n" <<
                  "$ main path_to_config_file\n";
        return 0;
    }
    std::string filename("config.dat");
    // user's config file
    if (argc == 2) {
        filename = std::string(argv[1]);
    }
    std::ifstream config_stream(filename);
    if (!config_stream.is_open()) {
        std::cerr << "Failed to open configuration file " << filename << std::endl;
        return 1;
    }
    config_data_t conf_data;
    try {
        read_config_data(config_stream, conf_data);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }

#ifdef DEBUG
    std::cout << "Input filename " << conf_data.input_file_name << "." << std::endl;
    std::cout << "Output alphabet order filename " << conf_data.output_alphabet_order << "." << std::endl;
    std::cout << "Output count order filename " << conf_data.output_count_order << "." << std::endl;
    std::cout << "Thread num to utilize " << conf_data.thread_num << "." << std::endl;
#endif
    std::vector<std::string> file_data;
    get_file_content(file_data, conf_data.input_file_name);
    for (const auto& v: file_data) {
        std::cout << v << std::endl;
    }
    return 0;
}
