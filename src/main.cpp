#include <iostream>
#include "core.hpp"
#include "commands/commands.hpp"
#include "math/bin_poi.hpp"
#include "methods/grin.hpp"


int main () {
    std::cout << "Predictive dialing methods analyzer\n";
    pdc::Core core;
    std::vector<double> probs = {0.9, 0.9, 0.9, 0.9, 0.5};
    pdc::bin_poi bp (probs);
    std::cout << "MORE_THAN 0.9:" << bp.more_than(0.9) << "\n";
    std::cout << "LESS_THAN 0.9:" << bp.leq_than(0.9) << "\n";
    pdc::Grin method;
    for (std::size_t i = 0; i < 200; i++) {
        pdc::Call call;
        call.answered = true;
        call.service = i + 1;
        call.setup = i + 1;
        method.addCall(call);
    }
    method.calculate(10, std::vector<double>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100},
    std::vector<double>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10});

    return pdc::command_cycle(core);
}
