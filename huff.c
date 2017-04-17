#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 10
int n,cnt = 0, counter = 0,logn=0;
typedef struct _treenode treenode;
struct _treenode
{
	int freq;
	char ch;
	treenode *left, *right;
};
typedef struct _pq
{
	int heap_size;
	treenode *A[MAX];
}PQ;
struct BinaryCodes
{
	char ch;
	char word[10];
}codes[MAX];
void create_pq (PQ *p)
{
	p->heap_size = 0;
}
int parent (int i)
{
	return (i-1)/2;
}
int left (int i)
{
	return i*2+1;
}
int right (int i)
{
	return i*2+2;
}
void heapify (PQ *p, int i)
{
	int l, r, smallest;
	counter++;
	treenode *t;
	l = left(i);
	r = right(i);
	if(l < p->heap_size && p->A[1]->freq < p->A[i]->freq)
		smallest = 1;
	else smallest = i;
	if(r < p->heap_size && p->A[r]->freq < p->A[smallest]->freq)
		smallest = r;
	if (smallest != i)
	{
		t = p->A[i];
		p->A[i] = p->A[smallest];
		p->A[smallest] = t;
		heapify(p, smallest);
	}
	if(logn<counter)
		logn=counter;
	counter = 0;	
}
void insert_pq (PQ *p, treenode *r)
{
	int i;
	p->heap_size++;
	i = p->heap_size - 1;
	while(i>0 && p->A[parent(i)]->freq > r->freq)
	{
		p->A[i] = p->A[parent(i)];
		i = parent(i);
	}
	p->A[i] = r;
}
treenode *extract_min_pq (PQ *p)
{
	treenode *r;
	if(p->heap_size == 0)
	{
		printf("\nHeap underflow\n");
		exit (1);
	}
	r = p->A[0];
	p->A[0] = p->A[p->heap_size-1];
	p->heap_size--;
	//printf("nlogn_Counter = %d\n",cnt++);
	cnt++;
	heapify(p, 0);
	return r;
}
treenode *build_huffman(char cha[MAX], int freqs[MAX], int num)
{
	int i, n;
	treenode *x, *y, *z;
	PQ p;
	create_pq(&p);
	for(i=0;i<num;i++)
	{
		x = malloc (sizeof(treenode));
		x->left = NULL;
		x->right = NULL;
		x->freq = freqs[i];
		x->ch = cha[i];
		insert_pq (&p, x);
	}
	n = p.heap_size-1;
	for(i=0;i<n;i++)
	{
		z = malloc(sizeof(treenode));
		x = extract_min_pq(&p);
		y = extract_min_pq(&p);
		z->left = x;
		z->right = y;
		z->freq = x->freq + y->freq;
		insert_pq(&p, z);
	}
	return extract_min_pq(&p);
}
void preorder(treenode *p, int i, char word[])
{
	int j;
	if(p!=NULL)
	{
		if(p->left == NULL && p->right == NULL)
		{
			word[i] = 0;
			//printf("\n%c - %s", p->ch, word);
			j = n++;
			codes[j].ch = p->ch;
			strcpy(codes[j].word, word);
		}
		word[i] = '0';
		preorder(p->left, i+1, word);
		word[i] = '1';
		preorder(p->right, i+1, word);
	}
}
void encode (char msg[])
{
	int i,j;
	for(i=0;msg[i]!='\0';i++)
	{
		for(j=0;j<n;j++)
		{
			if(msg[i]==codes[j].ch)
			{
				printf("%s",codes[j].word);
				break;
			}
		}
	}
}
void decode (treenode *r, char msg[])
{
	int i =0;
	treenode *t = r;
	while(msg[i] != '\0')
	{
		if(msg[i]=='0')
			t = t->left;
		else t = t->right;
		if(t->left == NULL && t->right == NULL)
		{
			printf("%c", t->ch);
			t = r;
		}
		i++;
	}
}
void main()
{
	int choice, i, j, w[MAX];
	char ch[MAX], word[MAX], msg[MAX];
	treenode *root;
	do
	{
		printf("\n\n1. Create Huffman tree.");
		printf("\n2. Encode a Message.");
		printf("\n3. Decode a Message.");
		printf("\n4. Display huffman codes.");
		printf("\n5. Display Time Complexity.");
		printf("\n6. Exit.");
		printf("\nSelect Choice -");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1 :
			printf("\nEnter number of characters : ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
				printf("\nEnter (character:frequency)::");
				scanf(" %c%d",&ch[i],&w[i]);
			}
			root = build_huffman (ch, w, n);
			preorder(root, 0, word);
			printf("\nHuffman tree created successfully.");
			break;
			
			case 2 :
			printf("\nEnter message ::");
			scanf("%s",msg);
			encode(msg);
			break;
			
			case 3 :
			printf("\nEnter encoded message ::");
			scanf("%s", msg);
			decode(root, msg);
			break;
			
			case 4 :
			printf("\nPrefix codes -");
			for(i=0;i<n;i++)
			{
				if(codes[i].ch!='\0')
				{
					printf("\n\t%c:%s", codes[i].ch, codes[i].word);
				}
			}
			break;
			
			case 5 :
			printf("\nn=%d",cnt);
			printf("\nlogn=%d",logn);
			printf("\nTime complexity(nlogn)=o(%d)",cnt*logn);
			break;
			
			case 6 :
			exit(0);
			break;
			
			default : 
			printf("\nInvalid choice.");
		}
	}while(choice!=6);
}

/*
OUTPUT-

info16@ubuntu:~$ cd Desktop
info16@ubuntu:~/Desktop$ gcc huff.c
info16@ubuntu:~/Desktop$ ./a.out


1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -1

Enter number of characters : 8

Enter (character:frequency)::a 10

Enter (character:frequency)::b 5

Enter (character:frequency)::c 15

Enter (character:frequency)::d 20

Enter (character:frequency)::e 1

Enter (character:frequency)::f 12

Enter (character:frequency)::g 25

Enter (character:frequency)::h 21

Huffman tree created successfully.

1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -4

Prefix codes -
	d:00
	g:01
	f:100
	c:101
	e:11000
	b:11001
	a:1101
	h:111

1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -2

Enter message ::bag
11001110101

1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -3

Enter encoded message ::11001110101
bag

1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -5

n=15
logn=3
Time complexity(nlogn)=o(45)

1. Create Huffman tree.
2. Encode a Message.
3. Decode a Message.
4. Display huffman codes.
5. Display Time Complexity.
6. Exit.
Select Choice -6
info16@ubuntu:~/Desktop$ 

*/		
