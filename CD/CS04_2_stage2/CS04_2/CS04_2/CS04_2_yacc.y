%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void yyerror(const char *s);
int yylex(void);
extern int yylineno;
%}

/* tokens */
%token BCSMAIN IF ELSE WHILE INT BOOL
%token ID NUM RELOP
%token ASSIGN PLUS TIMES SEMI LBRACE RBRACE LPAREN RPAREN

/* token values (store strings for IDs/NUM/RELOP ) */
%union {
    char *str;
}

/* token types that use the union */
%type <str> ID NUM RELOP

/* precedence and associativity */
%left PLUS
%left TIMES
%start program

%%

program
    : BCSMAIN LBRACE declist stmtlist RBRACE
        {  }
    ;


declist
    : decl
    | declist decl
    ;


decl
    : type ID SEMI
    ;


type
    : INT
    | BOOL
    ;


stmtlist
    : stmt
    | stmtlist SEMI stmt
    ;


stmt
    : ID ASSIGN aexpr
    | IF LPAREN expr RPAREN LBRACE stmtlist RBRACE ELSE LBRACE stmtlist RBRACE
    | WHILE LPAREN expr RPAREN LBRACE stmtlist RBRACE
    ;


expr
    : aexpr
    | aexpr RELOP aexpr
    ;


aexpr
    : term
    | aexpr PLUS aexpr
    ;


term
    : factor
    | term TIMES factor
    ;


factor
    : ID
    | NUM
    ;

%%

void yyerror(const char *s) {
    printf("Syntax Error\n");
    exit(0); 
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
        return 1;
    }
    
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }
    
    extern FILE *yyin;
    yyin = f;
    if (yyparse() == 0) {
        printf("Parsing Successful\n");
    } 
    
    return 0;
}

