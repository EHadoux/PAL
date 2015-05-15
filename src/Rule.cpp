#include "Include/Rule.h"
#include <numeric>
#include <sstream>

PAL::Rule::Rule(const PAL::Rule &other) :
_premisses(other._premisses), _probabilities(other._probabilities), _acts(other._acts) {}

PAL::Rule::Rule(const std::vector<std::shared_ptr<Act>> &acts, const std::vector<double> &probabilities) :
_acts(acts), _probabilities(probabilities) {
    check_probabilities();
}

PAL::Rule::Rule(const std::vector<std::shared_ptr<Act>> &acts, const std::vector<double> &probabilities,
                const std::unordered_map<Predicate, PREMISSE_TYPE, PredicateHash, PredicateEqual> &premisses) :
_premisses(premisses), _acts(acts), _probabilities(probabilities) {
    check_probabilities();
}


void PAL::Rule::check_probabilities() const {
    double sum = std::accumulate(_probabilities.begin(), _probabilities.end(), 0.0);
    if( sum != 1 )
        throw std::invalid_argument("Probability sum should be one. Here: " + std::to_string(sum));
    if( _acts.size() != _probabilities.size() )
        throw std::invalid_argument("The number of acts should match the number of probabilities.");
}

std::string PAL::Rule::to_string() const {
    std::stringstream s;
    if( _premisses.empty() )
        s << "none";
    else {
        auto it = _premisses.cbegin();
        s << (it->second == NEG ? "!" : "") << it->first;
        for(++it; it != _premisses.cend(); ++it)
            s << " & " << (it->second == NEG ? "!" : "") << it->first;
    }
    s << " => " << _probabilities[0] << " / " << *_acts[0];
    for( unsigned int i = 1; i < _acts.size(); ++i )
        s << " | " << _probabilities[i] << " / " << *_acts[1];
    return s.str();
}

std::ostream &operator<<(std::ostream &s, const PAL::Rule &r) {
    s << r.to_string();
    return s;
}
