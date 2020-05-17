#ifndef HPP_AC52BECF095F401FB406921EE8340822

#define HPP_AC52BECF095F401FB406921EE8340822

#include <vector>
#include <stdexcept>
#include <boost/multiprecision/cpp_complex.hpp>

namespace pdc {

class bin_poi {

    bin_poi () {
        omega = (2 * 3.14) / (success_probabilities.size() + 1);
    }

    std::vector<double> success_probabilities;
    double omega;

    std::vector<boost::multiprecision::cpp_complex_single> construct_pmfs();
    std::vector<long double> pmfs;
    std::vector<long double> cdfs;

public:
    bin_poi(std::vector<double> success_probabilities_in);

    int more_than(double probability_level);
    int leq_than(double probability_level);
};

} // namespace pdc

#endif // HPP_AC52BECF095F401FB406921EE8340822
