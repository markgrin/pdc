#ifndef HPP_B8FC6211CE06414788CB151FBE2FC2E4

#define HPP_B8FC6211CE06414788CB151FBE2FC2E4

#include "method.hpp"
#include "../math/emp_dist.hpp"
#include <iostream>

namespace pdc {

class Berlang : public Method {
    EmpDist setup_dist = EmpDist(200);
    EmpDist service_dist = EmpDist(200);

public:
    void addCall(Call& call) override {
        setup_dist.add(call.setup);
        service_dist.add(call.service);
    }
    std::size_t calculate (std::size_t agents,
                           std::vector<double> setup,
                           std::vector<double> service)
    {
        return 1;
    }
};

} // namespace pdc

#endif // HPP_B8FC6211CE06414788CB151FBE2FC2E4