%{
%}

%%
Hello|hello { printf("Typed Hello|hello");}
World|world { printf("displayed world");}
[ ]+ {}
%%

int main(){
yylex();
return 0;
}

int yywrap(){
    return 1;
}