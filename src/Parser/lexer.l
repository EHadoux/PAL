%option noyywrap

%{
#include "Predicate.h"
#include "Act.h"
#include "Rule.h"
#include "APS.h"
#include "Parser.hpp"
#include <iostream>
#define YY_DECL extern "C" int yylex()
%}

%%
[ \t\n]               {}
a\(                   { return PUB; }
h\(                   { return PRIV; }
[a-zA-Z]+             { yylval.sval = strdup(yytext); return ARG; }
=>                    { return SEP; }
&                     { return AND; }
\|                    { return OR; }
\+                    { return ADD; }
-                     { return REM; }
!                     { return NOT; }
\/                    { return PROBASEP; }
\)                    { return RP; }
#                     { return NONE; }
;                     { return RULESEP; }
0(\.[0-9]+)?|1(\.0)?  { yylval.dval = atof(yytext); return PROBA; }

%%
