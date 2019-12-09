#include "bin_poi.hpp"

namespace pdc {

namespace {

void f () {
    bin_poi poi (0.2, 0.3, 0.5);
}
} // namespace

    /*
def __init__(self, probabilities):

check_input_prob()
self.
omega = 2 * np.pi / (self.number_trials + 1)
self.
pmf_list = self.get_pmf_xi()
self.
cdf_list = self.get_cdf(self.pmf_list)

# ------------------------------------------------------------------------------
# Methods for the Poisson Binomial Distribution
# ------------------------------------------------------------------------------

i = 0
try:
isinstance(number_successes, collections
.Iterable)
pvalues = np.array(number_successes, dtype = 'float')
# if input is iterable (list, numpy.array):
for k in number_successes:
                pvalues[i] = 1. - self.cdf(k) + self.pmf(k)
                i += 1
            return pvalues
        except TypeError:
            # if input is an integer:
            if number_successes == 0:
                return 1
            else:
                return 1 - self.cdf(number_successes - 1)

# ------------------------------------------------------------------------------
# Methods to obtain pmf and cdf
# ------------------------------------------------------------------------------

    def get_cdf(self, event_probabilities):
        """Return the values of the cumulative density function.
        Return a list which contains all the values of the cumulative
        density function for :math:`i = 0, 1, ..., n`.
        :param event_probabilities: array of single event probabilities
        :type event_probabilities: numpy.array
        """
        cdf = np.empty(self.number_trials + 1)
        cdf[0] = event_probabilities[0]
        for i in range(1, self.number_trials + 1):
            cdf[i] = cdf[i - 1] + event_probabilities[i]
        return cdf

    def get_pmf_xi(self):
        """Return the values of the variable ``xi``.
        The components ``xi`` make up the probability mass function, i.e.
        :math:`\\xi(k) = pmf(k) = Pr(X = k)`.
        """
        chi = np.empty(self.number_trials + 1, dtype=complex)
        chi[0] = 1
        half_number_trials = int(
            self.number_trials / 2 + self.number_trials % 2)
        # set first half of chis:
        chi[1:half_number_trials + 1] = self.get_chi(
            np.arange(1, half_number_trials + 1))
        # set second half of chis:
        chi[half_number_trials + 1:self.number_trials + 1] = np.conjugate(
            chi[1:self.number_trials - half_number_trials + 1] [::-1])
        chi /= self.number_trials + 1
        xi = np.fft.fft(chi)
        if self.check_xi_are_real(xi):
            xi = xi.real
        else:
            raise TypeError("pmf / xi values have to be real.")
        xi += np.finfo(type(xi[0])).eps
        return xi

    def get_chi(self, idx_array):
        """Return the values of ``chi`` for the specified indices.
        :param idx_array: array of indices for which the ``chi`` values should
            be calculated
        :type idx_array: numpy.array
        """
        # get_z:
        exp_value = np.exp(self.omega * idx_array * 1j)
        xy = 1 - self.success_probabilities + \
            self.success_probabilities * exp_value[:, np.newaxis]
        # sum over the principal values of the arguments of z:
        argz_sum = np.arctan2(xy.imag, xy.real).sum(axis=1)
        # get d value:
        exparg = np.log(np.abs(xy)).sum(axis=1)
        d_value = np.exp(exparg)
        # get chi values:
        chi = d_value * np.exp(argz_sum * 1j)
        return chi

    */
}
