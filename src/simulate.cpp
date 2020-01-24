#include "simulate.hpp"
#include <iostream>

#include <list>

namespace pdc {

namespace {

struct CallPoint {
    Call call;
    double timestamp;
};

std::size_t makeNewCalls (Method& method, const std::vector<Call>& calls, std::list<CallPoint>& call_points,
                          std::size_t& newCallIndex, std::size_t agents, double & since_last_call) {
    std::vector<double> service_calls, setup_calls;
    for (const auto& call_point : call_points) {
        if (call_point.timestamp > call_point.call.setup)
            service_calls.push_back(call_point.timestamp - call_point.call.setup);
        else
            setup_calls.push_back(call_point.timestamp);
    }
    auto result = method.calculate(agents, setup_calls, service_calls).calls;
    std::size_t new_calls = result;

    //std::cout << "Make " << new_calls << "\n";

    for (std::size_t i = 0; i < new_calls; i++) {
        if ( newCallIndex >= calls.size())
            break;
        Call newCall = calls[newCallIndex++];
        CallPoint newCallPoint = {newCall, 0};
        //std::cout << newCall.answered << " : " << newCall.setup << " : " << newCall.service << "\n";
        call_points.push_back(newCallPoint);
        since_last_call = 0; 
    }

    //std::cout << "Free " << agents << "\nsetup_calls:";
    //for (auto x : setup_calls)
        //std::cout << x << ", ";
    //std::cout << "\nservice_calls:";
    //for (auto x : service_calls)
        //std::cout << x << ", ";
    //std::cout << "\n\n";
    return agents - service_calls.size();
}

} // namespace

SimResult simulate (double step, std::size_t agents, Method& method, const std::vector<Call>& calls) {
    std::size_t newCallIndex = 0;
    std::list<CallPoint> call_points;
    std::vector<double> service_calls;
    std::vector<double> setup_calls;
    SimResult result = {0, 0, 0, 0, 0, 0};
    double since_last_call = 0;
    while (true) {
        std::size_t free_agents = makeNewCalls(method, calls, call_points, newCallIndex, agents, since_last_call);

        if (newCallIndex >= calls.size())
            break ;

        for (auto it = call_points.begin(); it != call_points.end();) {
            auto& timestamp = it->timestamp;
            auto& setup = it->call.setup;
            auto& service = it->call.service;
            auto& answered = it->call.answered;
            if (timestamp <= setup) {
                timestamp += step;
                if (timestamp > setup) {
                    if (!answered) {
                        method.addCall(it->call);
                        it = call_points.erase(it);
                        result.not_answered++;
                        continue;
                    }
                    if (!free_agents) {
                        method.addCall(it->call);
                        it = call_points.erase(it);
                        //std::cout << "ABANDON!\n";
                        result.abandoned++;
                        continue;
                    }
                    result.answered++;
                    free_agents--;
                    continue;
                }
                continue ;
            }
            timestamp += step;
            if (timestamp > setup + service) {
                method.addCall(it->call);
                it = call_points.erase(it);
                result.finished++;
                free_agents++;
                continue;
            }
            it++;
        }
        since_last_call += step;
        result.duration += step;
        result.wait_time += step * free_agents;

    }
    return result;
}

} // namespace pdc
