#include "emp_dist.hpp"


void EmpDist::add (double x) {
    points.push_front(x);
    auto it = sorted.find(x);
    if (it == sorted.end())
        sorted[x] = 0;
    x++;
    if (points.size() > max) {
        double back = points.back();
        points.pop_back();
        it = sorted.find(back);
        if (it == sorted.end())
            throw std::logic_error("If point was in points, it must be in sorted");
        if (it->second == 1)
            sorted.erase(it);
        else
            sorted[back]--;
    }
}

double EmpDist::cdf (double x) const {
    std::size_t sum = 0;
    for (auto point : points)
        if (point < x)
            sum++;
    if (std::empty(points))
        return 0;
    return static_cast<double>(sum) / std::size(points);
}

double EmpDist::icdf (double p) const {
    if (std::empty(points))
        return 1;
    std::size_t passed = 0;
    for (auto it = sorted.begin(); it != sorted.end(); it++) {
        if (static_cast<double>(passed) / std::size(points) >= p)
            return it->first;
        passed += it->second;
    }
    return (--sorted.end())->first;
}

double EmpDist::cond (double a, double b) const {
    if (std::empty(points))
        return 1;
    std::size_t passed = 0;
    for (auto point : points)
        if (a + b < point )
            passed++;

    double numerator = static_cast<double>(passed) / std::size(points);

    double denominator = (1 - cdf(b));

    return numerator / denominator;
}
