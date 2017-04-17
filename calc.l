%{
	#include "y.tab.h"
	int yyerror(char *s);
%}

%%
"exit"		{return exit_command;}
[ \t] 		{;}
[0-9]+		{sscanf(yytext,"%d",&yylval);return NUMBER;}
[-+*/\n] 	{return *yytext; }
. 		{yyerror("Error:Unexpected character."); return 0;}
%%

int yywrap(void)
{
	return 1;
}

