/*
 ============================================================================
 Introduction to Algorithms - II | Stanford University | Tim Roughgarden
 Name        : greedy1.c
 Author      : Somnath Saha 
 Description : Bad Greedy Algo for minimizing wt'ed sum of completion times
 ============================================================================
*/

#include<stdio.h>

#define MAX 10000

void displayArray(int, int);

typedef struct job
{
	int w;
	int l;
}job;

job j[MAX], temp;

int cost_job(int i)
{
	return (j[i].w-j[i].l);
}

int main()
{
	int i=0, k=0, pos=0;
	
	FILE* f=fopen("jobs.txt", "r");
	//FILE* f=fopen("test_case2.txt", "r");
	while(!feof(f))
	{
		fscanf(f, "%d %d", &j[i].w, &j[i].l);
		i++;
		if(i==MAX) break;
	}
	//displayArray(0, MAX);
	//getchar();
	fclose(f);
	for(i=0; i<(MAX-1); ++i)
	{
		pos=i;
		for(k=i+1; k<MAX; ++k)
		{
			if(cost_job(k)>cost_job(pos))
			{
				pos=k;
			}
			else if(cost_job(k)==cost_job(pos))
			{
				if(j[k].w>j[pos].w)
				{
					pos=k;
				}
				else if((j[k].w==j[pos].w) && (j[k].l<j[pos].l))
				{
					pos=k;
				}
			}
		}
		temp=j[pos];
		j[pos]=j[i];
		j[i]=temp;
	}
	double sum=0, t=0;
	for(k=0; k<MAX; ++k)
	{
		t+=j[k].l;
		sum+=j[k].w*t;
		//printf("\nt=%lf sum=%lf", t, sum);
	}
	//displayArray(0, MAX);	
	printf("%.0lf", sum);
	return 0;
}


void displayArray(int s, int e)
{
	int i;
	for(i=s; i<e; ++i)
	{
		printf("\nw=%d l=%d", j[i].w, j[i].l);
	}
	printf("\n");
}
