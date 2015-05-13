#ifndef PAL_PREDICATE_H
#define PAL_PREDICATE_H

#include <string>
#include <iostream>

namespace PAL {
    enum SCOPE { PRIV, PUB };
    class Predicate {
    public:
        Predicate(std::string argument, SCOPE scope);
        Predicate(const Predicate &other);

        std::string get_argument() const { return _argument; }
        SCOPE get_scope()          const { return _scope; }

        std::string to_string() const;
    private:
        std::string _argument;
        SCOPE       _scope;
    };
}

std::ostream& operator<<(std::ostream &s, const PAL::Predicate &p);

#endif //PAL_PREDICATE_H
