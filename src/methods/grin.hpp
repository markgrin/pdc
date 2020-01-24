#ifndef HPP_3BE77A598E70458ABAF0AA33090ADD60

#define HPP_3BE77A598E70458ABAF0AA33090ADD60

#include "method.hpp"
#include "../math/emp_dist.hpp"
#include <iostream>

namespace pdc {

class Grin : public Method {
    EmpDist setup_dist = EmpDist(200);
    EmpDist service_dist = EmpDist(200);

public:
    void addCall(Call& call) override {
        setup_dist.add(call.setup);
        service_dist.add(call.service);
    }
    MethodResult calculate (std::size_t agents,
                           std::vector<double> setup,
                           std::vector<double> service) override {
        double need = 0.97;
        double seconds_with_no_free = 1; //;
        double agents_free_in_that_seconds = 1;//;
        return MethodResult(1ul);
    }
};

} // namespace pdc

#endif // HPP_3BE77A598E70458ABAF0AA33090ADD60