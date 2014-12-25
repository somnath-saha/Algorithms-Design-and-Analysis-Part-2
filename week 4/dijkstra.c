/*
 ============================================================================
 Introduction to Algorithms - I | Stanford University | Tim Roughgarden
 Name        : dijkstra.c
 Author      : Somnath Saha 
 Description : Find shortest no. of pairs that generate a sum
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <termios.h> 
#include <limits.h> 
#include <time.h> 

char getch();
void display();
void createGraph();
void DFS(int,int);
void DFS_Loop(int);

#define NO_OF_VERTICES 200
//#define NO_OF_ENTRIES 4
 
typedef struct node
{
	int x;
	char explored;
	int d;
	struct edge *link;
}node;

typedef struct edge
{
	int x;
	int w;
	struct edge *link;
}edge;
edge* tempEdge;

node g[NO_OF_VERTICES+1];

int t=0, s=0;
int v[NO_OF_VERTICES+2];

int minimum(int x, int y)
{
	return (x<y?x:y);
}

void dijkstra()
{
	int i, k=1, min=INT_MAX, minNode=0;
	v[1]=g[1].x;
	g[1].explored=1;
	g[1].d=0;
	printf("\nEntered Dijkstra's");
	getch();
	for(i=2; i<=NO_OF_VERTICES+1; i++)
	{
		v[i]=0;
	}
	//printf("\nCheckpoint cleared");
	//getch();
	while(v[NO_OF_VERTICES]==0)
	{
		min=INT_MAX;
		for(i=1;v[i]!=0;++i)
		{
			tempEdge=g[v[i]].link;
			while(tempEdge!=NULL)
			{
				//printf("\nChecking %d", g[tempEdge->x].x);
				//getch();
				if(g[tempEdge->x].explored!=1)
				{
					g[tempEdge->x].d = minimum(g[tempEdge->x].d, g[v[i]].d+tempEdge->w);
					if(g[tempEdge->x].d<min)
					{
						min=g[tempEdge->x].d;
						minNode=tempEdge->x;
						//printf("\nmin=%d minNode=%d", min, minNode);
					}
				}
				tempEdge=tempEdge->link;
			}
		}
		//printf("\nmin=%d minNode=%d set explored.", min, minNode);
		g[minNode].explored=1;
		v[i]=minNode;
	}
}

int main()
{
	//long t0=time(NULL);
	createGraph();
	dijkstra();
	display();
	int k[]={7,37,59,82,99,115,133,165,188,197}, i=0;
	printf("\n");
	for(i=0; i<10; ++i)
	{
		printf("%d, ", g[k[i]].d);
	}
	//printf("\nTotal Time taken = %lds.", time(NULL)-t0);
	return 0;
}

void createGraph()
{
	int i=1;
	FILE* fp=fopen("dijkstraData.txt", "r");
	//FILE* fp=fopen("data", "r");

	for(i=1; i<=NO_OF_VERTICES; i++)
	{
		g[i].x=i;
		g[i].explored=0;
		g[i].d=1000000;
		g[i].link=NULL;
	}
	
	
	printf("\nAll vertices initialised.");
	fseek(fp, 0, SEEK_SET);
	i=0;
	char s[200];
	char *t;
	int k, n, w;
	
	while(!feof(fp))
	{	
		fscanf(fp, "%s" , s);
		
		//printf("\n%s", s);
		n=atoi(s);
		
		for(k=0; (s[k]!=',')&&(s[k]!='\0'); ++k);
		t=s+k;
		
		if(s[k]!='\0')
		{
			//printf("\n%d", atoi(t+1));
			w=atoi(t+1);
			tempEdge=g[i].link;
			if(tempEdge==NULL)
			{
				tempEdge=(edge *)malloc(sizeof(edge));
				tempEdge->x=n;
				tempEdge->w=w;
				//printf("\n%d %d set in edge.", n, w);
				tempEdge->link=NULL;	
				g[i].link=tempEdge;	
			}
			else
			{
				while(tempEdge->link!=NULL)
				{
					tempEdge=tempEdge->link;
				}
				tempEdge->link=(edge *)malloc(sizeof(edge));
				tempEdge->link->x=n;
				tempEdge->link->w=w;
				tempEdge->link->link=NULL;
			}
		}
		else
		{
			i++;
		}
	}
	tempEdge=g[NO_OF_VERTICES].link;
	while(tempEdge!=NULL)
	{
		if(tempEdge->link!=NULL)
		{
			if(tempEdge->link->link==NULL)
			{
				edge * t=tempEdge;
				tempEdge=tempEdge->link;
				free(tempEdge);
				t->link=NULL;
			}
		}
		tempEdge=tempEdge->link;
	}
	printf("\nVertices and Edges read from file.");
	display();
	fclose(fp);
}

void display()
{
	int i=1;
	while(i<=NO_OF_VERTICES)
	{
		printf("\n%d [explored(%d), d(%d)] -> ", g[i].x, g[i].explored, g[i].d);
		tempEdge=g[i].link;
		while(tempEdge!=NULL)
		{
			printf("(%d,%d) ", tempEdge->x, tempEdge->w);
			tempEdge=tempEdge->link;
		}
		i++;
	}	
}

char getch()
{
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }
