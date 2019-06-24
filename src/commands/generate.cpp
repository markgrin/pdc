#include "generate.hpp"

#include <iostream>
#include <random>
#include <functional>

namespace pdc {

namespace {

std::function<double(std::mt19937&)> chooseGeneratorReal () {
    std::cout << "(Fixed, Uniform, Exponentioal){F/U/E}:";
    std::string answer;
    std::cin >> answer;

    if (answer == "F") {
        std::cout << "Fixed value:";
        double value;
        std::cin >> value;
        return [value](std::mt19937&) {return value;};

    } else if (answer == "U") {
        std::cout << "Unifrm left bound:";
        double left, right;
        std::cin >> left;
        std::cout << "Unifrm right bound:";
        std::cin >> right;
        return [left, right](std::mt19937& generator) {return std::uniform_real_distribution(left, right)(generator);};
    }
    // Exponential
    std::cout << "Exponential rate:";
    double rate;
    std::cin >> rate;
    return [rate](std::mt19937& generator) {return std::exponential_distribution(rate)(generator);};
}

std::function<bool(std::mt19937&)> chooseGeneratorBool () {
    std::cout << "(Fixed, Bernoulli){F/B}:";
    std::string answer;
    std::cin >> answer;

    if (answer == "F") {
        std::cout << "Fixed value:";
        bool value;
        std::cin >> value;
        return [value](std::mt19937 &) { return value; };
    }
    // Bernoullu
    std::cout << "Bernoulli success:";
    double success = 0;
    std::cin >> success;
    return [success](std::mt19937& generator) {return std::bernoulli_distribution(success)(generator);};
}

} // namespace

std::vector<Call> interactive_dataset_generation() {
    std::mt19937 generator {std::random_device{}()};
    std::vector<Call> calls;
    std::cout << "Size:";
    std::size_t size;
    std::cin >> size;
    calls.resize(size);
    std::cout << "Choose generator for Answered field\n";
    auto answered = chooseGeneratorBool();
    std::cout << "Choose generator for Setup field\n";
    auto setup = chooseGeneratorReal();
    std::cout << "Choose generator for Service field\n";
    auto service = chooseGeneratorReal();

    for (auto& call : calls) {
        call.answered = answered(generator);
        call.setup = setup(generator);
        call.service = service(generator);
    }
    return calls;
}


} // namespace pdc
