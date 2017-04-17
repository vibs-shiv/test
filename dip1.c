#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct SYMBOLTABLE
{
	char name[10];
	int addr;
	int val;
}SYMBOLTABLE;

SYMBOLTABLE st[10];
int lc=1;
int i,p,r,c,d,q,n,sym_ptr=1;

char b1[10],b2[10],b3[10],b4[10],b5[10],b6[10],b7[10],buffer[80];
char IS[][6]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char DL[][3]={"DC","DS"};
char AD[][7]={"START","END","ORIGIN","EQU","LTORG"};
char CC[][4]={"LT","LE","EQ","GT","GE","ANY"};
char RT[][5]={"AREG","BREG","CREG","DREG"};

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
    if(strcmp(st[i].name,a)==0)
       return i;
  }
    return -1;
}

void passone()
{
	char a[20];
	printf("Enter the filename: ");
	scanf("%s",a);
	FILE *fin,*fout;
	fin=fopen(a,"r");
	if(!fin)
	{
		perror("Error");
	}
	fout=fopen("output.txt","w");
	while(fgets(buffer,80,fin))
	{
		fprintf(fout,"\n");
		n=sscanf(buffer,"%s%s%s%s%s",b1,b2,b3,b4,b5);
		switch(n)
		{
			case 1:	//STOP or END
					{
						i=optab(b1);	//stop
						if(i==0)
						{	
							fprintf(fout,"(IS, %02d )",i);
							fprintf(fout,"\t\t\t\t\t\t\t%d",lc++);
						}
						i=adtab(b1);	//end
						if(i==2)
							fprintf(fout,"(AD, %02d )",i);
					}
					break;
			case 2:	//Start or Read or Print
					{
						i=optab(b1);	//Read or Print
						if(i==9|i==10)
						{	
							fprintf(fout,"(IS, %02d )",i);
							p=symtab(b2);
							if(p==-1)
							{
								strcpy(st[sym_ptr].name,b2);
								fprintf(fout,"(S, %02d )",sym_ptr);
								sym_ptr++;
							}
							else
								fprintf(fout,"(S, %02d )",p);
							fprintf(fout,"\t\t\t\t\t%d",lc++);
						}
						i=adtab(b1);
						if(i==1)
						{
							fprintf(fout,"(AD, %02d )",i);
							fprintf(fout,"(C, %s )",b2);
							lc=atoi(b2);
						}
					}
					break;
			
			case 3:	{
						i=optab(b1);	//from IS[1] to IS[8]
						if((i>=1 && i<=6) || (i==8))
						{
							fprintf(fout,"(IS, %02d )",i);
							r=regtab(b2);
							fprintf(fout,"(RT, %02d )",r);
							p=symtab(b3);
							if(p==-1)
							{
								strcpy(st[sym_ptr].name,b3);
								fprintf(fout,"(S, %02d )",sym_ptr);
								sym_ptr++;
							}
							else
								fprintf(fout,"(S, %02d )",p);
							fprintf(fout,"\t\t\t%d",lc++);
						}						
						if(i==7)
						{
							fprintf(fout,"(IS, %02d )",i);
							c=condtab(b2);
							fprintf(fout,"(CC, %02d )",c);
							p=symtab(b3);
							if(p==-1)
							{
								strcpy(st[sym_ptr].name,b3);
								fprintf(fout,"(S, %02d )",sym_ptr);
								sym_ptr++;
							}
							else
								fprintf(fout,"(S, %02d )",p);
							fprintf(fout,"\t\t\t%d",lc++);
						}	
						if(strcmp(b2,"DC")==0)
							d=1;
						if(strcmp(b2,"DS")==0)
							d=2;
						if(d==1|d==2)
						{
							fprintf(fout,"(DL, %02d )",d);
							p=symtab(b1);
							if(p==-1)
							{
								strcpy(st[sym_ptr].name,b1);
								fprintf(fout,"(S, %02d )",sym_ptr);
								st[sym_ptr].addr=lc;
								sym_ptr++;
							}
							else
							{
								st[p].addr=lc+1;
								fprintf(fout,"(S, %02d )",p);
							}
							fprintf(fout,"(C, %02d )",atoi(b3));
							fprintf(fout,"\t\t\t%d",lc++);
						}
									
					}
					break;
			case 4: {
						i=optab(b2);
						fprintf(fout,"(IS, %02d )",i);
						r=regtab(b3);
						fprintf(fout,"(RT, %02d )",r);
						q=symtab(b4);
						if(q==-1)
						{
								strcpy(st[sym_ptr].name,b1);
								fprintf(fout,"(S, %02d )",sym_ptr);
								sym_ptr++;
						}
						else
						{
							fprintf(fout,"(S, %02d )",q);
						}
						p=symtab(b1);
						strcpy(st[sym_ptr].name,b1);
						st[sym_ptr].addr=lc+1;
						sym_ptr++;
						fprintf(fout,"\t\t\t%d",lc++);
					}
					break;							
		}
	}
	fclose(fin);
	fclose(fout);
}

void passtwo()
{
	FILE *fin,*fout;
	fin=fopen("output.txt","r");
	if(!fin)
	{
		perror("Error");
	}
	fout=fopen("final.txt","w");
	lc=0;
	int a,b,c,addr;
	while(fgets(buffer,80,fin))
	{
		a=0,b=0,c=0;
		n=sscanf(buffer,"%s%s%s%s%s%s%s",b1,b2,b3,b4,b5,b6,b7);
		if(lc==0)
		{
			if((strcmp(b1,"(AD,")==0) && (strcmp(b2,"01")==0))
			{
				lc=atoi(b4);
				fprintf(fout,"\n");
			}
		}
		else if(strcmp(b1,"(IS,")==0)
		{
			if(strcmp(b2,"00")==0)
				fprintf(fout,"%d\t00\t00\t00",lc++);
			else
			{	
				a=atoi(b2);
				b=atoi(b4);
				c=atoi(b6);
				if(strcmp(b2,"09")==0 | strcmp(b2,"10")==0)
				{	
					addr = st[b].addr;
					fprintf(fout,"%d\t%d\t00\t%d",lc++,a,addr);
				}	
				else
				{
					addr = st[c].addr;
					fprintf(fout,"%d\t%02d\t%d\t%d",lc++,a,b,addr);
				}
			}
		}
		else if(strcmp(b1,"(DL,")==0)
			{	
				if(strcmp(b2,"02")==0)
					fprintf(fout,"%d",lc++);
				else if(strcmp(b2,"01")==0)
					fprintf(fout,"%d\t00\t00\t001",lc++);
			}

		fprintf(fout,"\n");
	}
	fclose(fin);
	fclose(fout);
}
int main()
{
	passone();
	passtwo();
	//printf("%d\n",lc);
	printf("\nSymbol table-\n");
	for(i=1;i<sym_ptr;i++)
		printf("%d\t%s\t%d\n",i,st[i].name,st[i].addr);
	return 0;
}
