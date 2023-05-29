%{
    int wc=0,cc=0,lc=0,sc=0;
%}

%%
[a-zA-Z]+ {
    cc=cc+yyleng;
    wc++;
    }
[ ] {sc++;}
[\n] {lc++;}
%%

int main(){
yyin=fopen("input.txt","r");
yyout=fopen("output.txt","w");

while(!feof(yyin)){
    yylex();
}
fprintf(yyout,"wc= %d, cc= %d, lc= %d, sc= %d",wc,cc,lc,sc);



return 0;
}

int yywrap(){
    return 1;
}