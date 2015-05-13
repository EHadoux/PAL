#ifndef PAL_APS_H
#define PAL_APS_H

#include "Rule.h"
#include <vector>
#include <string>
#include <iostream>
#include <memory>

namespace PAL {
    class APS {
    public:
        APS();
        //APS(const std::vector<std::shared_ptr<Rule>> &rules);

        void add_rule(const std::shared_ptr<Rule> &r) { _rules.push_back(r); }

        std::string to_string() const;
    private:
        std::vector<std::shared_ptr<Rule>> _rules;
    };
}

std::ostream& operator<<(std::ostream &s, const PAL::APS &r);

#endif //PAL_APS_H
