//
// Created by kwh44 on 4/20/19.
//

#include <set>
#include <boost/locale.hpp>
#include <boost/locale/boundary.hpp>
#include "boundary_analysis.hpp"

void parse(std::vector<std::string> &data, std::vector<std::string> &tokens_list) {
    std::set<std::string> tokens_set;
    for (const auto &v: data) {
        boost::locale::boundary::ssegment_index map(boost::locale::boundary::word, v.begin(), v.end());
        map.rule(boost::locale::boundary::word_any);
        tokens_set.insert(map.begin(), map.end());
    }
    tokens_list.reserve(tokens_set.size());
    std::copy(tokens_set.begin(), tokens_set.end(), std::back_inserter(tokens_list));
}
