#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct set //Each state of a DFA is a set of ststes of NFA
 {
	int states[15];
 }set;

typedef struct treenode //Structure of a node of syntax tree
  {
    char data;
    int nullable,nodeno;
    set firstpos,lastpos;
    struct treenode *left,*right;
  }treenode;

treenode * leafnodes[20]; //Array storing addresses of leaf nodes of syntax tree

set followpos[20];//For storing follow position of each node

int nodeno=0;

 char alphabets[10]={""}; //Set of input alphabet
 char DFAT[10][4]; //For string state transition table of final DFA
 set DFAxlat[10]; //For storing states of final DFA
 char nextstate=0,postfix[20];
 int visited[10],DFAstate=0;

 treenode *convert(char x);
 treenode * create_tree(char *postfix);
set setunion(set x,set y);
int setequal(set A, set B);
int insertDFAlat(set x);
void constructDFA(treenode *);
void setinsert(set *p,int  x);
int member(set myset,int  x);
int insertDFAxlat(set);

/***********    infix to postfix */

char st[20];
int top1=-1;

void push(char x)
  {
    top1++;
    st[top1]=x;
  }

char pop()
 {
   char x;
   x=st[top1];
   top1--;
   return(x);
}

int precedence(char x)
  {
    if(x=='(')
	return(0);
    if(x=='+')
	return(1);
    if(x=='.')
	return(2);
    if(x=='*')
	return(3);
    return(4);
  }

void convert_postfix()
   {
     char x,y;
     int i=0;
     //flushall();
     //clrscr();
     printf("\nenter a regular expression:");
    while((x=getchar())!='\n')
     {
	switch(x)
	  {
		case '(':push(x);break;
		case ')':y=pop();
			 while(y!='(')
			  {
				postfix[i++]=y;
				y=pop();
			  }
			break;
		case '*': postfix[i++]='*';break;
		case '+':
		case '.': while(top1 !=-1 && precedence(st[top1])>=precedence(x))
			    {
				y=pop();
				postfix[i++]=y;
			    }
			push(x);
			break;
		default: postfix[i++]=x;
	   }
	}
	while(top1!=-1)
	  {
		x=pop();
		postfix[i++]=x;
	  }
	postfix[i++]='X';//Augmented with the symbol X
	postfix[i++]='.';
	postfix[i]='\0';

  }

/*****************************************/

 void initialize() //Initialize the state transition table of final DFA
   {
      int i,j,k;
      for(i=0;i<10;i++)
	for(j=0;j<4;j++)
	     DFAT[i][j]='-';

   }

void print_DFA()
 {
	int i,j;
	printf("\n DFA************\n");
	i=strlen(alphabets);
	alphabets[i-1]=0;
	printf("\n");
	for(i=0;alphabets[i]!=0;i++)
		printf("\t%c",alphabets[i]);
	printf("\n---------------------------------");
	for(i=0;i<DFAstate;i++)
	  {
		printf("\n%d|",i);
		for(j=0;alphabets[j]!=0;j++)
			printf("\t%c",DFAT[i][j]);
	  }

 }

void printset(set x)
 {
   int i;
   for(i=1;i<=x.states[0];i++)
     printf(" %d ",x.states[i]);
 }



void postorder(treenode *p) //calculate fist,last and follow position
 {
   int i;
   if(p!=NULL)
    {
      postorder(p->left);
      postorder(p->right);
      if(p->left==NULL && p->right==NULL)
	{
		p->nullable=0;
		setinsert(&(p->firstpos),p->nodeno);
		p->lastpos=p->firstpos;
	}
      else
       switch(p->data)
	{
	  case '+':p->nullable=p->left->nullable || p->right->nullable;
		      p->firstpos=setunion(p->left->firstpos,p->right->firstpos);
		      p->lastpos=setunion(p->left->lastpos,p->right->lastpos);
		     break;

	  case '.':p->nullable=p->left->nullable && p->right->nullable;
		     if(p->left->nullable)
		     p->firstpos=setunion(p->left->firstpos,p->right->firstpos);
		     else
		     p->firstpos=p->left->firstpos;
		     if(p->right->nullable)
		     p->lastpos=setunion(p->left->lastpos,p->right->lastpos);
		     else
		     p->lastpos=p->right->lastpos;

		     for(i=1;i<=p->left->lastpos.states[0];i++)
			followpos[p->left->lastpos.states[i]]=
			     			setunion(followpos[p->left->lastpos.states[i]],p->right->firstpos);
		   break;

	  case '*' :p->nullable=1;
		    p->firstpos=p->left->firstpos;
		    p->lastpos=p->left->lastpos;

		     for(i=1;i<=p->lastpos.states[0];i++)
			followpos[p->lastpos.states[i]]=
			     setunion(followpos[p->lastpos.states[i]],p->firstpos);

	}
   }

 }



