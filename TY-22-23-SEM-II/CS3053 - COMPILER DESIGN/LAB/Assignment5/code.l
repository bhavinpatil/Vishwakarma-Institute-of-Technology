%{
#include <stdio.h>
%}

%s IN_COMMENT

%%

"/*"    { fprintf(yyout, "%s", yytext); BEGIN(IN_COMMENT); }
"/* "    { fprintf(yyout, "%s", yytext); BEGIN(IN_COMMENT); }
"//"    { fprintf(yyout, "%s", yytext); BEGIN(IN_COMMENT); }
"// "    { fprintf(yyout, "%s", yytext); BEGIN(IN_COMMENT); }

<IN_COMMENT>"*/"    { fprintf(yyout, "%s", yytext); BEGIN(INITIAL); }
<IN_COMMENT>" "    { fprintf(yyout, "%s", yytext); BEGIN(INITIAL); }
<IN_COMMENT>" */"    { fprintf(yyout, "%s", yytext); BEGIN(INITIAL); }
<IN_COMMENT>.       { fprintf(yyout, "%s", yytext); }

[A-Z]+  { 
            if ('YY_BUFFER_STATE' == IN_COMMENT) {
                fprintf(yyout, "%s", yytext);
            }
            else {
                for (int i = 0; i < yyleng; i++) {
                    fprintf(yyout, "%c", tolower(yytext[i]));
                }
            }
        }

\n      { fprintf(yyout, "\n"); }
.       { fprintf(yyout, "%s", yytext); }

%%

int main() {
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");
    yylex();
    return 0;
}


int yywrap(){
    return 1;
}