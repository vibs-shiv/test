#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct MNT
{
   char name[20];
}MNT;
MNT mnt[20];

typedef struct MDT
{
   int no;
   char code[20];
}MDT;
MDT mdt[20];

typedef struct positionPara
{
   int pno;
   char name[20];
}position;
position p[20];

typedef struct keywordPara
{
   int kno;
   char name[20];
   char val[20];
}keyword;
keyword k[20];

typedef struct Parameters
{
   int no;
   char name[20];
}PNT;
PNT pnt[10];

void MDTAB(char file[10]);
int KPDT_ptr=1,Pos_ptr=1,mdt_ptr=0, MDT_ptr=0,PNT_ptr=1,mnt_ptr=0,p_ptr=0,k_ptr=0,cnt=1,pnt_cnt=1;
char buffer[80],tok1[20],tok2[20],tok3[20],tok4[20],tok5[20],tok6[20],tok[20],def[20];
char temp[20],stat[20];

int positional_para(char *s)
{
  	int i;
  	for(i=0;i<p_ptr;i++)
  	{
    		if(strcmp(p[i].name,s)==0)
      	 	return i;
  	}
    return -1;
}

int keyword_para(char *s)
{
  	int i;
  	for(i=0;i<k_ptr;i++)
  	{
    		if(strcmp(k[i].name,s)==0)
       		return i;
  	}
    return -1;
}

void para_name_tab()
{
	int i,a;
	for(i=0;i<(p_ptr);i++)
	{
		pnt[i].no = i+1;
		strcpy(pnt[i].name,p[i].name);
		pnt_cnt++;

	}
	a = i;
	for(i=0;i<k_ptr;i++)
	{
		pnt[a].no = pnt_cnt;
		strcpy(pnt[a].name,k[i].name);
		pnt_cnt++;
	}
}

int PNT_search(char *s)
{
	int i;
	for(i=0;i<10;i++)
  	{
    		if(strcmp(pnt[i].name,s)==0)
       		return i;
  	}
	return -1;
}


void passone()
{
   	FILE *fp1;
   	int n,i,j=0,temp1=0,temp2,k1=0;
   	char s,file[20],temptok[20],temptok1[20],temptok2[20];
	printf("Enter File name:");
	scanf("%s",file);
	printf("%s",file);
   	fp1=fopen(file,"r");
   	if(fp1==NULL)
   	{
      		printf("error in opening file");
      		exit(0);
   	}
	else
   	{
		fgets(buffer,80,fp1);

       		n=sscanf(buffer,"%s%s%s%s%s%s",tok1,tok2,tok3,tok4,tok5,tok6);
  		printf("%s\t%s\t%s\t%s\t%s\t%s\t",tok1,tok2,tok3,tok4,tok5,tok6);
                if(strcmp(tok1,"MACRO")==0)
          	{
               		strcpy(mnt[mnt_ptr].name,tok2);
               		mnt_ptr++;

           	        if(tok3[0]=='&')
          		{	j=0;
                    for(temp1=0;temp1<strlen(tok3);temp1++)
                    {
                        temp2=tok3[temp1];
                        if(temp2==61)
                        {
                           // printf("This is true");
                            //printf("%d",temp1);
                            break;
                        }

                    }
                  //  printf("%d",temp1);
                    i=temp1;

				if(tok3[i]=='=')
				{
				   // printf("This is true");
				    for(k1=0;k1<temp1;k1++)
                    {
                        temptok[k1]=tok3[k1];
                    }
                    temptok[k1]='\0';
					strcpy(k[k_ptr].name,temptok);
					strcpy(p[p_ptr].name,temptok);
					p_ptr++;

					j=0;
					k[k_ptr].kno=k[k_ptr].kno+1;
					i++,j=0;;
					while(i!=20)
					{
						s=tok3[i];
	              				k[k_ptr].val[j]=s;
	                			j++;
	                			i++;
					}
				//	printf("%s",k[k_ptr].val);
                    k_ptr++;
				//	strcpy(k[k_ptr].val,def);
			 	}
				else
			        {
		 			 strcpy(p[p_ptr].name,tok3);
                 			 p_ptr++;
					 p[p_ptr].pno=p_ptr;
			        }
			}
			if(tok4[0]=='&')
          		{
                    for(temp1=0;temp1<strlen(tok4);temp1++)
                    {
                        temp2=tok4[temp1];
                        if(temp2==61)
                        {
                           // printf("This is true");
                            //printf("%d",temp1);
                            break;
                        }

                    }
                  //  printf("%d",temp1);
                    i=temp1;
				if(tok4[i]=='=')
				{

					//printf("This is true");
				    for(k1=0;k1<temp1;k1++)
                    {
                        temptok1[k1]=tok4[k1];
                    }
                    temptok[k1]='\0';
					strcpy(k[k_ptr].name,temptok1);
					strcpy(p[p_ptr].name,temptok1);
					p_ptr++;


					j=0;
					k[k_ptr].kno=k[k_ptr-1].kno+1;
					i++,j=0;;
					while(i!=20)
					{
						s=tok5[i];
	              				k[k_ptr].val[j]=s;
	                			j++;
	                			i++;
					}
					//printf("%s",k[k_ptr].val);
                    k_ptr++;
			 	}
				else
			        {
		 			 strcpy(p[p_ptr].name,tok4);
                 			 p_ptr++;
					 p[p_ptr].pno=p_ptr;
			        }
			}
			printf("\n%s",tok5);
			if(tok5[0]=='&')
          		{
                    for(temp1=0;temp1<strlen(tok5);temp1++)
                    {
                        temp2=tok5[temp1];
                        if(temp2==61)
                        {
                           // printf("This is true");
                            //printf("%d",temp1);
                            break;
                        }

                    }
                  //  printf("%d",temp1);
                    i=temp1;

				if(tok5[i]=='=')
				{
					//printf("This is true");
				    for(k1=0;k1<temp1;k1++)
                    {
                        temptok2[k1]=tok5[k1];
                    }
                    temptok[k1]='\0';
					strcpy(k[k_ptr].name,temptok2);
					//strcpy(p[p_ptr].name,temptok2);
					//p_ptr++;

					j=0;
					k[k_ptr].kno=k[k_ptr-1].kno+1;
					i++,j=0;;
					while(i!=20)
					{
						s=tok5[i];
	              				k[k_ptr].val[j]=s;
	                			j++;
	                			i++;
					}
					//printf("%s",k[k_ptr].val);
                    k_ptr++;
			 	}
				else
			        {
		 			 strcpy(p[p_ptr].name,tok5);
                 			 p_ptr++;
					 p[p_ptr].pno=p_ptr;
			        }
			}
			if(tok6[0]=='&')
          		{

				if(tok6[i]=='=')
				{
					strcpy(k[k_ptr].name,tok);
                			k_ptr++;
					j=0;
					k[k_ptr].kno=k[k_ptr].kno+1;
					while(i!=10)
					{
						s=tok3[i];
	              				def[j]=s;
	                			j++;
					}
					strcpy(k[k_ptr].val,def);
			 	}
				else
			        {
		 			 strcpy(p[p_ptr].name,tok6);
                 			 p_ptr++;
					 p[p_ptr].pno=p_ptr;
			        }
			}//end if
		}//end if


	MDTAB(file);
	}// end else

	fclose(fp1);
}

