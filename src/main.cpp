#include <iostream>
#include "core.hpp"
#include "commands/commands.hpp"
#include "math/bin_poi.hpp"


int main () {
    std::cout << "Predictive dialing methods analyzer\n";
    pdc::Core core;
    std::vector<double> probs = {0.1, 0.2, 0.3, 0.4, 0.5};
    pdc::bin_poi bp (probs);
    return pdc::command_cycle(core);
}
