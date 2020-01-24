#ifndef HPP_1EBD42EF3B3C42199B6BE5867904D716

#define HPP_1EBD42EF3B3C42199B6BE5867904D716

#include "method.hpp"

namespace pdc {

class Progressive : public Method {
    void addCall(Call& call) override {
    }
    MethodResult calculate (std::size_t agents,
                           std::vector<double> setup,
                           std::vector<double> service) override
    {
        return MethodResult(agents > setup.size() + service.size() + 1 ? agents - setup.size() - service.size() - 1 : 0);
    }
};


} // namespace pdc

#endif /* HPP_1EBD42EF3B3C42199B6BE5867904D716 */
