#include "timestamp.hpp"
#include <stdio.h>
#include <time.h>


std::string str_timestamp(void) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    char chr[256];

    strftime(chr, sizeof(chr), "%Y%m%d_%H%M%S", t);

    std::string str = chr;
    return str;
}