void main()
 {
	treenode *root;
	int i;
	convert_postfix();
	printf("\n\npostfix expression= %s",postfix);
	initialize();
	root=create_tree(postfix);
	//printf("\ninput alphabets :%s\n",alphabets);
	//printf("\nPostorder Traversal on Tree : ");
	postorder(root);
	printf("\n\nFollow positions :\n");
	for(i=0;i<nodeno;i++)
	 {
		printf("\n%d : ",i);
		printset(followpos[i]);
	 }

	constructDFA(root);
	print_DFA();
	printf("\n\nTranslation table :\n");
	for(i=0;i<DFAstate;i++)
	  {
	     printf("\n state %d is => {",i);
	     printset(DFAxlat[i]);
	     printf("}");
	  }
	printf("\n\nSet of Final states:\n ");
	for(i=0;i<DFAstate;i++)
	  {
	    if(member(DFAxlat[i],nodeno-1))
		{
		   printf("\nState %d is a final state=>{",i);
		   printset(DFAxlat[i]);
		   printf("}");
		}
	 }

	//getch();
 }

 treenode *convert(char x)
   {
     treenode *temp;
     int i;
     temp=(treenode*)malloc(sizeof(treenode));
     temp->data=x;
     temp->left=temp->right=NULL;
     temp->firstpos.states[0]=0;
     temp->lastpos.states[0]=0;
    if(isalnum(x))
       {
	for(i=0;alphabets[i]!=0 && x!=alphabets[i];i++);
		if(alphabets[i]==0)
		   {
		      alphabets[i]=x;
		      alphabets[i+1]=0;
		   }
	leafnodes[nodeno]=temp;
	followpos[nodeno].states[0]=0;
	temp->nodeno=nodeno;
	nodeno++;
      }
  return(temp);
 }

 treenode * create_tree(char *postfix)
  { int i;
    treenode *temp,*temp1,*temp2;
    treenode *stack[30];
    int top=-1;
    for(i=0;postfix[i]!=0;i++)
     {
       if(isalnum(postfix[i]))
	   {
		temp=convert(postfix[i]);
		top++;
		stack[top]=temp;
	   }
	else
	 switch(postfix[i])
	   {
	      case '+':
	      case '.':temp=convert(postfix[i]);
		       temp->right=stack[top];
		       temp->left=stack[top-1];
		       stack[top-1]=temp;
		       top--;break;
	      case '*': temp=convert(postfix[i]);
			temp->left=stack[top];
			stack[top]=temp;
		       break;
	     }
	 }
     return(stack[top]);
   }

 set setunion(set x,set y)
     {
       set myset;
       int i;
       myset=x;
       for(i=1;i<=y.states[0];i++)
		if(!member(myset,y.states[i]))
			setinsert(&myset,y.states[i]);
       return(myset);
     }
 int member(set myset,int x)
  {
    int i;
    for(i=1;i<=myset.states[0];i++)
    if(x==myset.states[i])
	return(1);
    return(0);
  }
 void setinsert(set *p,int x)
   {
     int i;
     for(i=p->states[0];i>=1 && x<p->states[i];i--)
		p->states[i+1]=p->states[i];
     p->states[i+1]=x;
     (p->states[0])++;
    }

 int setequal(set A, set B)
  {
    int i;
    for(i=0;i<=A.states[0];i++)
	if(A.states[i]!=B.states[i])
		return(0);
    return(1);
   }

 int insertDFAXlat(set x)
  {
    int i;
    for(i=0;i<DFAstate;i++)
	if(setequal(x,DFAxlat[i]))
		return(i);
    DFAxlat[i]=x;
    DFAstate++;
    return(i);
   }
 void constructDFA(treenode *p)
  {
    int i,flag,k,j,temp,cnode;
    int stateno; set fromstate, tostate,closeset;
    stateno=insertDFAxlat(p->firstpos);
    for(i=0;i<10;i++)
	visited[i]=0;
    do
     {
       flag=1;
       for(i=0;i<DFAstate;i++)
	{
	   if(!visited[i])
	     {
	       visited[i]=1;
	       flag=0;
	       fromstate=DFAxlat[i];
	       for(k=0;alphabets[k]!='\0';k++)
		 {
		   tostate.states[0]=0;
		   for(j=1;j<=fromstate.states[0];j++)
		    {
			cnode=fromstate.states[j];
			if(leafnodes[cnode]->data==alphabets[k])
				tostate=setunion(tostate,followpos[cnode]);
		    }
		  if(tostate.states[0]>0)
		    {
			stateno=insertDFAxlat(tostate);
			DFAT[i][k]=stateno+48;
		    }
		 }
	     }
	}
     }while(flag==0);
   }

int insertDFAxlat( set x )
 {
    int i;
    for(i=0;i<DFAstate;i++)
	if(setequal(x,DFAxlat[i]))
		return(i);
    DFAxlat[i]=x;
    DFAstate++;
    return(i);
 }

/*
*****************  Input/Output **************
==================

enter a regular expression:(a+b)*.a.b.b
postfix expression= ab+*a.b.b.X.

Follow positions :

0 :  0  1  2
1 :  0  1  2
2 :  3
3 :  4
4 :  5
5 :
 DFA************

        a       b
---------------------------------
0|      1       0
1|      1       2
2|      1       3
3|      1       0

Translation table :

 state 0 is => { 0  1  2 }
 state 1 is => { 0  1  2  3 }
 state 2 is => { 0  1  2  4 }
 state 3 is => { 0  1  2  5 }

Set of Final states:

State 3 is a final state=>{ 0  1  2  5 }
*/
