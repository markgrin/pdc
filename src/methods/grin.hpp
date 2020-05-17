#ifndef HPP_3BE77A598E70458ABAF0AA33090ADD60

#define HPP_3BE77A598E70458ABAF0AA33090ADD60

#include "method.hpp"
#include "../math/emp_dist.hpp"
#include "../math/bin_poi.hpp"
#include "../common/timer.hpp"
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
        bool success = true;
        std::size_t vector_init = 0;
        std::size_t vector_pushes = 0;
        std::size_t bin_poi_init = 0;
        std::size_t sum_time = 0;
        for (double time = time_step; time < setup_dist.mean() ; time += time_step) {
            timer t;
            t.begin();
            std::vector<double> pluses;
            std::vector<double> minuses;
            t.end();
            vector_init += t.duration();
            t = timer();
            t.begin();
            for (std::size_t i = 0; i < setup.size(); i++) {
                minuses.push_back(1 - setup_dist.cond(setup[i], time));
            }
            for (std::size_t i = 0; i < service.size(); i++) {
                pluses.push_back(1 - service_dist.cond(service[i], time));
            }
            t.end();
            vector_pushes += t.duration();
            t = timer();
            t.begin();
            bin_poi plus_poi(std::move(pluses));
            bin_poi minus_poi(std::move(minuses));
            t.end();
            bin_poi_init += t.duration();
            t = timer();
            t.begin();
            int sum_for_time = plus_poi.more_than(0.97) - minus_poi.leq_than(0.97) + static_cast<int>(agents);
            if (sum_for_time < 0) {
                success = false;
                break;
            }
            t.end();
            sum_time += t.duration();
        }
        std::cout << "VECTOR_INIT" << vector_init << "\n";
        std::cout << "VECTOR_PUSHES" << vector_pushes << "\n";
        std::cout << "BIN_POI_INIT" << bin_poi_init << "\n";
        std::cout << "SUM_TIME" << sum_time << "\n";
        if (!success) {
            return MethodResult(0ul);
        }
        return MethodResult(1ul);
    }
};

} // namespace pdc

#endif // HPP_3BE77A598E70458ABAF0AA33090ADD60