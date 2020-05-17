#include "bin_poi.hpp"

#include <boost/multiprecision/cpp_complex.hpp>
#include <complex>
#include "../common/timer.hpp"


namespace pdc {

namespace {

} // namespace

std::vector<boost::multiprecision::cpp_complex_single> bin_poi::construct_pmfs() {
    std::vector<boost::multiprecision::cpp_complex_single> chi(success_probabilities.size() + 1);
    std::size_t half_size = success_probabilities.size() / 2 + (success_probabilities.size() % 2);
    std::cout << "INIT:" << t.duration() << "\n";
    for (std::size_t i = 0; i <= half_size; i++) {
        chi[i] = exp(i * omega * boost::multiprecision::cpp_complex_single(0, 1));
    }
    for (std::size_t x = 0; x < half_size; x++) {
        boost::multiprecision::cpp_complex_single::value_type argz_sum = 0;
        boost::multiprecision::cpp_complex_single::value_type exparg = 0;
        for (std::size_t y = 0; y < success_probabilities.size(); y++) {
            auto temp = 1 + success_probabilities[y] * chi[x + 1] - success_probabilities[y];
            argz_sum += atan2(temp.imag(), temp.real());
            exparg += log(abs(temp));
        }
        auto d_value = exp(exparg);
        chi[x + 1] = d_value * exp(argz_sum * boost::multiprecision::cpp_complex_single(0, 1));
    }
    chi[0] = 1;
    return chi;
}

bin_poi::bin_poi(std::vector<double> success_probabilities_in) :
        success_probabilities (std::move(success_probabilities_in)),
        omega (0) {
    for (auto p : success_probabilities) {
        if (p > 1 || p < 0) {
            throw std::runtime_error("probability should be bounded in [0, 1]");
        }
    }
    // 2 * PI / (n + 1)
    omega = 2 * (3.1415926535897932384626433832795) / (success_probabilities.size() + 1);
    auto chis = construct_pmfs();
    for (std::size_t i = 0; i < success_probabilities.size() / 2; i++) {
        const auto& conj = chis[1 + i];
        chis[chis.size() - 1 - i] = boost::multiprecision::cpp_complex_single(conj.real(), conj.imag() * (-1));
    }
    for (auto& chi : chis) {
        chi /= success_probabilities.size() + 1;
    }
    auto sum = chis[0];
    for (std::size_t i = 1; i < chis.size(); i++)
       sum += chis[i];
    std::vector<boost::multiprecision::cpp_complex_single> xis(success_probabilities.size() + 1);
    auto pi = boost::math::constants::pi<boost::multiprecision::cpp_complex_single::value_type>();
    auto e = boost::math::constants::e<boost::multiprecision::cpp_complex_single::value_type>();
    auto i = boost::multiprecision::cpp_complex_single(0, 1);
    boost::multiprecision::cpp_complex_single second(0, 0);
    for (std::size_t c = 0; c < chis.size(); c++) {
        xis[c] = 0;
        for (std::size_t n = 0; n < chis.size(); n++) {
            xis[c] += chis[n] * pow(e, ((-2) * i * pi * c * n) / boost::multiprecision::cpp_complex_single::value_type(chis.size()));
        }
    }
    for (auto xi : xis) {
        pmfs.push_back(xi.real().convert_to<long double>());
    }
    cdfs.push_back(pmfs.front());
    for (std::size_t i = 1; i < pmfs.size(); i++) {
        cdfs.push_back(cdfs[i - 1] + pmfs[i]);
    }
}

int bin_poi::more_than(double probability_level) {
    for (std::size_t i = cdfs.size() - 1; i != 0; --i) {
        if (1 - cdfs[i] > probability_level) {
            return i;
        }
    }
    return 0;
}

int bin_poi::leq_than(double probability_level) {
    for (std::size_t i = 0; i < cdfs.size(); i++) {
        if (cdfs[i] > probability_level) {
            return i;
        }
    }
    return cdfs.size();
}

} // namespace pdc
