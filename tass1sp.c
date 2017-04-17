/*
	NAME:TWINKLE JAGANI
	ROLL NO.:120
	AIM:Write a program to implement II pass assembler. ( For hypothetical instruction set from Dhamdhere)
		a. Consider following cases only (Literal processing not expected)
		b. Forward references
		c. DS and DC statement
		d. START, EQU
		e. Error handling: symbol used but not defined, invalid instruction/register etc.

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct SYMBOLTABLE
{
  char name[10];
  int addr,val;
}SYMBOLTABLE;
SYMBOLTABLE ST[10];

static int lc=0;
int sym_ptr=1;

char IS[][6]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char DL[][3]={"DC","DS"};
char AD[][7]={"START","END","ORIGIN","EQU","LTORG"};
char CC[][4]={"LT","LE","EQ","GT","GE","ANY"};
char RT[][5]={"AREG","BREG","CREG","DREG"};
char source[20],buffer[80],tok1[10],tok2[10],tok3[10],tok4[10],tok5[10],tok6[10],tok7[10];

int optab(char *s)
{
  int i;
  for(i=0;i<11;i++)
  {
    if(strcmp(IS[i],s)==0)
       return i;
  }
    return -1;
}

int adtab(char *s)
{
  int i;
  for(i=0;i<5;i++)
  {
    if(strcmp(AD[i],s)==0)
       return i+1;
  }
    return -1;
}

int regtab(char *s)
{
  int i;
  for(i=0;i<4;i++)
  {
    if(strcmp(RT[i],s)==0)
       return i+1;
  }
    return -1;
}
int condtab(char *s)
{
  int i;
  for(i=0;i<6;i++)
  {
    if(strcmp(CC[i],s)==0)
       return i+1;
  }
    return -1;
}

int dltab(char *s)
{
  int i;
  for(i=0;i<2;i++)
  {
    if(strcmp(DL[i],s)==0)
       return i+1;
  }
    return -1;
}

int symtab(char *a)
{
  int i;
  for(i=1;i<sym_ptr;i++)
  {
    if(strcmp(ST[i].name,a)==0)
       return i;
  }
    return -1;
}



void printsymtab()
{
  int i;
  printf("\n\n***********SYMTAB***********");
  printf("\n------------------------------\n");
  printf("\nNo.\tSYMBOL\tADDR\tLEN");
  printf("\n------------------------------\n");
  for(i=1;i<sym_ptr;i++)
     printf("\n %d\t%s\t%d\t%d",i,ST[i].name,ST[i].addr,ST[i].val);
}


void print_file(char *s)
{
  FILE *fp;
  char str[30];
  fp=fopen(s,"r");
  if(fp==NULL)
  {
     printf("\n Error in Opening file");
     exit(0);
  }
  while(fgets(str,30,fp))
      printf("%s",str);
}


void passone()
{
 	FILE *fs,*ft;
 	int p,n,i=0,j=0,k,b,t,f=0;
 	char *s;
 	fs=fopen(source,"r");
 	if(fs==NULL)
 	{
    		printf("file not found");
    		exit(0);
	}

  	ft=fopen("intermediate.txt","w");
        fprintf(ft,"***Pass one output***\n");
	
 	while(fgets(buffer,80,fs))
 	{
   		n=sscanf(buffer,"%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5);
		
		fprintf(ft,"\n");
		switch(n)
		{
			case 1://STOP OR END 
		i=optab(tok1);
	    	if(i==0)  //STOP
	    	{
	     		fprintf(ft," (IS, %02d)",i);
			fprintf(ft,"\t\t\t%d",lc);
	     		lc++;
	    	}
	       i=adtab(tok1);
	       if(i==2) //END 
	    	{
	      		fprintf(ft,"(AD, %02d)",i);
			
		}	
			
	    		break;

		case 2://START OR READ OR PRINT
	      i=adtab(tok1);
	      if(i==1)  //START
	      {
		
	      		lc=atoi(tok2)-1;
	      		fprintf(ft,"(AD, %02d) ",i);
              		fprintf(ft,"(C, %s)",tok2);
			lc++;
	      		break;
		
		
	      }
		
	     i=optab(tok1);
	     if(i==9 || i==10) //READ OR PRINT
	     {
		fprintf(ft,"(IS, %02d)",i);
	       p=symtab(tok2);
	       if(p==-1)
	       {
	       		strcpy(ST[sym_ptr].name,tok2);	       		 
			fprintf(ft," (S, %02d)",sym_ptr);
			
	       		sym_ptr++;
			
	       }
	      else
		fprintf(ft," (S, %02d)",p);	
	      
	    }
	    	fprintf(ft,"\t\t%d",lc);
		lc++;
	    break;

		case 3:
	      if(strcmp(tok2,"DS")==0)// A DS 2
	       {
		   	p=symtab(tok1);
		   	if(p==-1)
		   	{
		    		strcpy(ST[sym_ptr].name,tok1);
		    		ST[sym_ptr].addr=lc;
		    		ST[sym_ptr].val=atoi(tok3);
		    		fprintf(ft,"(DL, 02) "); 
				fprintf(ft,"(C, %02d)",atoi(tok3));
				fprintf(ft," (S, %02d)",sym_ptr);
				fprintf(ft,"\t%d",lc);
		          sym_ptr++;
		        }
		        else
		        {
		      		ST[p].addr=lc;
		      		ST[p].val=atoi(tok3);
		      		fprintf( ft,"(DL, 02)"); 
				fprintf(ft," (C, %02d)",atoi(tok3));
				fprintf(ft," (S, %02d)",p);
				fprintf(ft,"\t%d",lc);
		    	}
		   lc++;
		   break;
	       }

	       // A DC 2
	       if(strcmp(tok2,"DC")==0)
	       {
		   p=symtab(tok1);
		   if(p==-1)
		   {
		    		strcpy(ST[sym_ptr].name,tok1);
		    		ST[sym_ptr].addr=lc;
		    		ST[sym_ptr].val=atoi(tok3);
		    		fprintf(ft," (DL, 01) "); 
		    		fprintf(ft,"(C, %02d)",atoi(tok3)); 
		    		fprintf(ft," (S, %02d)",sym_ptr);
				fprintf(ft,"\t%d",lc);
		    sym_ptr++;
			
		   }
		   else
		   {
		      		ST[p].addr=lc;
		      		ST[p].val=atoi(tok3);
		      		fprintf(ft," (DL, 01) "); 
				fprintf(ft,"(C, %02d)",atoi(tok3)); 
				fprintf(ft," (S, %02d)",p);
				fprintf(ft,"\t%d",lc);
		   }
			lc++;
		   break;
	      }

	      //L3 READ A OR L3 PRINT A
	      i=optab(tok2);
	      if(i==9 || i==10)
	      {
		   p=symtab(tok1);
	   	   if(p==-1) //SYMBOL NOT FOUND IN SYMTAB
		   {
		  		strcpy(ST[sym_ptr].name,tok1);
		  		ST[sym_ptr].addr=lc;
		  		sym_ptr++;
			
		   }
		p=symtab(tok3);
		   if(p==-1)
		   {
		  		strcpy(ST[sym_ptr].name,tok3);
		  		fprintf(ft,"(IS, %02d)",i); 
				fprintf(ft," (S, %02d)",sym_ptr);
				fprintf(ft,"\t%d",lc);
		        sym_ptr++;
		   }
		else
		        fprintf(ft,"(IS, %02d) ",i); fprintf(ft,"(S, %02d)",p);
			fprintf(ft,"\t%d",lc);
		break;
	      } //end first if

	      
	      i=optab(tok1);
		if(i!=-1)
		fprintf(ft,"(IS, %02d)",i);
	      if(i>=1 && i<=8)
	      {
		//tok2[strlen(tok2)-1]='\0';
		   if(i==7) 
		    {//BC
		  	k=condtab(tok2);
                    	fprintf(ft," (CC, %02d)",k);
			k=regtab(tok3);
			if(k!=-1)
			fprintf(ft," (RT,%02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
				fprintf(ft,"\t%d",lc);
				lc++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);
			fprintf(ft,"\t%d",lc);
			lc++;			
			}
			
			break;
			}
		    }
		else if(i==4||i==5)
		    {//MOVER
			
			//tok2[strlen(tok2)-1]='\0';
			k=regtab(tok2);
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			
		  	k=regtab(tok3);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
		
		 	fprintf(ft,"\t%d",lc);
			lc++;
		  		 break;
		 	}
		if(i==1 || i==2|| i==3||i==8)//for add,sub,mul,div
		{	
				printf("in add");
				k=regtab(tok2);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok2);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok2);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
			
			k=regtab(tok3);//for token3
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
	
			}
			fprintf(ft,"\t%d",lc);
			lc++;
			break;
		   }
		 
	       //end if

		if(i==6)//comp
		{	
				printf("in add");
				k=regtab(tok2);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok2);
		       if(k	==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok2);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}

			k=regtab(tok3);//for token3
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
			fprintf(ft,"\t%d",lc);
			lc++;
			break;
		}

		  //EQU
		
	       
		}
		if(strcmp(tok2,"EQU")==0)
		{
                    
		    t=symtab(tok3);
		    j=symtab(tok1);
		   if(t==-1)
		   {
		    	//printf("\nGiven Symbol of 'Equate' is not present in symbol table...!!!");
			break;
		   }
		    if(j==-1)
		   {
		    	strcpy(ST[sym_ptr].name,tok1);
		    	ST[sym_ptr].addr=ST[t].addr;
		   }
		   else
		    	ST[j].addr=ST[t].addr;
			fprintf(ft,"(AD, 04)");
			fprintf(ft," (S, %02d)",t);
		   
		}
			
		break;
		case 4:k=symtab(tok1);//LABEL HANDLING
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok1);
				ST[sym_ptr].addr = lc;
		    		//fprintf(ft,"(S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   				
			i=optab(tok2);
			printf("tok 2 =%d",i);
		fprintf(ft,"(IS, %02d)",i);
	      if(i>=1 && i<=8)
	      {
		//tok2[strlen(tok2)-1]='\0';
		   if(i==7) 
		    {//BC
		  	k=condtab(tok3);
                    	fprintf(ft," (CC, %02d)",k);
			k=regtab(tok4);
			if(k!=-1)
			fprintf(ft," (RT,%02d)",k);
			else
			{
				k=symtab(tok4);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok4);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
				fprintf(ft,"\t%d",lc);
			lc++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);
			fprintf(ft,"\t%d",lc);
			lc++;			
			}
			
			break;
			}
		    }
		else if(i==4||i==5)
		    {//MOVER
			
			//tok2[strlen(tok2)-1]='\0';
			k=regtab(tok3);
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			
		  	k=regtab(tok4);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok4);
		       if(k==-1)

		       {
		    		strcpy(ST[sym_ptr].name,tok4);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
		
		 	fprintf(ft,"\t%d",lc);
			lc++;
		  		 break;
		 	}
		if(i==1 || i==2|| i==3||i==8)//for add,sub,mul,div
		{	
				
				k=regtab(tok3);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
			
			k=regtab(tok4);//for token3
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok4);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok4);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
	
			}
			fprintf(ft,"\t%d",lc);
			lc++;
			break;
		   }
		 
	       //end if

		if(i==6)//comp
		{	
				
				k=regtab(tok3);//for token2
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok3);
		       if(k	==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok3);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}

			k=regtab(tok4);//for token3
			if(k!=-1)
                  	fprintf(ft," (RT, %02d)",k);
			else
			{
				k=symtab(tok4);
		       if(k==-1)
		       {
		    		strcpy(ST[sym_ptr].name,tok4);
		    		fprintf(ft," (S, %02d)",sym_ptr);
               		    	sym_ptr++;
							
		       }
		   	else
		   	{ 	
			fprintf(ft," (S, %02d)",k);			
			}
			
			}
			fprintf(ft,"\t%d",lc);
			lc++;
			break;
		}

			
		}
	        }
		
	}
fcloseall();
}

void passtwo()
{
	int i,j,k,n,p,a;
	//char temp[20];
	 FILE *fi,*fo;


	fi=fopen("intermediate.txt","r");
       if(fi==NULL)
 	{
    		printf("file not found");
    		exit(0);
	}
	
      fo=fopen("target.txt","w");
	fprintf(fo,"***** Target code *****");
	lc=0;
	while(fgets(buffer,80,fi))
	{	
		n=sscanf(buffer,"%s%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5,tok6,tok7);
		
		
		if(lc==0)
		{	if(strcmp(tok1,"(AD,")==0 && strcmp(tok2,"01)")==0)
   			{
			
			lc=atoi(tok4)-1;
			fprintf(fo,"\n");	
			continue;
			}
			/*else
			printf("First statement is not start...!!!"); break;
		*/
		}
		else
		{
			fprintf(fo,"\n");	
			if(strcmp(tok1,"(AD,")!=0)
			{	
				
						lc++;
						fprintf(fo,"%d\t",lc);
				
			}
			if(strcmp(tok1,"(DL,")==0 )
   			{
			//fprintf(fo,"\n%3d)  ",lc);
			
			if(strcmp(tok2,"01)")==0)
     			{
				//lc=lc+atoi(tok4);
				fprintf(fo,"\t00\t0");
				fprintf(fo,"\t001");	
				fprintf(fo,"\n");		
			}			
			else
			fprintf(fo,"\n");
			continue;
     		
    			}

		if(strcmp(tok1,"(IS,")==0 )
   		{
			
			fprintf(fo,"\t%02d ",atoi(tok2));
			if(strcmp(tok2,"00)")==0)
 			{
			fprintf(fo,"\t00\t000\n");
			
			continue;
  			}
			if(strcmp(tok3,"(S,")==0)
 			{
    			//strcpy(tok5,tok3);
    			//strcpy(tok6,tok4);
   	 		fprintf(fo,"\t0 ");
			fprintf(fo,"\t%d\n",ST[atoi(tok4)].addr);
			
			continue;
 			}
			if(strcmp(tok3,"(RT,")==0)
			{
				fprintf(fo,"\t%d",atoi(tok4));
				if(strcmp(tok5,"(S,")==0)
				{a=atoi(tok6);				
				fprintf(fo,"\t%d\n",ST[a].addr);
				}
				continue;	
			}
			if(strcmp(tok3,"(CC,")==0)
			{
				fprintf(fo,"\t%d",atoi(tok4));
				if(strcmp(tok5,"(S,")==0)
				{a=atoi(tok6);				
				fprintf(fo,"\t%d\n",ST[a].addr);
				}
				continue;	
			}
		
		fprintf(fo,"\n");
		
     		}
		if(strcmp(tok1,"(AD,")==0 )
		{
			if(strcmp(tok2,"04)")==0)
			continue;
			if(strcmp(tok2,"02)")==0)
			fcloseall();break;
		}
		
     		}
	
	}//while
