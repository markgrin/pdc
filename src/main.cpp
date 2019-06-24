#include <iostream>
#include "core.hpp"
#include "commands/commands.hpp"


int main () {
    std::cout << "Predictive dialing methods analyzer\n";
    pdc::Core core;
    return pdc::command_cycle(core);
}
