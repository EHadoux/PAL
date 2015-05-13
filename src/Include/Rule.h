#ifndef PAL_RULE_H
#define PAL_RULE_H

#include "Act.h"
#include "Predicate.h"
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

namespace PAL {
    enum PREMISSE_TYPE { POS, NEG, UNDEF };

    class Rule {
    public:
        Rule(const std::vector<std::shared_ptr<Act>> &acts, const std::vector<double> &probabilities);
        Rule(const std::vector<std::shared_ptr<Act>> &acts, const std::vector<double> &probabilities,
             const std::unordered_map<Predicate, PREMISSE_TYPE, PredicateHash, PredicateEqual> &premisses);
        Rule(const Rule &other);

        std::string to_string() const;
    private:
        void check_probabilities() const;

        std::unordered_map<Predicate, PREMISSE_TYPE,
                PredicateHash, PredicateEqual> _premisses;
        std::vector<std::shared_ptr<Act>>      _acts;
        std::vector<double>                    _probabilities;
    };
}

std::ostream& operator<<(std::ostream &s, const PAL::Rule &r);

#endif //PAL_RULE_H
