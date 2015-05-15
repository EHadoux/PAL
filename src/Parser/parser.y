%{
#include "Predicate.h"
#include "Act.h"
#include "Rule.h"
#include "APS.h"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);

std::unique_ptr<PAL::APS> aps;
%}

%union {
    double dval;
    char *sval;
    PAL::Predicate *pval;
    PAL::Rule *rval;
    PAL::Act *act;
    std::unordered_map<PAL::Predicate, PAL::PREMISSE_TYPE, PredicateHash, PredicateEqual> *pmap;
    std::pair<double, std::shared_ptr<PAL::Act>> *pact;
    std::pair<std::vector<double>, std::vector<std::shared_ptr<PAL::Act>>> *asval;
    std::pair<bool, PAL::Predicate*> *premval;
}

%token PUB PRIV SEP AND OR ADD REM PROBASEP RP NOT NONE RULESEP
%token <sval> ARG
%token <dval> PROBA

%type <act>     modifiers
%type <pact>    act
%type <asval>   acts
%type <pval>    predicate
%type <premval> premisse
%type <pmap>    premisses
%type <rval>    rule

%start aps

%%
aps:
    aps rule RULESEP { aps->add_rule(std::make_shared<PAL::Rule>(*$2)); delete $2; }
    | rule RULESEP   { aps = std::make_unique<PAL::APS>(); aps->add_rule(std::make_shared<PAL::Rule>(*$1)); delete $1; }
    ;

rule:
    premisses SEP acts { $$ = new PAL::Rule(std::get<1>(*$3), std::get<0>(*$3), *$1); delete $1; delete $3; }
    | NONE SEP acts    { $$ = new PAL::Rule(std::get<1>(*$3), std::get<0>(*$3)); delete $3; }
    ;

premisses:
    premisses AND premisse { $$ = $1; (*$$)[*std::get<1>(*$3)] = (std::get<0>(*$3) ? PAL::POS : PAL::NEG); delete $3; }
    | premisse             { $$ = new std::unordered_map<PAL::Predicate, PAL::PREMISSE_TYPE,
                                                         PredicateHash, PredicateEqual>();
                             (*$$)[*std::get<1>(*$1)] = (std::get<0>(*$1) ? PAL::POS : PAL::NEG); delete $1; }
    ;

premisse:
    predicate       { $$ = new std::pair<bool, PAL::Predicate*>(true, $1); }
    | NOT predicate { $$ = new std::pair<bool, PAL::Predicate*>(false, $2); }
    ;

acts:
    acts OR act { $$ = $1; std::get<0>(*$$).push_back(std::get<0>(*$3)); std::get<1>(*$$).push_back(std::get<1>(*$3));
                  delete $3; }
    | act       { $$ = new std::pair<std::vector<double>,std::vector<std::shared_ptr<PAL::Act>>>({std::get<0>(*$1)},{std::get<1>(*$1)});
                  delete $1; }
    ;

act:
    PROBA PROBASEP modifiers { $$ = new std::pair<double, std::shared_ptr<PAL::Act>>($1, std::make_shared<PAL::Act>(*$3)); delete $3; }
    | PROBA PROBASEP NONE    { $$ = new std::pair<double, std::shared_ptr<PAL::Act>>($1, std::make_shared<PAL::Act>()); }
    ;

modifiers:
    modifiers AND ADD predicate   { $$ = $1; $$->add_modifier(*$4, PAL::ADD); delete $4; }
    | modifiers AND REM predicate { $$ = $1; $$->add_modifier(*$4, PAL::REM); delete $4; }
    | ADD predicate               { $$ = new PAL::Act(); $$->add_modifier(*$2, PAL::ADD); delete $2; }
    | REM predicate               { $$ = new PAL::Act(); $$->add_modifier(*$2, PAL::REM); delete $2; }
    ;

predicate:
    PUB ARG RP    { $$ = new PAL::Predicate(std::string($2), PAL::PUB); }
    | PRIV ARG RP { $$ = new PAL::Predicate(std::string($2), PAL::PRIV); }
    ;

%%
void set_input(FILE *in) {
    yyin = in;
}

std::unique_ptr<PAL::APS> parse() {
    yyparse();
    return move(aps);
}

void yyerror (char const *s) {
    fprintf (stderr, "%s\n", s);
}
