//
// Created by kwh44 on 4/20/19.
//

#include <boost/locale.hpp>
#include <boost/locale/boundary.hpp>
#include <algorithm>
#include <set>
#include "boundary_analysis.h"


static int count(const std::string &str, const std::string &sub) {
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
         offset = str.find(sub, offset + sub.length())) {
        ++count;
    }
    return count;
}

void parse(std::vector<std::unique_ptr<std::map<std::string, size_t>>> &list, size_t start, size_t step,
           std::vector<std::string> &data, std::mutex &list_mtx) {
    auto tls_map = std::make_unique<std::map<std::string, size_t> >();
#ifdef DEBUG
    std::cout << "tls map created" << std::endl;
#endif
    for (size_t i = start; i < data.size(); ++i) {
        boost::locale::boundary::ssegment_index map(boost::locale::boundary::word, data[i].begin(), data[i].end());
        map.rule(boost::locale::boundary::word_any);
        std::set<std::string> s(map.begin(), map.end());
        for (auto &v: s) {
            tls_map->insert_or_assign(v, (*tls_map)[v] + count(data[i], v));
        }
    }
    list_mtx.lock();
    list.emplace_back(std::move(tls_map));
    list_mtx.unlock();
}
