#include "Include/Predicate.h"
#include <sstream>

PAL::Predicate::Predicate(std::string argument, PAL::SCOPE scope) :
_argument(argument), _scope(scope) {}

PAL::Predicate::Predicate(const PAL::Predicate &other) :
_argument(other._argument), _scope(other._scope) {}

std::string PAL::Predicate::to_string() const {
    std::stringstream s;
    s << (_scope == PUB ? "a(" : "h(") << _argument << ")";
    return s.str();
}

std::ostream& operator<<(std::ostream &s, const PAL::Predicate &p) {
    s << p.to_string();
    return s;
}

