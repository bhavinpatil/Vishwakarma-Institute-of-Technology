%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%token NUMBER VARIABLE
%token GREATER_THAN LESS_THAN GREATER_THAN_EQUAL LESS_THAN_EQUAL EQUAL NOT_EQUAL

%left GREATER_THAN LESS_THAN GREATER_THAN_EQUAL LESS_THAN_EQUAL EQUAL NOT_EQUAL

%%

statement: expression { printf("Valid expression\n"); }
         ;

expression: operand operator operand
          ;

operand: VARIABLE
       | NUMBER
       ;

operator: GREATER_THAN
        | LESS_THAN
        | GREATER_THAN_EQUAL
        | LESS_THAN_EQUAL
        | EQUAL
        | NOT_EQUAL
        ;

%%

int main()
{
    printf("Enter a relational expression: ");
    yyparse();
    return 0;
}
int yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
    return 0;
}
