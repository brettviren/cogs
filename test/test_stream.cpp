#include "cogs/stream.hpp"
#include "cogs/issues.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <URL>" << std::endl;
        return 0;
    }
    auto s = cogs::make_stream(argv[1]);
    while (true) {
        cogs::object obj;
        try {
            obj = s->pop();
        }
        catch (const cogs::stream_exhausted& se) {
            std::cerr <<"done.\n";
            break;
        }
        std::cerr << obj << std::endl;
    }
    return 0;
}
