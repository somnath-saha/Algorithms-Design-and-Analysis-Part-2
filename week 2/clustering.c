/*
 ============================================================================
 Introduction to Algorithms - II | Stanford University | Tim Roughgarden
 Name        : clustering.c
 Author      : Somnath Saha 
 Description : Clustering Algorithm using Altered Kruskal MST
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <termios.h> 
#include <limits.h> 
#include <time.h> 

typedef struct node
{
	int x;
	int leader;
	int count;
	struct edge *link;
}node;

typedef struct edge
{
	int s, d;
	int w;
	struct edge *link;
}edge;

char getch();
void display();
void createGraph();
void QuickSort(edge* list[], int start, int end);
int split(edge* list[], int start, int end);
int cluster(int);
#define NO_OF_VERTICES 500
#define NO_OF_ENTRIES 124750

/*
#define NO_OF_VERTICES 9
#define NO_OF_ENTRIES 13
char filename[]="test";

*/
char filename[]="clustering1_sorted.txt";


int comp=0;
edge* tempEdge;
edge* list[NO_OF_ENTRIES+5];
node g[NO_OF_VERTICES+1];

int main()
{
	long t1=time(NULL);
	createGraph();
	if(NO_OF_ENTRIES<10000)
	{
	printf("\nStarting QuickSort...");
	getch();
	QuickSort(list,1,NO_OF_ENTRIES);
	display();
	getch();
	}
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
		printf("\nAll array sorted. continue for clustering...");
	getch();
	//printf("\n%d", cluster(4));
	i=cluster(4);
	printf("\ni=%d Max spacing=%d.", i, list[i]->w);
	//display();
	return 0;
}

int cluster(int k)
{
	int i=0, j=0;
	int ncluster();
	while(ncluster()>k)
	{
		i++;
		//printf("\nNo of clusters=%d for i=%d", ncluster(), i);
		//getch();
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
					//printf("\nFor j=%d g[j].leader=%d and g[list[i]->d].leader=%d g[j].count=%d", j, g[j].leader, g[list[i]->d].leader, g[j].count);
				}
				else if(g[j].leader==dleader)
				{
					g[j].leader=sleader;
					g[j].count+=scount;
					//printf("\nFor j=%d g[j].leader=%d and g[list[i]->s].leader=%d g[j].count=%d", j, g[j].leader, g[list[i]->s].leader, g[j].count);
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
					//printf("\nFor j=%d g[j].leader=%d and g[list[i]->d].leader=%d g[j].count=%d", j, g[j].leader, g[list[i]->d].leader, g[j].count);
				}
				else if(g[j].leader==g[list[i]->s].leader)
				{
					g[j].leader=g[list[i]->d].leader;
					g[j].count+=dcount;
					//printf("\nFor j=%d g[j].leader=%d and g[list[i]->s].leader=%d g[j].count=%d", j, g[j].leader, g[list[i]->s].leader, g[j].count);
				}	
				//printf("\ndone for j=%d",j);
				//getch();			
			}	
			
		}
		//printf("\ndone for i=%d",i);
		//display();
		//getch();
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
	//FILE* fp=fopen("clustering1_sorted.txt", "r");
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
	if(NO_OF_ENTRIES<10000)
	fscanf(fp, "%d" , &i);
	i=1;
	while(!feof(fp))
	{	
		if(i++>NO_OF_ENTRIES)	break;
		
		fscanf(fp, "%d %d %d" , &v1, &v2, &w);
		
		//SETUP EDGE FOR V1 TO V2
		tempEdge=(edge *)malloc(sizeof(edge));
		tempEdge->link=NULL;
		tempEdge->w=w;
		tempEdge->d=v2;
		tempEdge->s=v1;
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
		list[i-1]=tempEdge;
		//SETUP EDGE FOR V2 TO V1
		tempEdge=(edge *)malloc(sizeof(edge));
		tempEdge->link=NULL;
		tempEdge->w=w;
		tempEdge->d=v1;
		tempEdge->s=v2;
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
	//display();
	//getch();
	fclose(fp);
}

int split(edge* list[], int start, int end)
{
	edge* temp;
	int p, q;
	p=start+1;
	q=end;
	temp=list[p];
	//printf("\nSplitting with start=%d end=%d.", start, end); 
	while(p<q)
	{
		while( list[p]->w <= list[start]->w)
		{
				p++;
				if(p==NO_OF_VERTICES+1) 
				{
					break;
				}
		}
		while(list[q]->w  >  list[start]->w)
		{
				q--;
				if(q==-1) 
				{
					q=0;
					break;
				}
		}
		if (p<q)
		{
			temp=list[p];
			list[p]=list[q];
			list[q]=temp;
			//if(p>5000000){
			//printf("\np=%d(w=%d) & q=%d(w=%d) exchanged.", p, list[p]->w, q, list[q]->w); 
			//getch();
			//getch();}
		}
	}
	if(list[q]->w  <  list[start]->w)
	{
		temp=list[start];
		list[start]=list[q];
		list[q]=temp;
	}
	return q;
}
int count=0, u=0;
void QuickSort(edge* list[], int start, int end)
{
	if(start<end)
	{
		int i;
		i=split(list, start, end);
		count++;
		if(count>114738){
			u++;
		printf("\n%d(%d) setup. s=%d e=%d", i, u, start, end); 
	}
		//display();
		
		//}
		//printf("\nCalling for start=%d end=%d", start, i-1); 
		//getch();
		QuickSort(list, start, i-1);
		//printf("\nCalling for start=%d end=%d", i+1, end); 
		//getch();
		QuickSort(list, i+1, end);
	}
	//printf("\nDone for start=%d and end=%d", i, u, start, end);
	//getch();
}

void display()
{
	int i=1;
	//while(i<=1)
	while(i<=NO_OF_VERTICES)
	{
		printf("\n%d -> leader=%d count=%d", g[i].x, g[i].leader, g[i].count);
		tempEdge=g[i].link;
		i++;
	}
	i=1;
	//printf("\n");
	//getch();
	//while(i<=100)

	//FILE* fp=fopen("clustering1_sorted.txt", "w");


	while(i<=NO_OF_ENTRIES)
	{
		printf("\n%d) %d (%d->%d), ", i, list[i]->w, list[i]->s, list[i]->d);
		//fprintf(fp, "%d %d %d\n", list[i]->s, list[i]->d, list[i]->w);
		//if(i%500==0) getch();
		i++;
	}
	//printf("\nWritten to file");
	//getch();
	//fclose(fp);
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
 
 /*
 void quicksort(int[], int, int); // prototype

void quicksort(int a[], int l, int r) 
{
    int i, j, v, t;
    if(r > l)
    {
        v = a[r];
        i = l - 1;
        j = r;

        for(;;)
       {
            while (a[++i] < v); 
            while (a[--j] > v);

            if(i >= j) break;
            t = a[i]; a[i] = a[j]; a[j] = t;

        } // End for here


    t = a[i]; a[i] = a[r]; a[r] = t;

    quicksort(a, l, i - 1);
    quicksort(a, i + 1, r);

    }
   */
 
