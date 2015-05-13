#ifndef PAL_HELPERS_H
#define PAL_HELPERS_H

#include "Predicate.h"
#include <string>

struct PredicateHash {
    std::size_t operator()(const PAL::Predicate &p) const {
        return std::hash<std::string>()(p.get_argument() + (p.get_scope() == PAL::PUB ? "a" : "h"));
    }
};

struct PredicateEqual {
    bool operator()(const PAL::Predicate &l, const PAL::Predicate &r) const {
        return l.get_argument() == r.get_argument() && l.get_scope() == r.get_scope();
    }
};

#endif //PAL_HELPERS_H
