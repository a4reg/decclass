//
// Created by nikitas on 12.03.16.
//

#include <iostream>
#include "StructExpander.h"

int main(int argc, char **argv)
{
    StructExpander expander;
    if (argc == 2)
        expander.expand("/home/nikitas/Repos/decclass/tests/input.cpp", argv[1]);
    //expander.debug_print(std::cout);
    expander.print(std::cout);
    return 0;
}