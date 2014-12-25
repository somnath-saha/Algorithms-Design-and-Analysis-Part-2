/*
 ============================================================================
 Introduction to Algorithms - II | Stanford University | Tim Roughgarden
 Name        : clustering_final.c
 Author      : Somnath Saha 
 Description : Clustering Algorithm using Altered Kruskal MST
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <termios.h> 

typedef struct node
{
	int x;
	int leader;
	int count;
}node;

typedef struct edge
{
	int s, d;
	int w;
}edge;

char getch();
void display();
void createGraph();
int cluster(int);

#define NO_OF_VERTICES 500
#define NO_OF_ENTRIES 124750

char filename[]="clustering1_sorted.txt";

int comp=0;
edge* tempEdge;
edge* list[NO_OF_ENTRIES+5];
node g[NO_OF_VERTICES+1];

int main()
{
	//CREATE GRAPH FROM A SORTED EDGE LIST FILE
	createGraph();
	
	int i=0, flg=0;
	for(i=1;i<NO_OF_ENTRIES;++i)
	{
		if(list[i]->w>list[i+1]->w)
		{
			printf("\n%d) %d %d %d\n", i, list[i]->s, list[i]->d, list[i]->w);
			flg++;
		}
	}
	if(flg==0)
	{
		printf("\nArray is sorted. Now to apply clustering...");
		getch();
	}
	else
		return -1;
	i=cluster(4);
	printf("\nMaximum spacing=%d. (At edge no.=%d)",  list[i]->w, i);
	return 0;
}

int cluster(int k)
{
	int i=0, j=0;
	int ncluster();
	while(ncluster()>k)
	{
		i++;
		int scount=g[list[i]->s].count, dcount=g[list[i]->d].count;
		int sleader=g[list[i]->s].leader, dleader=g[list[i]->d].leader;
		if(sleader==dleader) continue;
		if(g[list[i]->s].count>g[list[i]->d].count)
		{
			for(j=1;j<=NO_OF_VERTICES;++j)
			{
				if(g[j].leader==sleader)
				{
					g[j].count+=dcount;
				}
				else if(g[j].leader==dleader)
				{
					g[j].leader=sleader;
					g[j].count+=scount;
				}
			}	
		}
		else
		{
			for(j=1;j<=NO_OF_VERTICES;++j)
			{
				if(g[j].leader==g[list[i]->d].leader)
				{
					g[j].count+=scount;
				}
				else if(g[j].leader==g[list[i]->s].leader)
				{
					g[j].leader=g[list[i]->d].leader;
					g[j].count+=dcount;
				}			
			}				
		}
	}	
	while(g[list[i]->s].leader==g[list[i]->d].leader) i++;
	return i;	
}

int ncluster()
{
	int i=1, a[NO_OF_VERTICES+1], count=0;
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		a[i]=0;
	}
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		a[g[i].leader]=1;
	}
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		if(a[i]==1) 
			count++;
	}
	return count;
}

void createGraph()
{
	int i=1, v1, v2, w;
	FILE* fp=fopen(filename, "r");
	if(fp==NULL) 
	{
		printf("\nFile couldn't be opened.");
		getch();
		return;		
	}
	for(i=1; i<=NO_OF_VERTICES; ++i)
	{
		g[i].x=i;
		g[i].leader=i;
		g[i].count=1;
	}
	printf("\nAll vertices initialised.");
	i=1;
	while(!feof(fp))
	{	
		if(i++>NO_OF_ENTRIES)	break;
		fscanf(fp, "%d %d %d" , &v1, &v2, &w);
		tempEdge=(edge *)malloc(sizeof(edge));
		tempEdge->w=w;
		tempEdge->d=v2;
		tempEdge->s=v1;
		list[i-1]=tempEdge;
	}
	printf("\nVertices and Edges read from file.");
	fclose(fp);
}

void display()
{
	int i=1;
	while(i<=NO_OF_VERTICES)
	{
		printf("\n%d -> leader=%d count=%d", g[i].x, g[i].leader, g[i].count);
		i++;
	}
	i=1;
	while(i<=NO_OF_ENTRIES)
	{
		printf("\n%d) %d (%d->%d), ", i, list[i]->w, list[i]->s, list[i]->d);
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
 
