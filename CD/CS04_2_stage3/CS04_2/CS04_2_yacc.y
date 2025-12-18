%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *outf;
int tempCount = 0;

char *newtemp() {
    char buf[16];
    sprintf(buf, "t%d", ++tempCount);
    return strdup(buf);
}

void emit(char *lhs, char *rhs) {
    fprintf(outf, "%s = %s\n", lhs, rhs);
    printf("%s = %s\n", lhs, rhs);
}
void emit_op(char *res, char *a, char *op, char *b) {
    fprintf(outf, "%s = %s %s %s\n", res, a, op, b);
    printf("%s = %s %s %s\n", res, a, op, b);
}

void yyerror(const char *s);
int yylex(void);
extern int yylineno;
%}


%token BCSMAIN IF ELSE WHILE INT BOOL
%token ID NUM RELOP
%token ASSIGN PLUS TIMES SEMI LBRACE RBRACE LPAREN RPAREN

%union { char *str; }
%type <str> ID NUM aexpr term factor

%left PLUS
%left TIMES
%start program

%%

program
    : BCSMAIN LBRACE declist stmtlist RBRACE
        { printf("Parsing and code generation successful.\n"); }
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
        {
            emit($1, $3);
            free($1); free($3);
        }
    | IF LPAREN expr RPAREN LBRACE stmtlist RBRACE ELSE LBRACE stmtlist RBRACE
        
    | WHILE LPAREN expr RPAREN LBRACE stmtlist RBRACE
        
    ;

expr
    : aexpr
    | aexpr RELOP aexpr  
    ;

aexpr
    : term
        { $$ = $1; }
    | aexpr PLUS aexpr
        {
            char *t = newtemp();
            emit_op(t, $1, "+", $3);
            $$ = t;
            free($1); free($3);
        }
    ;

term
    : factor
        { $$ = $1; }
    | term TIMES factor
        {
            char *t = newtemp();
            emit_op(t, $1, "*", $3);
            $$ = t;
            free($1); free($3);
        }
    ;

factor
    : ID   { $$ = $1; }
    | NUM  { $$ = $1; }
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
    if (!f) { perror("fopen"); return 1; }

    extern FILE *yyin;
    yyin = f;
    outf = fopen("CS04_2_output.txt", "w");
    if (!outf) { perror("fopen output"); return 1; }

    yyparse();
    fclose(outf);
    fclose(f);
    return 0;
}

