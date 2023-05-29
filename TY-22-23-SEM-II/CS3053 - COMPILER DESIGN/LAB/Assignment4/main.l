%option noyywrap
/* %option c++ */
%{
    #include<stdio.h>
    #include<stdlib.h>
%}

/* REGULAR DECLARATIONS */
function_matching (int|void|double|float|char)\s*[a-z|A-Z]\w+\s*\(\)\s*
preprocessor_directives #include\s*<.+>
variable_matching (int|void|double|float|char)\s*[a-z|A-Z]\w*\s*(;|=.+;)
function_call \s*\w\w*\(.*\);

/* RULE SECTION */
%%
{function_matching} {
    printf("HERE2");
    fprintf(yyout, "FUNCTION - %s\n", yytext);
}
{function_call} {
    printf("HERE5");
    fprintf(yyout, "FUNCTION CALL - %s\n", yytext);
}
{variable_matching} {
    printf("HERE3");
    fprintf(yyout, "VARIABLE - %s\n", yytext);
}
{preprocessor_directives} {
    fprintf(yyout, "PREPROCESSOR DIRECTIVE - %s\n", yytext);
    printf("HERE1");
}
%%

int main(){
    yyout = fopen("output.txt", "w");
    yyin = fopen("main.c", "r");

    while(!feof(yyin)){
        yylex();
    }
    return 1;
}
