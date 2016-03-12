//
// Created by nikitas on 12.03.16.
//

#include <iostream>
#include "StructExpander.h"

int main(int argc, char **argv)
{
    StructExpander expander;
    expander.expand("/home/nikitas/Repos/decclass/tests/input.cpp", "model");
    //expander.debug_print(std::cout);
    expander.print(std::cout);
    return 0;
}