//
// Created by kwh44 on 4/20/19.
//

#ifndef PARALLEL_INDEXING_BOUNDARY_ANALYSIS_H
#define PARALLEL_INDEXING_BOUNDARY_ANALYSIS_H

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <mutex>

void parse(std::vector<std::unique_ptr<std::map<std::string, size_t>>> &, size_t, size_t, std::vector<std::string> &,
           std::mutex &);

#endif //PARALLEL_INDEXING_BOUNDARY_ANALYSIS_H
