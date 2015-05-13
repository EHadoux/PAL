#ifndef PAL_ACT_H
#define PAL_ACT_H

#include "Predicate.h"
#include "Helpers.h"
#include <map>
#include <string>
#include <unordered_map>

namespace PAL {
    enum MODIFIER_TYPE {ADD, REM, NONE};
    class Act {
    public:
        Act();
        Act(const Act &other);
        //Act(const std::unordered_map<Predicate, MODIFIER_TYPE, PredicateHash, PredicateEqual> &modifiers);

        void add_modifier(const Predicate &p, MODIFIER_TYPE m) { _modifiers[p] = m; }

        bool empty() const;

        std::string to_string() const;
    private:
        std::unordered_map<Predicate, MODIFIER_TYPE, PredicateHash, PredicateEqual> _modifiers;
    };
}

std::ostream& operator<<(std::ostream &s, const PAL::Act &a);

#endif //PAL_ACT_H
