#ifndef PARALLEL_INDEXING_COUNT_TOKEN_USAGE_H
#define PARALLEL_INDEXING_COUNT_TOKEN_USAGE_H

#include <vector>
#include <string>
#include <set>
#include <memory>
#include <map>
#include <mutex>

void token_usage(std::vector<std::string> &, std::vector<std::string> &,
                 std::vector<std::unique_ptr<std::map<std::string, size_t>>> &list, size_t start, size_t step,
                 std::mutex &);

#endif //PARALLEL_INDEXING_COUNT_TOKEN_USAGE_H
