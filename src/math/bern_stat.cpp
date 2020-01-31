#include "bern_stat.hpp"

namespace pdc {

void BernStat::add (bool success) {
    data.push_back(success);
    while (data.size() > max) {
        data.pop_front();
    }
    cache.reset();
}

double BernStat::get_p () const {
    if (data.empty()) {
        return 0u;
    }
    if (cache) {
        return cache.value();
    }
    std::size_t success = 0u;
    for (auto item : data) {
        if (item) {
            success += 1;
        }
    }
    double result = static_cast<double>(success) / static_cast<double>(data.size());
    cache = result;
    return result;
}

} // namespace pdc