#include "Include/APS.h"
#include <sstream>

PAL::APS::APS() {}

/*PAL::APS::APS(const std::vector<std::shared_ptr<Rule>> &rules) :
_rules(rules) {}*/

std::string PAL::APS::to_string() const {
    std::stringstream s;
    for( auto r : _rules )
        s << *r << std::endl;

    return s.str();
}

std::ostream& operator<<(std::ostream &s, const PAL::APS &r) {
    s << r.to_string();
    return s;
}
