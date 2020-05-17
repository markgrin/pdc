#ifndef HPP_254C332464D34F1F83966AB83E1F6462

#define HPP_254C332464D34F1F83966AB83E1F6462

#include "methods/method.hpp"
#include "call.hpp"

namespace pdc {

struct SimResult {
    double duration;
    double wait_time;
    double limited_time;
    std::size_t finished;
    std::size_t answered;
    std::size_t abandoned;
    std::size_t not_answered;
};


SimResult simulate (double step, std::size_t agents, Method& method, const std::vector<Call>& calls);

} // namespace pdc

#endif /* HPP_254C332464D34F1F83966AB83E1F6462 */
