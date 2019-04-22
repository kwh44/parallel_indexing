#include "count_token_usage.hpp"
#include <iostream>
#include <boost/locale.hpp>
#include <boost/locale/boundary.hpp>
#include <algorithm>
#include <set>
#include "boundary_analysis.hpp"

static int count(const std::string &str, const std::string &sub) {
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
         offset = str.find(sub, offset + sub.length())) {
        ++count;
    }
    return count;
}


void token_usage(std::vector<std::string> &data, std::vector<std::string> &token_list,
                 std::vector<std::unique_ptr<std::map<std::string, size_t>>> &list, size_t start, size_t step,
                 std::mutex &list_mtx) {
    auto tls_map = std::make_unique<std::map<std::string, size_t> >();
    for (size_t i = start; i < token_list.size(); i += step) {
        size_t usage_count = 0;
        for (const auto &v: data) usage_count += count(v, token_list[i]);
        tls_map->insert_or_assign(token_list[i], usage_count);
    }
    list_mtx.lock();
    list.emplace_back(std::move(tls_map));
    list_mtx.unlock();
}
