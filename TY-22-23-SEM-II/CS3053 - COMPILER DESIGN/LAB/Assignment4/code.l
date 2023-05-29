%{
#include <stdio.h>
%}

%%

"auto" | "break" | "case" | "char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" { fprintf(yyout, "Keyword: %s\n", yytext); }


"(" { fprintf(yyout, "Left Parenthesis\n"); }
")" { fprintf(yyout, "Right Parenthesis\n"); }
"{" { fprintf(yyout, "Left Brace\n"); }
"}" { fprintf(yyout, "Right Brace\n"); }
"[" { fprintf(yyout, "Left Bracket\n"); }
"]" { fprintf(yyout, "Right Bracket\n"); }
";" { fprintf(yyout, "Semicolon\n"); }
"," { fprintf(yyout, "Comma\n"); }
"." { fprintf(yyout, "Period\n"); }
"->" { fprintf(yyout, "Structure Pointer\n"); }
"++" { fprintf(yyout, "Increment\n"); }
"--" { fprintf(yyout, "Decrement\n"); }
"+"|"-"|"*"|"/"|"%" { fprintf(yyout, "Arithmetic Operator: %s\n", yytext); }
"=" { fprintf(yyout, "Assignment Operator\n"); }
"=="|"!="|"<"|">"|"<="|">=" { fprintf(yyout, "Relational Operator: %s\n", yytext); }
"&&" { fprintf(yyout, "Logical AND\n"); }
"||" { fprintf(yyout, "Logical OR\n"); }
"!" { fprintf(yyout, "Logical NOT\n"); }
"&" { fprintf(yyout, "Bitwise AND\n"); }
"|" { fprintf(yyout, "Bitwise OR\n"); }
"^" { fprintf(yyout, "Bitwise XOR\n"); }
"~" { fprintf(yyout, "Bitwise NOT\n"); }
"<<"|">>" { fprintf(yyout, "Bitwise Shift: %s\n", yytext); }
"?" { fprintf(yyout, "Conditional Operator\n"); }
":" { fprintf(yyout, "Colon\n"); }

[0-9]+ { fprintf(yyout, "Number: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { fprintf(yyout, "Identifier: %s\n", yytext); }
. { fprintf(yyout, "Invalid Character\n"); }

%%

int main() {
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");
    while(!feof(yyin)){
        yylex();
    }
    return 0;
}

int yywrap(){
    return 1;
}