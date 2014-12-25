/*
 ============================================================================
 Introduction to Algorithms - II | Stanford University | Tim Roughgarden
 Name        : prim.c
 Author      : Somnath Saha 
 Description : Prim's Minimum Spanning Tree (Finding the net minimum cost)
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

#define NO_OF_VERTICES 500
#define NO_OF_ENTRIES 2184
 
typedef struct node
{
	int x;
	char explored;
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

int main()
{
	createGraph();
	//display();
	void prim();
	prim();
	//display();
	return 0;
}

void prim()
{
	int i, min=INT_MAX, minNode=0, v[NO_OF_VERTICES+2];
	float sum=0;
	v[1]=g[1].x;
	g[1].explored=1;
	//printf("\nEntered Prim's");
	//getch();
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
					if(tempEdge->w<min)
					{
						min=tempEdge->w;
						minNode=tempEdge->x;
						//printf("\nmin=%d minNode=%d", min, minNode);
					}
				}
				tempEdge=tempEdge->link;
			}
		}
		//printf("\nmin=%d minNode=%d set explored.", min, minNode);
		g[minNode].explored=1;
		sum+=min;
		v[i]=minNode;
	}
	printf("\nMIN SUM=%.0lf.", sum);
}

void createGraph()
{
	int i=1, v1, v2, w;
	FILE* fp=fopen("edges.txt", "r");
	
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		g[i].x=i;
		g[i].explored=0;
	}
	printf("\nAll vertices initialised.");
	i=1;
	while(!feof(fp))
	{	
		if(i++>NO_OF_ENTRIES)	break;
		
		fscanf(fp, "%d %d %d" , &v1, &v2, &w);
		
		//SETUP EDGE FOR V1 TO V2
		tempEdge=(edge *)malloc(sizeof(edge));
		tempEdge->link=NULL;
		tempEdge->w=w;
		tempEdge->x=v2;
		if(g[v1].link==NULL)
		{
			g[v1].link=tempEdge;			
		}
		else
		{
			edge *temp=g[v1].link;
			while(temp->link!=NULL)
			{
				temp=temp->link;
			}
			temp->link=tempEdge;
		}
		//SETUP EDGE FOR V2 TO V1
		tempEdge=(edge *)malloc(sizeof(edge));
		tempEdge->link=NULL;
		tempEdge->w=w;
		tempEdge->x=v1;
		if(g[v2].link==NULL)
		{
			g[v2].link=tempEdge;			
		}
		else
		{
			edge *temp=g[v2].link;
			while(temp->link!=NULL)
			{
				temp=temp->link;
			}
			temp->link=tempEdge;
		}	
	}
	
	printf("\nVertices and Edges read from file.");
	fclose(fp);
}

void display()
{
	int i=1;
	while(i<=NO_OF_VERTICES)
	{
		printf("\n%d [explored(%d)] -> ", g[i].x, g[i].explored);
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
