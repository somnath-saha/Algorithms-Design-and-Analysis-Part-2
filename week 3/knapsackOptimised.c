/*
 ============================================================================
 Introduction to Algorithms - II | Stanford University | Tim Roughgarden
 Name        : knapsackOptimised.c
 Author      : Somnath Saha 
 Description : Knapsack Problem
 ============================================================================
*/

#include <stdio.h>
#include <unistd.h>   
#include <termios.h> 

#define NO_OF_ROWS 2000000
#define NO_OF_COLUMNS 2000
int row=NO_OF_ROWS, col=NO_OF_COLUMNS;

struct object
{
	int value;
	int wt;
}item[NO_OF_COLUMNS+1];

char getch();

void readFile()
{
	//FILE* fp=fopen("test", "r");
	FILE* fp=fopen("knapsack_big.txt", "r");
	if(!fp)
	{
		printf("Couldn't open file");
		return;
	}
	int w, v, i=0;
	fscanf(fp, "%d %d", &row, &col);
	while(!feof(fp))
	{
		if(++i>col) break;
		fscanf(fp, "%d %d", &v, &w);
		
		item[i].value=v;
		item[i].wt=w;
	}
	fclose(fp);
}

void display()
{
	int i;
	printf("\nITEMS:");
	for(i=1; i<=col; ++i)
	{
		printf("\n%d) %d %d", i, item[i].value, item[i].wt);
	}
	printf("\n");
}

inline int max(int a, int b)
{
	return (a>b?a:b);
}

int main()
{
	int a[NO_OF_ROWS+1];
	int i, j;
	readFile();
	for(j=0; j<=row; ++j)
	{
		a[j]=0;
	}
	for(i=1; i<=col; ++i)
	{
		for(j=row; j>=0; --j)
		{
			if (j-item[i].wt>=0)
				a[j]=max(a[j], (a[(j-item[i].wt)]+item[i].value));	
		}
	}
	printf("\nOptimal value=%d ", a[row]);
	return 0;
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
