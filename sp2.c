#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char IS[][6]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char DL[][3]={"DC","DS"};
char AD[][9]={"START","END","ORIGIN","EQU","LTORG"};
char CC[][4]={"LT","LE","EQ","GT","GE","ANY"};
char RT[][6]={"AREG","BREG","CREG","DREG"};
char buffer[80],b1[10],b2[10],b3[10],b4[10],b5[10],b6[10],b7[10];

typedef struct lit_table
{
	char name[10];
	int val;
	int addr;
}lit_table;

int i,l,r,n,p,q,a,b,c,d,lc=0,lit_ptr=0,pool_ptr=0;
lit_table lt[10];
int ltpool[10];
int optab(char *s)
{
	int i;
	for(i=0;i<11;i++)
		if(strcmp(IS[i],s)==0)
			return i;
	return -1;
}

int adtab(char *s)
{
	int i;
	for(i=0;i<5;i++)
		if(strcmp(AD[i],s)==0)
			return i+1;
	return -1;
}

int regtab(char *s)
{
	int i;
	for(i=0;i<5;i++)
		if(strcmp(RT[i],s)==0)
			return i+1;
	return -1;
}

int condtab(char *s)
{
	int i;
	for(i=0;i<7;i++)
		if(strcmp(CC[i],s)==0)
			return i+1;
	return -1;
}

int littab(char *s)
{
	int i;
	for(i=0;i<lit_ptr;i++)
	{
		if(strcmp(lt[i].name,s)==0)
			return i;
	}	
	return -1;
}
void passone()
{
	char file[20];
	FILE *fin,*fout;
	printf("Enter the file name: ");
	scanf("%s",file);
	fin = fopen(file,"r");
	if(!fin)
		perror("File Not Available");
	fout = fopen("o1.txt","w");
	ltpool[pool_ptr++]=0;
	while(fgets(buffer,80,fin))
	{
		n=sscanf(buffer,"%s%s%s%s%s",b1,b2,b3,b4,b5);
		switch(n)
		{
			case 1:{
						i=optab(b1);
						if(i==0)
						{
							fprintf(fout,"(IS, %02d )",i);
							fprintf(fout,"\t\t\t\t\t\t\t%d\n",lc++);
						}
						i=adtab(b1);
						if(i==2)
							fprintf(fout,"(AD, %02d )\n",i);
						if(i==5||i==2)
						{
							ltpool[pool_ptr]=lit_ptr;
							int j=ltpool[pool_ptr-1];
							while(j<ltpool[pool_ptr])
							{
								fprintf(fout,"(DL, 02 )");
								fprintf(fout,"(C, %02d )",lt[j].val);
								lt[j].addr=lc;
								fprintf(fout,"\t\t\t\t\t%d\n",lc++);
								j++;
							}
							pool_ptr++;
													
						}
					}
					break;
			case 2:{
						i=adtab(b1);
						if(i==1)
						{
							fprintf(fout,"(AD, %02d )",i);
							fprintf(fout,"(C, %s )\n",b2);
							lc=atoi(b2);
						}
					}
				break;
			case 4:{
						i=optab(b1);
						if(i>=1 && i<=6 | i==8)
						{
							fprintf(fout,"(IS, %02d )",i);
							r=regtab(b2);
							fprintf(fout,"(RT, %02d )",r);
							strcpy(lt[lit_ptr].name,b3);
							lt[lit_ptr].val=atoi(b4);
							fprintf(fout,"(L, %02d )",lit_ptr++);
							fprintf(fout,"\t\t\t%d\n",lc++);
						}						
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
	fin=fopen("o1.txt","r");
	if(!fin)
	{
		perror("Error");
	}
	fout=fopen("final2.txt","w");
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
				addr = lt[c].addr;
				fprintf(fout,"%d\t%02d\t%d\t%d",lc++,a,b,addr);
				
			}
		}
		else if(strcmp(b1,"(DL,")==0 && strcmp(b2,"02")==0)
		{
				fprintf(fout,"%d",lc++);
		}
		else
			continue;
		fprintf(fout,"\n");
	}
	fclose(fin);
	fclose(fout);
}

int main()
{
	passone();
	passtwo();
	printf("\nLiteral table-\n");
	for(i=0;i<lit_ptr;i++)
		printf("%d\t%s\t%d\t%d\n",i,lt[i].name,lt[i].val,lt[i].addr);
	printf("\nLiteral Pool table-\n");
	for(i=0;i<pool_ptr;i++)
		printf("%d\t%d\n",i,ltpool[i]);
	return 0;
}
