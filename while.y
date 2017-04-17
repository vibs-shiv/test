%{
	#include "lex.yy.c"
	#include<stdio.h>
	#include<string.h>
	void push();
	void codegen();
	void codegen_assign();
	void codegen_assign1();
	void while_kw();
	void cond();
	void trueblk();
	char st[100][10];
	int top=0;
	char subscript[2]="0";
	char temp[2]="t";
	int lnum=1;
	int start=1;

%}

%start S
%token ID NUM WHILE 
%right '=' '<'
%left '+' '-'
%left '*' '/'
%%

S : 	WHILE{while_kw();} '(' E ')'{cond();} E ';'{trueblk();}
  	;
E : 	V '='{push();} E{codegen_assign();}
  	| E '+'{push();} E{codegen();}
  	| E '-'{push();} E{codegen();}
  	| E '*'{push();} E{codegen();}
  	| E '/'{push();} E{codegen();}
  	| '(' E ')'
  	| V
  	| NUM{push();}
  	;
V :   	ID {push();}
  	;
%%

int main()
{
 	printf("Enter the expression : ");
 	yyparse();
}
void push()
{
  	strcpy(st[++top],yytext);
}

void codegen()
{
 	strcpy(temp,"t");
 	strcat(temp,subscript);
  	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
  	top-=2;
 	strcpy(st[top],temp);
 	subscript[0]++;
}

void codegen_assign()
{
 	printf("%s %s %s\n",st[top-2],st[top-1],st[top]);
 	top-=2;
}

void codegen_assign1()
{
 	printf("%s < %s\n",st[top-2],st[top]);
 	top-=2;
}

void while_kw()
{
	printf("L%d: \n",lnum++);
}

void cond()
{
 	strcpy(temp,"t");
 	strcat(temp,subscript);
 	printf("%s = not %s\n",temp,st[top]);
 	printf("if %s goto L%d\n",temp,lnum);
 	subscript[0]++;
}

void trueblk()
{
	printf("goto L%d \n",start);
	printf("L%d: \n",lnum);
}



