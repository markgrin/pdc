#include <iostream>
#include "core.hpp"
#include "commands/commands.hpp"
#include "math/bin_poi.hpp"
#include "methods/grin.hpp"


int main () {
    std::cout << "Predictive dialing methods analyzer\n";
    pdc::Core core;
    std::vector<double> probs = {0.1, 0.2, 0.3, 0.4, 0.5};
    pdc::bin_poi bp (probs);
    pdc::Grin method;
    for (std::size_t i = 0; i < 200; i++) {
        pdc::Call call;
        call.answered = true;
        call.service = i + 1;
        call.setup = i + 1;
        method.addCall(call);
    }
    method.calculate(10, std::vector<double>{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 100},
    std::vector<double>{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 100});

    return pdc::command_cycle(core);
}
