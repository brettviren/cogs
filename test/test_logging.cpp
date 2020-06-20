#include "ers/ers.h"

int main()
{
    ERS_DEBUG(1, "A level 1 debug");
    ERS_DEBUG(2, "A level 2 debug");
    ERS_DEBUG(3, "A level 3 debug");
    ERS_INFO("An info");
    ERS_LOG("A log");
}
