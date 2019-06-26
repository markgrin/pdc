#ifndef HPP_A5DD1A1091FC4581AA989BB007BE8170

#define HPP_A5DD1A1091FC4581AA989BB007BE8170

#include <deque>
#include <map>

class EmpDist {
    std::deque<double> points;
    std::map<double, std::size_t> sorted;
    std::size_t max;
public:
    EmpDist () = delete;
    EmpDist (std::size_t maxLength) : max (maxLength) {}

    void add (double x);

    double cdf (double x) const;
    double icdf (double p) const;
};

#endif // HPP_A5DD1A1091FC4581AA989BB007BE8170