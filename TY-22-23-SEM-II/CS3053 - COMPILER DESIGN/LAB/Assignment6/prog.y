%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex(void);
    int yyerror(char*errormsg);
 
%token NUMBER ID 
%left '+' '-' '*' '/'

%%

grammar:expr
{
    printf("\n Exp Result: %d", $$);
    exit(0);
}


expr:expr'+'expr{$$=$1+$3}
    |expr'-'expr{$$=$1-$3}
    |expr'*'expr{$$=$1*$3}
    |expr'/'expr{$$=$1/$3}
    | '('expr')'
    |NUMBER
    |ID
    ;
%%

int main(void)
{printf("Enter the Arithmatic Expression: ");
yyparse();
printf("Arithmatic Expression Valid!!!");
yyclearin;
return 0;
}

int yyerror(char*errormsg) 
{printf("Arithmatic Expression Invalid");
exit(1);
return 1;
}