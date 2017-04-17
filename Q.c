
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

int x[20]={0},count=0;

void main()
{
	int n;
	void nQueens(int k,int n);
	printf("Enter no. of Queens:");
	scanf("%d",&n);
	nQueens(1,n);
	printf("\nTotal solutions=%d",count);
}

void print_sol(int n)
{
 	int i,j;
 	count++;
 	printf("\n\nSolution #%d:\n",count);
 	for(i=1;i<=n;i++)
 	{
  		for(j=1;j<=n;j++)
  		{
   			if(x[i]==j)
    				printf("Q\t");
    		
   		else
    			printf("*\t");
  		}
  		printf("\n");
 	}
}

void nQueens(int k,int n)
{
	int i;
	int place(int k,int i);	
	
	for(i=1;i<=n;i++)
	{
		
		if(place(k,i))
		{
			x[k] =i;
			
			if(k==n)
			{
				print_sol(n);
			}
			else
			nQueens(k+1,n);
		}
	}
}

int place(int k,int i)
{
	int j;
	for(j=1;j<=k-1;j++)
	{
            if((x[j]==i)||(abs(x[j]-i)==abs(j-k)))
		return 0;

	}
	return 1;
}


