%{
    #include<stdio.h>
%}

%% 

[0-9]+ {printf("Integer Token\n");}   
.* {}

%%

int yywrap (void){}

int main()
{
    printf("Enter Input Data: ");
    yylex();
    return 0;
}