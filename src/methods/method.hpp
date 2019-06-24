#ifndef HPP_7E2AD4CECAA24FE6941C2951D98BFCDA

#define HPP_7E2AD4CECAA24FE6941C2951D98BFCDA

#include "../call.hpp"
#include <vector>

namespace pdc {

struct Method {
    virtual void addCall(Call &call) = 0;

    virtual std::size_t calculate(std::size_t agents,
                                  std::vector<double> setup,
                                  std::vector<double> service) = 0;
    virtual ~Method(){}
};

} // namespace pdc

#endif // HPP_7E2AD4CECAA24FE6941C2951D98BFCDA
