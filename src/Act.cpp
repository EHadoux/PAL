#include "Include/Act.h"
#include <sstream>

PAL::Act::Act() {}

PAL::Act::Act(const Act &other) :
_modifiers(other._modifiers) {}

/*PAL::Act::Act(const std::unordered_map<Predicate, MODIFIER_TYPE, PredicateHash, PredicateEqual> &modifiers) :
_modifiers(modifiers) {}*/

bool PAL::Act::empty() const {
    return _modifiers.empty();
}

std::string PAL::Act::to_string() const {
    std::stringstream s;
    if(empty())
        s << "none";
    else
        for(auto p : _modifiers)
            s << (p.second == ADD ? "+" : "-") << p.first << " ";
    return s.str();
}

std::ostream& operator<<(std::ostream &s, const PAL::Act &a) {
    s << a.to_string();
    return s;
};
