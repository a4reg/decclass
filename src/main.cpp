//
// Created by nikitas on 12.03.16.
//

#include <iostream>
#include "StructExpander.h"

static void usage() {
    std::cout << R"(decclass <path-to-cxx-file> <aim-struct>)" << std::endl;
}


int main(int argc, char **argv)
{
    StructExpander expander;
    if (argc == 3)
        expander.expand(argv[1], argv[2]);
    else {
        usage();
        return 0;
    }
    expander.debug_print(std::clog);
    expander.print(std::cout);
    return 0;
}