#ifndef HPP_3BE77A598E70458ABAF0AA33090ADD60

#define HPP_3BE77A598E70458ABAF0AA33090ADD60

#include "method.hpp"
#include "../math/emp_dist.hpp"
#include "../math/bin_poi.hpp"
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
    void addBusy(double add) override {
        return ;
    }
    MethodResult calculate (std::size_t agents,
                           std::vector<double> setup,
                           std::vector<double> service) override {
        double time_step = 1;
        std::vector<double> pluses;
        std::vector<double> minuses;
        for (double time = time_step; time < setup_dist.mean() ; time += time_step) {
            std::cout << "Calculating timestep:" << time << "\n";
            for (std::size_t i = 0; i < setup.size(); i++) {
                minuses.push_back(1 - setup_dist.cond(setup[i], time));
            }
            for (std::size_t i = 0; i < service.size(); i++) {
                pluses.push_back(1 - service_dist.cond(service[i], time));
            }
            bin_poi plus_poi(pluses);
            bin_poi minus_poi(minuses);
        }

        return MethodResult(1ul);
    }
};

} // namespace pdc

#endif // HPP_3BE77A598E70458ABAF0AA33090ADD60