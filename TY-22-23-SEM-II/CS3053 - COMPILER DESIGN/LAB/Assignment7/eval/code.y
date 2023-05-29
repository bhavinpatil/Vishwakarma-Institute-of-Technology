%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%token NUMBER VARIABLE
%token GREATER_THAN LESS_THAN GREATER_THAN_EQUAL LESS_THAN_EQUAL EQUAL NOT_EQUAL

%left GREATER_THAN LESS_THAN GREATER_THAN_EQUAL LESS_THAN_EQUAL EQUAL NOT_EQUAL

%%

statement: expression { printf("Result: %d\n", $1); }
         ;

expression: operand operator operand { $$ = evaluate_expression($1, $2, $3); }
          ;

operand: VARIABLE { $$ = get_variable_value($1); }
       | NUMBER   { $$ = $1; }
       ;

operator: GREATER_THAN        { $$ = GREATER_THAN; }
        | LESS_THAN           { $$ = LESS_THAN; }
        | GREATER_THAN_EQUAL  { $$ = GREATER_THAN_EQUAL; }
        | LESS_THAN_EQUAL     { $$ = LESS_THAN_EQUAL; }
        | EQUAL               { $$ = EQUAL; }
        | NOT_EQUAL           { $$ = NOT_EQUAL; }
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

int evaluate_expression(int operand1, int operator, int operand2)
{
    switch (operator) {
        case GREATER_THAN:
            return operand1 > operand2;
        case LESS_THAN:
            return operand1 < operand2;
        case GREATER_THAN_EQUAL:
            return operand1 >= operand2;
        case LESS_THAN_EQUAL:
            return operand1 <= operand2;
        case EQUAL:
            return operand1 == operand2;
        case NOT_EQUAL:
            return operand1 != operand2;
        default:
            printf("Invalid operator\n");
            return 0;
    }
}