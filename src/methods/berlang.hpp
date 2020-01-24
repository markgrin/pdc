#ifndef HPP_B8FC6211CE06414788CB151FBE2FC2E4

#define HPP_B8FC6211CE06414788CB151FBE2FC2E4

#include "method.hpp"
#include "../math/emp_dist.hpp"
#include "../math/berlang.hpp"
#include "progressive.hpp"


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
    MethodResult calculate (std::size_t agents,
                           std::vector<double> setup,
                           std::vector<double> service) override {
        if (!setup_dist.is_full()) {
            std::cout << "FULL\n";
            return Progressive().calculate(agents, setup, service);
        }
        double possible_intensity = iberlang(0.97, agents);
        std::cout << "possible intensity:" << possible_intensity << "\n";
        possible_intensity; // /= pickup prob.
        double mean = service_dist.mean();
        std::cout << "mean" << mean << "\n";
        double per_second = (mean ? mean / possible_intensity : 0);
        std::cout << "per second:" << per_second << "\n---\n";
        return MethodResult(per_second);
    }
};

} // namespace pdc

#endif // HPP_B8FC6211CE06414788CB151FBE2FC2E4