#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"

void Encode(int *message,int *c,int **G,int n,int m)
{
	int i,j;
	//產生message
	for(i=0;i<n-m;i++)
	{		
		message[i] = rand()%2;
	}	
	//產生codeword c=m*G
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-m;j++)
			c[i] += message[j]*G[j][i];
		c[i] = c[i] % 2;
	}
	//errno_t err_fopen3;
	//FILE* fid5;
	//err_fopen3 = fopen_s(&fid5, "c.dat", "a+");
	//for (i = 0; i < n; i++) //check h矩陣 by willy
	//{
	//	fprintf(fid5, "%d ", c[i]);
	//}
	//fprintf(fid5, "\n");
	//fclose(fid5);
	//for (i = 0; i < n; i++) //check codeword by willy
	//{
	//		printf("%d ", c[i]);
	//}
	//printf("\n");
}