fcloseall();
}


int main()
{
	int i;
   printf("\n enter the file name:");
  scanf("%s",source);
  printf("\n***** Input File ****\n ");
  print_file(source);
  
  passone();
	printf("***Error Handling***");
  for(i=1;i<sym_ptr;i++)
	if(ST[i].addr == 0)
		printf("Symbol %s is not defined.....!! ",ST[i].name);
  printsymtab();
  //printlittab();
  //printpooltab();
  printf("\n");
  passtwo(); 
return 0;
}
/*
	OUTPUT:
nandlal@nandlal-desktop:~$ cd Desktop
nandlal@nandlal-desktop:~/Desktop$ gcc tass1sp.c
nandlal@nandlal-desktop:~/Desktop$ ./a.out

 enter the file name:input.txt

***** Input File ****
 START 101
READ N
MOVER BREG ONE 
MOVEM BREG TERM
AGAIN MULT BREG TERM
MOVER CREG TERM
ADD CREG ONE
MOVEM CREG TERM
COMP CREG N
BC LE AGAIN
DIV BREG TWO
MOVEM BREG RESULT
PRINT RESULT
STOP
N DS 1
RESULT DS 1
ONE DC 1
TERM DS 1
TWO DC 2
END
tok 2 =3in addin addin add***Error Handling***

***********SYMTAB***********
------------------------------

No.	SYMBOL	ADDR	LEN
------------------------------

 1	N	114	1
 2	ONE	116	1
 3	TERM	117	1
 4	AGAIN	104	0
 5	TWO	118	2
 6	RESULT	115	1


*/

