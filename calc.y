%{
	int yyerror(char *s);
	#include<stdio.h>
	#include<stdlib.h>
%}
%start list
%token NUMBER
%token exit_command
%left '+' '-'
%left '*' '/'

%%
list:
	|list '\n' 
	|list expr '\n' {printf("Answer=%d\n",$2);}
	|list exit_command '\n' {exit(0);}
	;
expr: 	NUMBER {$$=$1;}
	|expr '+' expr {$$=$1+$3;}
	|expr '-' expr {$$=$1-$3;}
	|expr '*' expr {$$=$1*$3;}
	|expr '/' expr {$$=$1/$3;}
	;
%%

int main()
{
	yyparse();
	return 0;
}

int yyerror(char *s)
{
	fprintf(stderr,"*%s*\n",s);
	return 0;
}
