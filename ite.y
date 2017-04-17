%{
	#include "lex.yy.c"
	#include<stdio.h>
	#include<string.h>
	void push();
	void codegen();
	void codegen_umin();
	void codegen_assign();
	void lab1();
	void lab2();
	void lab3();
	char st[100][10];
	int top=0;
	char i_[2]="0";
	char temp[2]="t";
	int label[20];
	int lnum=0;
	int ltop=0;
%}
%token ID NUM IF THEN ELSE
%right '='
%left '+' '-'
%left '*' '/'

%%
S : IF '(' E ')'{lab1();} THEN E ';'{lab2();} ELSE E ';'{lab3();}
  ;
E : V '='{push();} E{codegen_assign();}
  | E '+'{push();} E{codegen();}
  | E '-'{push();} E{codegen();}
  | E '*'{push();} E{codegen();}
  | E '/'{push();} E{codegen();}
  | '(' E ')'
  | V
  | NUM{push();}
  ;
V : ID {push();}
  ;
%%


int main()
{
 	printf("Enter the expression : ");
 	yyparse();
 	return 1;
}

void push()
{
  	strcpy(st[++top],yytext);
}

void codegen()
{
 	strcpy(temp,"t");
 	strcat(temp,i_);
  	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
  	top-=2;
 	strcpy(st[top],temp);
 	i_[0]++;
}

void codegen_assign()
{
 	printf("%s = %s\n",st[top-2],st[top]);
 	top-=2;
}

void lab1()
{
 	lnum++;
 	strcpy(temp,"t");
 	strcat(temp,i_);
 	printf("%s = not %s\n",temp,st[top]);
 	printf("if %s goto L%d\n",temp,lnum);
 	i_[0]++;
 	label[++ltop]=lnum;
}

void lab2()
{
	int x;
	lnum++;
	x=label[ltop--];
	printf("goto L%d\n",lnum);
	printf("L%d: \n",x);
	label[++ltop]=lnum;
}

void lab3()
{
	int y;
	y=label[ltop--];
	printf("L%d: \n",y);
}


