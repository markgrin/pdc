#ifndef HPP_29B9211B3290496DAB726C9F806B2D67

#define HPP_29B9211B3290496DAB726C9F806B2D67

#include "../call.hpp"

#include <vector>

namespace pdc {

std::vector<Call> load ();
void save (const std::vector<Call>& dataset);

} // namespace pdc

#endif // HPP_29B9211B3290496DAB726C9F806B2D67
