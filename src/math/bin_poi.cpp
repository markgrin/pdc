#include "bin_poi.hpp"

#include <boost/multiprecision/cpp_complex.hpp>
#include <complex>

namespace pdc {

namespace {

} // namespace

std::vector<boost::multiprecision::cpp_complex_quad> bin_poi::construct_pmfs() {
    std::vector<boost::multiprecision::cpp_complex_quad> chi(success_probabilities.size() + 1);
    std::size_t half_size = success_probabilities.size() / 2 + (success_probabilities.size() % 2);
    for (std::size_t i = 0; i <= half_size; i++) {
        chi[i] = exp(i * omega * boost::multiprecision::cpp_complex_quad(0, 1));
        std::cout << i << " " << chi[i] << "\n";
    }
    for (std::size_t x = 0; x < half_size; x++) {
        boost::multiprecision::cpp_complex_quad::value_type argz_sum = 0;
        boost::multiprecision::cpp_complex_quad::value_type exparg = 0;
        for (std::size_t y = 0; y < success_probabilities.size(); y++) {
            auto temp = 1 + success_probabilities[y] * chi[x + 1] - success_probabilities[y];
            argz_sum += atan2(temp.imag(), temp.real());
            exparg += log(abs(temp));
        }
        auto d_value = exp(exparg);
        chi[x + 1] = d_value * exp(argz_sum * boost::multiprecision::cpp_complex_quad(0, 1));
    }
    chi[0] = 1;
    return chi;
}

bin_poi::bin_poi(std::vector<double> success_probabilities_in) :
        success_probabilities (std::move(success_probabilities_in)),
        xis (success_probabilities.size() + 1),
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
        chis[chis.size() - 1 - i] = boost::multiprecision::cpp_complex_quad(conj.real(), conj.imag() * (-1));
    }
    for (auto& chi : chis) {
        chi /= success_probabilities.size() + 1;
        std::cout << chi << " ";
    }
    auto sum = chis[0];
    for (std::size_t i = 1; i < chis.size(); i++)
       sum += chis[i];
    auto pi = boost::math::constants::pi<boost::multiprecision::cpp_complex_quad::value_type>();
    auto e = boost::math::constants::e<boost::multiprecision::cpp_complex_quad::value_type>();
    auto i = boost::multiprecision::cpp_complex_quad(0, 1);
    boost::multiprecision::cpp_complex_quad second(0, 0);
    for (std::size_t c = 0; c < chis.size(); c++) {
        xis[c] = 0;
        for (std::size_t n = 0; n < chis.size(); n++) {
            xis[c] += chis[n] * pow(e, ((-2) * i * pi * c * n) / boost::multiprecision::cpp_complex_quad::value_type(chis.size()));
        }
    }
}

} // namespace pdc
