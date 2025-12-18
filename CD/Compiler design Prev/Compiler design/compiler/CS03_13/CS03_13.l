%{
#include "y.tab.h"
%}

%%

"BcsMain"      { return BCSMAIN; }
"int"          { return INT; }
"bool"         { return BOOL; }
"if"           { return IF; }
"else"         { return ELSE; }
"while"        { return WHILE; }

"{"            { return LBRACE; }
"}"            { return RBRACE; }
"("            { return LPAREN; }
")"            { return RPAREN; }
";"            { return SEMICOLON; }
"="            { return ASSIGN; }

"<"            { return LT; }
">"            { return GT; }
"<="           { return LE; }
">="           { return GE; }
"=="           { return EQ; }
"!="           { return NE; }

"+"            { return PLUS; }
"*"            { return MULT; }

[0-9]+         { yylval.num = atoi(yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = strdup(yytext); return ID; }

[ \t\n]+       { /* Ignore whitespace */ }
.              { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

