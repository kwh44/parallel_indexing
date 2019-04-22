#include <iostream>
#include <thread>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include "read_config.hpp"
#include "measure_time.hpp"
#include "read_from_file.hpp"
#include "boundary_analysis.hpp"

typedef std::pair<std::string, size_t> pair;

int main(int argc, char **argv) {
    // help info
    if (argc == 2 && std::string(argv[1]) == "--help") {
        std::cout << "Description\n" <<
                  "$ ./parallel_indexing <path_to_config_file>\n";
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

    // check output files
    std::ofstream output_alphabet(conf_data.output_alphabet_order);
    if (!config_stream.is_open()) {
        std::cerr << "Failed to open file for alphabet order result" << std::endl;
        return 1;
    }
    std::ofstream output_count(conf_data.output_count_order);
    if (!config_stream.is_open()) {
        std::cerr << "Failed to open file for count order result " << std::endl;
        return 1;
    }

#ifdef DEBUG
    std::cout << "Input filename " << conf_data.input_file_name << "." << std::endl;
    std::cout << "Output alphabet order filename " << conf_data.output_alphabet_order << "." << std::endl;
    std::cout << "Output count order filename " << conf_data.output_count_order << "." << std::endl;
    std::cout << "Thread num to utilize " << conf_data.thread_num << "." << std::endl;
#endif

    auto start_reading = get_current_time_fenced();
    std::vector<std::string> file_data;
    get_file_content(file_data, conf_data.input_file_name);
    auto finish_reading = get_current_time_fenced();
#ifdef DEBUG
    for (const auto &v: file_data) {
        std::cout << v << std::endl;
    }
#endif
    std::vector<std::thread> thread_list;
    thread_list.reserve(conf_data.thread_num);
    std::vector<std::unique_ptr<std::map<std::string, size_t>>> list;
    std::mutex list_mtx;
    auto start_counting = get_current_time_fenced();
    for (size_t i = 0; i < conf_data.thread_num; ++i) {
        thread_list.emplace_back(parse, std::ref(list), i, conf_data.thread_num, std::ref(file_data),
                                 std::ref(list_mtx));
    }
    for (auto &v: thread_list) v.join();
    auto finish_counting = get_current_time_fenced();
    // merge all maps in first
    std::map<std::string, size_t> &final_map = *list[0];
    std::for_each(list.begin() + 1, list.end(), [&](const std::unique_ptr<std::map<std::string, size_t>> &a) {
        for (const auto &v: *a) list[0]->operator[](v.first) += v.second;
    });
    // remove merged maps
    list.erase(list.begin() + 1, list.end());
#ifdef DEBUG
    for (auto &v: final_map) {
        std::cout << v.first << ": " << v.second << std::endl;
    }
#endif
    // create a empty vector of pairs
    std::vector<std::pair<std::string, size_t>> sort_container(final_map.size());
    // copy key-value pairs from the map to the vector
    std::copy(final_map.begin(), final_map.end(), sort_container.begin());
    // sort the pair by alphabet
    std::sort(sort_container.begin(), sort_container.end(),
              [](const pair &l, const pair &r) {
                  return l.first < r.first;
              });
    // write to output file
    for (auto &v: sort_container) {
        output_alphabet << v.first << ": " << v.second << std::endl;
    }
    // sort by usage count
    std::sort(sort_container.begin(), sort_container.end(),
              [](const pair &l, const pair &r) {
                  return l.second > r.second;
              });
    // write to output file
    for (auto &v: sort_container) {
        output_count << v.first << ": " << v.second << std::endl;
    }
    auto total_finish = get_current_time_fenced();
    std::cout << "Total time: " << to_us(total_finish - start_reading) / 1000000.0 << std::endl;
    std::cout << "Reading time: " << to_us(finish_reading - start_reading) / 1000000.0 << std::endl;
    std::cout << "Counting time: " << to_us(finish_counting - start_counting) / 1000000.0 << std::endl;
    return 0;
}
