%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    extern int yylex();
    extern int yyparse();
    extern FILE *yyin;
    void yyerror(const char *s);
    int yydebug = 1; // Enable debugging

    typedef union {
        int num;
        char *str;
    } YYSTYPE;

    #define YYSTYPE_IS_DECLARED 1
%}

%union {
    int num;
    char *str;
}

%token <num> NUM
%token <str> ID
%token BCSMAIN INT BOOL IF ELSE WHILE
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON ASSIGN
%token LT GT LE GE EQ NE PLUS MULT

%%

program : BCSMAIN LBRACE declist stmtlist RBRACE { printf("Parsing Successful\n"); }
        ;

declist : declist decl
        | decl
        ;

decl : type ID SEMICOLON
     ;

type : INT
     | BOOL
     ;

stmtlist : stmtlist stmt SEMICOLON
         | stmt SEMICOLON
         ;

stmt : ID ASSIGN aexpr
     | IF LPAREN expr RPAREN LBRACE stmtlist RBRACE ELSE LBRACE stmtlist RBRACE
     | WHILE LPAREN expr RPAREN LBRACE stmtlist RBRACE
     ;

expr : aexpr relop aexpr
     | aexpr
     ;

aexpr : aexpr PLUS term
      | term
      ;

term : term MULT factor
     | factor
     ;

factor : ID
       | NUM
       ;

relop : LT | GT | LE | GE | EQ | NE
      ;

%%

void yyerror(const char *s) {
    printf("Syntax Error\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    yyin = file;
    yydebug = 1;  // Enable parser debugging
    yyparse();
    
    fclose(file);
    return 0;
}

