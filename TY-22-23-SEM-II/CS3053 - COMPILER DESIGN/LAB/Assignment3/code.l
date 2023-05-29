%{
#include <stdio.h>
#include <string.h>
int lc=0;
%}

%%

^(a|A).* { fprintf(yyout, "%s", yytext); lc++;}
.*(a|A)$ {fprintf(yyout, "%s", yytext); lc++;}
.* { }
%%

int main() {
    yyin=fopen("input.txt","r");
    yyout=fopen("output.txt","w");

    while(!feof(yyin)){
        yylex();
    }
    fprintf(yyout,"line count = %d",lc);
    return 0;
}

int yywrap(){
    return 1;
}