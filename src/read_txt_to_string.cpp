#include "read_txt_to_string.hpp"
#include <limits>

void read_from_txt(std::ifstream &file, std::string &text) {
    auto const start_pos = file.tellg();
    file.ignore(std::numeric_limits<std::streamsize>::max());
    auto const char_count = file.gcount();
    file.seekg(start_pos);
    text = std::string(char_count, char{});
    file.read(&text[0], text.size());
}