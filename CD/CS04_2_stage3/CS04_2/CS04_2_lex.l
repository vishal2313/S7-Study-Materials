%{
#include "CS04_2_yacc.tab.h"
#include <string.h>
%}

%%

 /* Keywords */ 
"BcsMain"   { return BCSMAIN; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"int"       { return INT; }
"bool"      { return BOOL; }

 /* Identifiers*/
[a-zA-Z][a-zA-Z0-9]*   { yylval.str = strdup(yytext); return ID; }

 /* Numbers */
[0-9]+                   { yylval.str = strdup(yytext); return NUM; }

 /* Relational operators */
"<"|">"|"<="|">="|"=="|"!="   { yylval.str = strdup(yytext); return RELOP; }

 /* single-character tokens */
"="     { return ASSIGN; }
"+"     { return PLUS; }
"*"     { return TIMES; }
";"     { return SEMI; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"("     { return LPAREN; }
")"     { return RPAREN; }

 /* whitespace */
[ \t\n]+   ;

 /* catch-all for illegal characters */
.         { return yytext[0]; }

%%

int yywrap(void) { return 1; }

