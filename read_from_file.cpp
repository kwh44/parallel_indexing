#include "read_from_file.hpp"
#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <boost/locale/generator.hpp>
#include <boost/locale.hpp>


static void errmsg(const char *);

static void fail(const char *, const char *, int);

static void warn(const char *, const char *);


void get_file_content(std::vector<std::string> &storage_container, std::string &filename) {
    boost::locale::generator gen;
    std::locale::global(gen("en_us.UTF-8"));
    std::string format = boost::locale::fold_case(boost::locale::normalize(std::string(filename.end() - 3, filename.end())));
    if (format == "zip") {
        int response = 0;
        ssize_t len = 1;
        char buff[10240];
        struct archive *a;
        struct archive_entry *entry;
        a = archive_read_new();
        archive_read_support_format_zip(a);
        if ((response = archive_read_open_filename(a, filename.c_str(), 10240))) {
            fail("archive_read_open_filename()", archive_error_string(a), response);
        }
        while ((response = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
            // relative path to the file in the archive
            // std::cout << archive_entry_pathname(entry) << std::endl;
            if (archive_entry_size(entry) > 0) {
                len = archive_read_data(a, buff, sizeof(buff));
                while (len > 0) {
                    storage_container.emplace_back(boost::locale::fold_case(boost::locale::normalize(std::string(buff))));
                    len = archive_read_data(a, buff, sizeof(buff));
                }
            }
        }
        archive_read_close(a);
        archive_read_free(a);
    } else if (format == "txt") {
        std::cout << "see ya later" << std::endl;
    } else {
        std::cout << "Support for this format hasn't been added." << std::endl;
    }
}


static void
errmsg(const char *m) {
    write(2, m, strlen(m));
}

static void
warn(const char *f, const char *m) {
    errmsg(f);
    errmsg(" failed: ");
    errmsg(m);
    errmsg("\n");
}

static void
fail(const char *f, const char *m, int r) {
    warn(f, m);
    exit(r);
}