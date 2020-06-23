#include "cogs/stream.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc == 1) {
        std::cerr << "usage: " << argv[0] << " <uri>" << std::endl;
        return -1;
    }
    
    auto cs = cogs::make_stream(argv[2]);

    while (true) {
        std::cerr << cs->pop() << std::endl;
    }

    return 0;
}
