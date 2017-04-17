#include<stdio.h>
int main()
{
	int n,a[10][10],i,j;
	void flyod(int a[10][10],int n);
	printf("\nEnter the no of vertices in graph:");
	scanf("%d",&n);
	printf("\nEnter the matrix(for infinity enter 999):");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	printf("A0 matrix is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
	flyod(a,n);
	return;
}
void flyod(int d[10][10],int n)
{
	int i,j,k,p[n][n],c1=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			p[i][j]=-1;
	for(k=0;k<n;k++)
	{
		
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				c1++;
				if(d[i][j]>d[i][k]+d[k][j])
				{
					d[i][j]=d[i][k]+d[k][j];
					p[i][j]=k+1;
					
				}
			}
		}
		printf("\nMatrix A %d is:\n",k+1);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				printf("%d\t",d[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n\tTime :%d\n\n",c1);
	printf("Path from each vertex is :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(p[i][j]!=-1)
				printf("%d->%d->%d\n",i+1,p[i][j],j+1);
			else
				printf("%d->%d\n",i+1,j+1);		
		}
	}
}
/*Output:
ssl12@ssl12-ThinkCentre-M60e:~/Desktop$ gcc flyod.c
ssl12@ssl12-ThinkCentre-M60e:~/Desktop$ ./a.out

Enter the no of vertices in graph:4

Enter the matrix(for infinity enter 999):3 2 1 999
2 5 1 0
9 8 3 1
5 4 2 3
A0 matrix is:
3	2	1	999	
2	5	1	0	
9	8	3	1	
5	4	2	3	

Matrix A 1 is:
3	2	1	999	
2	4	1	0	
9	8	3	1	
5	4	2	3	

Matrix A 2 is:
3	2	1	2	
2	4	1	0	
9	8	3	1	
5	4	2	3	

Matrix A 3 is:
3	2	1	2	
2	4	1	0	
9	8	3	1	
5	4	2	3	

Matrix A 4 is:
3	2	1	2	
2	4	1	0	
6	5	3	1	
5	4	2	3	
Path from each vertex is :
1->1
1->2
1->3
1->2->4
2->1
2->1->2
2->3
2->4
3->4->1
3->4->2
3->3
3->4
4->1
4->2
4->3
4->4
*/				
			
		
