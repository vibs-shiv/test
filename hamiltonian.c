/*HAMILTONIAN PATH NON-RECURSIVE CODE*/

#include<stdio.h>
#define MAX 10

int G[MAX][MAX];
int x[10];

int Nextvalue(int G[MAX][MAX], int n, int k)
{
	int i,j;
	while(1)
	{
		x[k] = (x[k]+1) % (n+1);
		if(x[k] == 0)
		{
			return 1;
		}
			
		if(G[x[k-1]] [x[k]] != 0)
		{
			for(j=1; j<=k-1; j++)
			{
				if(x[j] == x[k])
				{
					break;
				}
					
			}
			if(j == k)
			{
				if((k<n) || ((k==n) && (G[x[n]] [x[1]])))
				{
					return 1;
				}
			}
		}
	}
}

void hamiltonian(int G[MAX][MAX], int n, int k)
{
	int i;
	
	while(k!=0)
	{
		Nextvalue(G,n,k);
		if(x[k] != 0)
		{
			if(k == n)
			{
				printf("\n");
				for(i=1; i<=n; i++)
				{
					printf("%d-->",x[i]);
				}
				
				printf("%d",x[1]);
				printf("\n\n");
			}
			else
			{
				k = k+1;
			}
		}
		else
		{
			k = k-1;
		}
	}
}

int main()
{
	int i,j,n;
	printf("\nEnter the no. of vertices: ");
	scanf("%d",&n);
	
	printf("\nEnter Adjancency matrix: \n");
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			G[i][j] = 0;
			x[i] = 0;
		}
	}
	for(i=1; i<=n; i++)
	{
		for(j=1; j<=n; j++)
		{
			scanf("%d",&G[i][j]);
		}
	}
	
	x[1] = 1;
	hamiltonian(G,n,2);
	return 0;
}

/*
Output:-

info02@info02-HP-Pro-3090-MT:~/Desktop/Pree167$ gcc hamiltonian.c
info02@info02-HP-Pro-3090-MT:~/Desktop/Pree167$ ./a.out

Enter the no. of vertices: 5

Enter Adjancency matrix: 
0 1 0 1 0
1 0 1 1 1
0 1 0 0 1
1 1 0 0 1
0 1 1 1 0

1-->2-->3-->5-->4-->0


1-->4-->5-->3-->2-->0

info02@info02-HP-Pro-3090-MT:~/Desktop/Pree167$ ^C
info02@info02-HP-Pro-3090-MT:~/Desktop/Pree167$ 


*/
