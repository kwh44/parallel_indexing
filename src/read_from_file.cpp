#include <archive.h>
#include <archive_entry.h>
#include <sstream>
#include <boost/locale/generator.hpp>
#include <boost/locale.hpp>
#include "read_txt_to_string.hpp"
#include "read_from_file.hpp"

void get_file_content(std::vector<std::string> &storage_container, std::string &filename) {
    boost::locale::generator gen;
    std::locale::global(gen("en_us.UTF-8"));
    std::string format = boost::locale::fold_case(
            boost::locale::normalize(std::string(filename.end() - 3, filename.end())));

    if (format == "txt") {
        std::string text;
        std::ifstream txt_file(filename);
        if (txt_file.is_open()) {
            read_from_txt(txt_file, text);
            storage_container.emplace_back(text);
        } else {
            std::cerr << "Couldn't open input txt file" << std::endl;
            std::exit(1);
        }
    } else {
        int response;
        ssize_t len;
        constexpr size_t buffer_size = 8192;
        char buff[buffer_size];
        struct archive *a;
        struct archive_entry *entry;
        a = archive_read_new();
        archive_read_support_filter_all(a);
        archive_read_support_format_all(a);
        if ((response = archive_read_open_filename(a, filename.c_str(), buffer_size))) {
            std::cerr << "archive_read_open_filename() failed: " << archive_error_string(a) << std::endl;
            std::exit(response);
        }
        while (archive_read_next_header(a, &entry) == ARCHIVE_OK) {
            if (archive_entry_size(entry) > 0) {
                std::stringstream entry_content_string;
                len = archive_read_data(a, buff, sizeof(buff));
                while (len > 0) {
                    entry_content_string << boost::locale::fold_case(boost::locale::normalize(std::string(buff)));
                    len = archive_read_data(a, buff, sizeof(buff));
                }
                storage_container.emplace_back(std::move(entry_content_string.str()));
            }
        }
        archive_read_close(a);
        archive_read_free(a);
    }
}
