#include "commands.hpp"

#include "generate.hpp"
#include "../methods/progressive.hpp"
#include "../simulate.hpp"

#include <iostream>
#include <string>
#include <random>

namespace pdc {

namespace {

void help() {
    std::cout << "help - print help message\n";
    std::cout << "generate_data - generates dataset\n";
    std::cout << "list_data - list generated datasets\n";
    std::cout << "exit - exit\n";
}

void list_data(Core& core) {
    if (core.datasets.empty())
        std::cout << "Empty\n";

    for (const auto& dataset : core.datasets) {
        std::cout << dataset.first << " size:" << dataset.second.size() << "\n";
    }
}

void generate_data(Core& core) {
    std::cout << "Name:";
    std::string name;
    std::cin >> name;
    auto dataset = interactive_dataset_generation();
    core.datasets[name] = dataset;

}

void simulate(Core& core) {
    std::string name;
    std::cout << "dataset:";
    std::cin >> name;
    Progressive progressive;
    std::cout << "agents:";
    std::size_t agents = 20;
    std::cin >> agents;
    double step = 0.1;
    std::cout << "step:";
    std::cin >> step;

    auto dataset = core.datasets[name];
    auto result = simulate(step, agents, progressive, dataset);

    std::cout << "duration:" << result.duration << "\n";
    std::cout << "answered:" << result.answered << "\n";
    std::cout << "not answered:" << result.not_answered << "\n";
    std::cout << "finished:" << result.finished << "\n";
    std::cout << "abandoned:" << result.abandoned << "\n";
    std::cout << "wait_time:" << result.wait_time << "\n";
    std::cout << "abandoned rate:" << result.abandoned / static_cast<double>(result.answered + result.abandoned) << "\n";
    std::cout << "average wait:" << static_cast<double>(result.wait_time) / (agents * result.duration) << "\n";
}

} // namespace

int command_cycle (Core& core) {
    while (true) {
        std::string command;
        std::cout << "cmd:";
        if (!(std::cin >> command)) {
            std::cout << "I\\O ERROR\n";
            return 1;
        }
        if (command == "exit") {
            return 0;
        } else if (command == "help") {
            help();
        } else if (command == "list_data") {
            list_data(core);
        }
        else if (command == "generate_data") {
            generate_data(core);
        }
        else if (command == "simulate") {
            simulate(core);
        }
        else {
            std::cout << "Unkown command:" << command << "\n";
        }
        std::cout << "\n";
    }
}

} // namespace pdc