void printMNT()
{
	int i,j;
	printf("\n\n");
	printf("\nMNT");
	printf("\n name\t#PP\t#KP\t#MDTP\tKPDTP");
	for(i=0;i<mnt_ptr;i++)
	{
		printf("\n %s\t%d\t%d\t%d\t%d",mnt[i].name,p_ptr,k_ptr,MDT_ptr,KPDT_ptr);
	}
}

void printpara()
{
	int i,j,cnt=1;
	printf("\n\n");
	printf("\nParameter Table (PNTAB)");
        printf("\n+-------------+");
	for(i=0;i<pnt_cnt;i++)
	{
		printf("\n| %d |   %s   |",cnt,pnt[i].name);
		cnt++;
	}

	printf("\n+-------------+\n");

}

void printKp()
{
	int i,j;
	printf("\n\n");
	printf("\nKeyword Parameter Name Table (KPDTAB)");
        printf("\n+--------------+");
	KPDT_ptr=k_ptr;
        for(i=0;i<KPDT_ptr;i++)
	{
		printf("\n| %d |    %s    |      %s|",k[i].kno,k[i].name,k[i].val);


	}
	printf("\n+--------------+\n");

}

void printPosp()
{
	int i,j;
	printf("\n\n");
	printf("\nPositional Parameter Name Table (PPTAB)");
        printf("\n+--------------+");
	Pos_ptr=p_ptr;
        for(i=0;i<Pos_ptr;i++)
	{
		printf("\n| %d |   %s    |",p[i].pno+1,p[i].name);

	}
	printf("\n+--------------+\n");

}

void MDTAB(char file[10])
{
	int l,k,n,f=0;
	FILE *fp1;
	fp1 = fopen(file,"r");
	fgets(buffer,80,fp1);
	printf("\nMDT\n");
		printf("\n+----------------------------------------------------+");
   		while(fgets(buffer,80,fp1))
 		{
			n=sscanf(buffer,"%s%s%s",tok1,tok2,tok3);

        	switch(n)
		{
			case 1:printf("\n| %d |",cnt);
				if(strcmp(tok1,"MEND")==0)
				printf("\t %s",tok1); f=1;
				break;
			case 2:printf("\n| %d |",cnt);
			       printf("\t %s",tok1);
				l = positional_para(tok2);
				if(l!=-1)
				{
					printf("\t(P,%d)\n",l+1);
				}
				else
				{
					l = keyword_para(tok2);
					if(l!=-1)
					{
						k= PNT_search(tok2);
						printf("\t(p,%d)\n",k+1);

					}
				}
				break;
			case 3:printf("\n| %d |",cnt);
			       printf("\t %s",tok1);
				l = positional_para(tok2);
				if(l!=-1)
				{
					printf("\t(P,%d)",l+1);
				}
				else
				{
					l = keyword_para(tok2);
					if(l!=-1)
					{
						k= PNT_search(tok2);
						printf("\t(p,%d)",k+1);

					}
				}

				l = positional_para(tok3);
				if(l!=-1)
				{
					printf("\t(P,%d)\n",l+1);
				}
				else
				{
					l = keyword_para(tok3);
					if(l!=-1)
					{
						k= PNT_search(tok3);
						printf("\t(p,%d)\n",k+1);

					}
				}
				break;
			default: printf("INVALID STATEMENT");
		}//end switch
		cnt++;
			if(f==1) break;
		}//end while

	printf("\n+----------------------------------------------------+");
}

int main()
{
 	passone();
 	printMNT();
	para_name_tab();
 	printpara();
 	printKp();
 	printPosp();
 	return;
}

