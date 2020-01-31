#ifndef HPP_AC52BECF095F401FB406921EE8340822

#define HPP_AC52BECF095F401FB406921EE8340822

#include <vector>
#include <stdexcept>

namespace pdc {

class bin_poi {

    bin_poi () {
        omega = (2 * 3.14) / (success_probabilities.size() + 1);
    };

    std::vector<double> success_probabilities;
    double omega;

    void construct_pmfs();

public:
    bin_poi(std::vector<double> success_probabilities_in) :
            success_probabilities (std::move(success_probabilities_in)),
            omega (0) {
        for (auto p : success_probabilities) {
            if (p > 1 || p < 0) {
                throw std::runtime_error("probability shoul be bounded in [0, 1]");
            }
        }
        // 2 * PI / (n + 1)
        omega = 2 * (3.1415926535897932384626433832795) / (success_probabilities.size() + 1);
        construct_pmfs();
    }
};

} // namespace pdc

#endif // HPP_AC52BECF095F401FB406921EE8340822
