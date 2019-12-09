#ifndef HPP_AC52BECF095F401FB406921EE8340822

#define HPP_AC52BECF095F401FB406921EE8340822

#include <vector>
#include <exception>

namespace pdc {

class bin_poi {
    bin_poi () {
        omega = (2 * 3.14) / (success_probabilities.size() + 1);
    };
    std::vector<double> success_probabilities;
    double omega;
public:
    template<typename ...Ts>
    bin_poi(double p, Ts ... ps) :
            bin_poi(ps...) {
        if (p > 1 || p < 0)
            throw std::logic_error("probability shoul be bounded in [0, 1]");
        success_probabilities.push_back(p);
    }
};

} // namespace pdc

#endif // HPP_AC52BECF095F401FB406921EE8340822
