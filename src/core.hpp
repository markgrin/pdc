#ifndef HPP_BDC1456B1CD84B7DB6020CBEB869342E

#define HPP_BDC1456B1CD84B7DB6020CBEB869342E

#include "call.hpp"

#include <string>
#include <vector>
#include <map>


namespace pdc {

class Core {
public:
    std::map<std::string, std::vector<Call>> datasets;
};

} // namespace pdc

#endif // HPP_BDC1456B1CD84B7DB6020CBEB869342E
