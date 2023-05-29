/* lexer.l */

%{
#include "prog.tab.h"
extern int yylval;    

%}

%%

[ \t\n]     ;

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z]+   { yylval = strdup(yytext); return VARIABLE; }

">"         { return GREATER_THAN; }
"<"         { return LESS_THAN; }
">="        { return GREATER_THAN_EQUAL; }
"<="        { return LESS_THAN_EQUAL; }
"=="        { return EQUAL; }
"!="        { return NOT_EQUAL; }

.           { fprintf(stderr, "Invalid character: %s\n", yytext); }

%%

int yywrap(void)
{
    return 0;
}
