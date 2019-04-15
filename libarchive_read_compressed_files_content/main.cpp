#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
// only for dev
#include <iostream>

static void errmsg(const char *);

static void fail(const char *, const char *, int);

static void warn(const char *, const char *);


int main(int argc, char **argv) {
    if (argc < 2) exit(1);
    int response;
    ssize_t len;
    const char *filename = argv[1];
    char buff[8192];
    struct archive *a;
    struct archive_entry *entry;
    a = archive_read_new();
    archive_read_support_format_zip(a);
    if ((response = archive_read_open_filename(a, filename, 10240))) {
        fail("archive_read_open_filename()",
             archive_error_string(a), response);
    }
    while ((response = archive_read_next_header(a, &entry)) == ARCHIVE_OK) {
        std::cout << archive_entry_pathname(entry) << std::endl;
        if (archive_entry_size(entry) > 0) {
            len = archive_read_data(a, buff, sizeof(buff));
            std::cout << std::string(buff);
            while (len > 0) {
                len = archive_read_data(a, buff, sizeof(buff));
                std::cout << std::string(buff);
            }
        }
        std::cout << std::endl;
        return 0;
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