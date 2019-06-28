#include "dataset_io.hpp"

#include <fstream>
#include <iostream>

namespace pdc {

namespace {

Call getSSVCall (std::fstream& file) {
    if (!file)
        return {0, 0, 0};
    int success;
    Call call;
    file >> success;
    file >> call.setup;
    file >> call.service;
    return call;

}

void writeSSV (const Call& call, std::fstream& file) {
    file << static_cast<int>(call.answered) << " " << call.setup << " " << call.service << "\n";
}

} // namespace

std::vector<Call> load () {
    std::string filename;
    std::cout << "Enter filename:";
    std::cin >> filename;

    std::fstream file (filename, std::ios::in);
    Call call = getSSVCall (file);
    std::vector<Call> result;
    if (call.setup) {
        result.push_back(call);
        call = getSSVCall (file);
    }
    return result;
}

void save (const std::vector<Call>& dataset) {
    std::string filename;
    std::cout << "Enter filename:";
    std::cin >> filename;

    std::fstream file (filename, std::ios::out);
    for (const auto& call : dataset)
        writeSSV(call, file);
}

} // namespace pdc
