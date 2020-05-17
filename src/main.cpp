#include <iostream>
#include "core.hpp"
#include "commands/commands.hpp"
#include "math/bin_poi.hpp"
#include "methods/grin.hpp"


int main () {
    std::cout << "Predictive dialing methods analyzer\n";
    pdc::Core core;

    return pdc::command_cycle(core);
}
