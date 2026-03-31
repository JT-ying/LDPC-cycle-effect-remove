#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "Configuration.h"

//#define total_col 12000
//#define total_row 4000

int Preprocess(int maxcoldegree, int* maxdegree, int** G_temp, int** H_original, int* return_real_row_num,char filename[99])
{
	//大致上是學長傳承下來的架構
	//註解掉的部分主要是針對非fullrank矩陣的操作
	//然而若是非fullrank經過這些操作，會將全0列刪除掉
	//與H大小不一致，codeword也會變少，且m個row也會被修正成刪除後的，導致無法脫離while (j != m)迴圈
	//目前對非fullrank的操作是，只做高斯消去(含列與行交換)
	//即使有全零列也不進行刪除，該方法目前可行且未有bug

	int n, m, u, yes;
	FILE* fid;
	fid = fopen(filename, "r");
	//第一個參數代表此 H matrix 有 n 個 column
	fscanf(fid, "%d", &n);
	//第二個參數代表此 H matrix 有 m 個 row
	fscanf(fid, "%d", &m);
	//第三個參數代表此 H 最大的 coldegree
	fscanf(fid, "%d", &maxcoldegree);
	int i, j, k, l;
	int original_m = m;
	int element;
	int* temp;
	int* temp1;
	//int temp_value;
	temp = new int[n];
	temp1 = new int[m];
	int** H;
	H = new int* [m];
	for (i = 0; i < m; i++)
		H[i] = new int[n];

	for (j = 0; j < m; j++)
		for (i = 0; i < n; i++)
			H[j][i] = 0;
	//memset(h[j], 0, n); //rewritten by cmlee

	//還原H矩陣
	for (i = 0; i < n; i++)
	{
		for (k = 0; k < maxcoldegree; k++)
		{
			fscanf(fid, "%d", &element);
			H[element - 1][i] = 1;
		}
	}
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "H.dat", "w");
	//for (i = 0; i < m; i++) //check H矩陣 by willy
	//{
	//	fprintf(fid3,"\n");
	//	for (j = 0; j < n; j++)
	//	{
	//		fprintf(fid3,"%d", H[i][j]);
	//	}
	//}
	//fprintf(fid3,"\n");
	//fclose(fid3);
	//複製到H_original矩陣	
	for (j = 0; j < m; j++)		//rewrite by cmlee
		for (i = 0; i < n; i++)
			H_original[j][i] = H[j][i];
	// memcpy_s(H_original, m*n * sizeof(int), H, m*n*sizeof(int));
	int* rearrange_order;
	rearrange_order = new int[n];
	// for (i = 0; i < n; i++) rewritten by cmlee
	//	rearrange_order[i] = 0;
	memset(rearrange_order, 0, n);

	//一次完成一整列
	j = 0;
	int rref_number = 0;
	yes = 0;
	int one_counter = 0;
	int allzero_column_num = 0;
	int counter1 = 0;
	int** H_temp;

	H_temp = new int* [original_m];
	for (i = 0; i < original_m; i++)
		H_temp[i] = new int[n];
	//parity check matrix to generator matrix with gaussian elimation
	while (j != m)
	{
		//errno_t err_fopen1;
		//FILE* fid3;
		//err_fopen1 = fopen_s(&fid3, "H5(96,48).dat", "a+");
		//fprintf(fid3, "j = %d", j);
		//for (int i2 = 0; i2 < m; i2++) //check h矩陣 by willy
		//{
		//	fprintf(fid3, "\n");
		//	for (int j2 = 0; j2 < n; j2++)
		//	{
		//		fprintf(fid3, "%d ", H[i2][j2]);
		//	}
		//}
		//fprintf(fid3, "\n");
		//fclose(fid3);
		//判斷對角線上元素是否為0,如果不是0的話就對調
		if (H[j][j] == 0)
		{
			yes = 0;
			//先把整列放到temp
			//for (i = 0; i < n; i++)  rewrite by cmlee
			//	temp[i] = H[j][i];
			memcpy(temp, H[j], n * sizeof(int));
			//往下尋找1的位置
			for (i = j; i < m; i++)
			{
				if (H[i][j] != 0)
				{
					yes = 1;
					for (k = 0; k < n; k++) //從該"列"向下找到1後，將該"行"交換至符合對角線=1的位置
						H[j][k] = H[i][k];  //例如i=8,j=3,(8,3)找到1，則將第8行與第3行對調
					for (k = 0; k < n; k++) //則在(3,3)會=1
						H[i][k] = temp[k];
					break;
				}

			}
			//if (yes == 1)  // add by cmlee
			//continue;
		}

		if (H[j][j] == 1)
		{
			for (i = 0; i < m; i++)
			{
				if (H[i][j] != 0 && i != j)
				{
					for (k = 0; k < n; k++)
						H[i][k] = (H[j][k] + H[i][k]) % 2;
				}
			}
			yes = 1;
		}
		//觀察

		//printf("%d ",H[j][j]);

		//rref_number += 1;
		if (yes == 1)
			j += 1;
		//else
		//	system("pause");
		//if(yes != 1)
		//	j -= 1;
		//errno_t err_fopen1;
		//FILE* fid3;
		//err_fopen1 = fopen_s(&fid3, "H.dat", "a+");
		//fprintf(fid3, "j = %d", j);
		//for (int i2 = 0; i2 < m; i2++) //check h矩陣 by willy
		//{
		//	fprintf(fid3, "\n");
		//	for (int j2 = 0; j2 < n; j2++)
		//	{
		//		fprintf(fid3, "%d ", H[i2][j2]);
		//	}
		//}
		//fprintf(fid3, "\n");
		//fclose(fid3);
		/////////////////////////////檢查以下的row是不是全部都是0////////////////////////////
		allzero_column_num = 0;
		int rate_change = 0;//0表示rate沒有改變
		one_counter = 0;
		for (k = j; k < m; k++)
		{
			for (i = 0; i < n; i++)		
				if (H[k][i] == 1)
					one_counter++;
		}
		if (one_counter == 0)		//H[j~m][0~n]皆==0
		{
			allzero_column_num = m - j;
			rate_change = 1;
			//printf("j=%d\n", j);//列出行交換的位置
			//errno_t err_fopen1;
			//FILE* fid3;
			//err_fopen1 = fopen_s(&fid3, "H.dat", "a+");
			//fprintf(fid3,"j = %d", j);
			//for (int i2 = 0; i2 < m; i2++) //check H矩陣 by willy
			//{
			//	fprintf(fid3, "\n");
			//	for (int j2 = 0; j2 < n; j2++)
			//	{
			//		fprintf(fid3, "%d ", H[i2][j2]);
			//	}
			//}
			//fprintf(fid3, "\n");
			//fclose(fid3);

			/*
			H_temp = new int *[(m-allzero_column_num)];
			for(i=0;i<m-allzero_column_num;i++)
				H_temp[i] = new int [n];
			*/
			//for (k = 0; k < m - allzero_column_num; k++)
			//{
			//	for (i = 0; i < n; i++)
			//		H_temp[k][i] = H[k][i];
			//	delete[] H[k];      // added by cmlee
			//}
			//delete[] H;

			//H = new int* [(m - allzero_column_num)];
			//for (i = 0; i < m - allzero_column_num; i++)
			//	H[i] = new int[n];

			//for (k = 0; k < m - allzero_column_num; k++)
			//	//				for (i = 0; i < n; i++)
			//	//					H[k][i] = H_temp[k][i];
			//	memcpy_s(H[k], n * sizeof(int), H_temp[k], n * sizeof(int));
			//delete (H_temp);
			m = m - allzero_column_num;
		}//(one_counter == 0)

		//往下檢查是不是都沒有1，如果都沒有1就往同一個row的column去找，注意要從大於m之後的column開始///////
		//而且H_original也要跟著變
		int change;
		int* temprow;
		temprow = new int[n];
		int* temp3;
		temp3 = new int[m];

		int* temp_original;
		temp_original = new int[original_m];
		int counter3 = 0;
		if (j != m)
		{
			change = 0;
			int counter2 = 0;

			//{
			counter1 = 0;
			counter2 = 0;
			for (i = j; i < m; i++) 
				if (H[i][j] == 0)
					counter1++;

			if (counter1 == m - j)		//H[j~m][j] == 0
			{
				printf("counter1 j = %d\n", j);
				for (k = 0; k < n; k++)
					if (H[j][k] == 0)
						counter3++;
			}
			if (counter3 == n)			//H[j][0~n] == 0
			{
				printf("counter3 j = %d\n", j);
				for (k = 0; k < n; k++)
				{
					temprow[k] = H[j][k];
					H[j][k] = H[m - 1][k];
					H[m - 1][k] = temprow[k];
				}
			}
			if (counter1 == m - j)		//H[j~m][j] == 0
			{

				for (k = m; k < n; k++)
					if (H[j][k] == 1 && change == 0)
					{
						change = 1;
						for (u = 0; u < m; u++)
						{
							temp3[u] = H[u][k];
							H[u][k] = H[u][j];
							H[u][j] = temp3[u];
						}

						for (u = 0; u < original_m; u++)
						{
							temp_original[u] = H_original[u][k];
							H_original[u][k] = H_original[u][j];
							H_original[u][j] = temp_original[u];
						}
					}
			}//if (counter1 == m-j)

		}//if (j != m)
		//}//if(rate_change ==0)
	//printf("%d ",H[j-1][j-1]);
		delete [] temprow;
		delete [] temp3;
	}//while(j != m)
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "H.dat", "w");
	//for (i = 0; i < original_m; i++) //check H矩陣 by willy
	//{
	//	fprintf(fid3, "\n");
	//	for (j = 0; j < n; j++)
	//	{
	//		fprintf(fid3, "%d ", H_original[i][j]);
	//	}
	//}
	//fprintf(fid3, "\n");
	//fclose(fid3);
	/////////////////////////////////將縮小的H矩陣還原/////////////////////////////////
	/*
	int **H_temp2;
	H_temp2 = new int *[original_m];
	for(i=0;i<original_m;i++)
		H_temp2[i] = new int [n];
	*/
	//for (k = 0; k < original_m; k++)
	//	for (i = 0; i < n; i++)
	//		H_temp[k][i] = 0;

	//for (k = 0; k < m; k++)
	//	for (i = 0; i < n; i++)
	//		H_temp[k][i] = H[k][i];
	//delete H;
	//H = new int* [original_m];
	//for (i = 0; i < original_m; i++)
	//	H[i] = new int[n];

	//for (k = 0; k < original_m; k++)
	//	for (i = 0; i < n; i++)
	//		H[k][i] = H_temp[k][i];
	//delete (H_temp2);
	//printf("%d",H[92][92]);
	//////////////////////////////////////////////////////////////////////////////////	
	int diagnal = 0;
	//int zero_counter;
	int* temp2;
	temp2 = new int[m];

	int non_full_count = 0; // Added for counting the zero column by cmlee

	//while (diagnal != m)
	//{
	//	non_full_count = 0;
	//	yes = 1;
	//	while (H[diagnal][diagnal] == 0)
	//	{
	//		non_full_count++;
	//		//先把整行放到temp1,把H_original放到temp

	//		for (k = 0; k < m; k++)
	//		{
	//			temp1[k] = H[k][diagnal];
	//			temp[k] = H_original[k][diagnal];
	//		}

	//		for (l = 0; l < n - (diagnal + 1); l++)
	//		{
	//			//將整行都搬到最後面
	//			for (k = 0; k < m; k++)
	//			{
	//				H[k][diagnal + l] = H[k][diagnal + l + 1];
	//				H_original[k][diagnal + l] = H_original[k][diagnal + l + 1];
	//			}
	//		}

	//		for (k = 0; k < m; k++)
	//		{
	//			H[k][n - 1] = temp1[k];
	//			H_original[k][n - 1] = temp[k];
	//		}
	//		if (non_full_count == (n - diagnal))
	//			break;

	//		//}//if (yes==1)

	//	}//while(H[diagnal][diagnal] == 0)
	//	if (non_full_count == (n - diagnal))
	//		break;
	//	diagnal += 1;
	//}
	*return_real_row_num = m;
	/*
	for (k=0;k<m;k++)
		printf("%d ",H[k][diagnal-1]);
	*/
	/*
	int **H_temp2;
	H_temp2 = new int *[original_m];
	for(i=0;i<original_m;i++)
		H_temp2[i] = new int [n];
	*/
	/*
	for (k=0;k<original_m;k++)
		for (i=0;i<n;i++)
			H_temp[k][i] = 0;

	for (k=0;k<m;k++)
		for (i=0;i<n;i++)
			H_temp[k][i] = H[k][i];
	delete H;
	H = new int *[original_m];
	for(i=0;i<original_m;i++)
		H[i] = new int [n];

	for (k=0;k<original_m;k++)
		for (i=0;i<n;i++)
			H[k][i] = H_temp[k][i];
	*/
	//delete H_temp;
	//delete H_temp2;



	//m = real_row;

	//H的後面部分放到G的前面
	//int H1[3][6] ={{1,0,0,1,1,0},{0,1,0,1,1,1},{0,0,1,1,0,1}};
	//int G_temp1[3][6] ={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};;
	//m=3;n=6;
	for (i = original_m; i < n; i++)
		for (j = 0; j < original_m; j++)
			G_temp[i - original_m][j] = H[j][i];//轉置

	for (i = original_m; i < n; i++)
		G_temp[i - original_m][i] = 1;

	//errno_t err_fopen2;
	//FILE* fid4;
	//err_fopen2 = fopen_s(&fid4, "G.dat", "a+");
	//fprintf(fid4, "original_m = %d", original_m);
	//for (j = 0; j < original_m; j++) //check h矩陣 by willy
	//{
	//	fprintf(fid4, "\n");
	//	for (i = 0; i < n; i++)
	//	{
	//		fprintf(fid4, "%d ", G_temp[j][i]);
	//	}
	//}
	//fprintf(fid4, "\n");
	//fclose(fid4);


	delete [] H;
	delete [] H_temp;
	delete [] temp;
	delete [] temp1;

	/*
	printf("\n\n\G matrix  is\n");
	for (i=0;i<m;i++)
	{
		 printf("\n");
		 for (j=0;j<n;j++)
		 printf("%d ",G_temp[i][j]);
	}
	*/
	//檢查是否G*H^T = 0

	int sum = 0;
	//int checkmatrix[3][3];

	int** checkmatrix;
	checkmatrix = new int* [n - m];
	for (k = 0; k < (n - m); k++)
		checkmatrix[k] = new int[original_m];

	for (k = 0; k < (n - m); k++)
		for (j = 0; j < original_m; j++)
			checkmatrix[k][j] = 0;

	for (k = 0; k < n - original_m; k++)
		for (j = 0; j < original_m; j++)
		{
			sum = 0;
			for (i = 0; i < n; i++)
			{

				sum = G_temp[k][i] * H_original[j][i];
				checkmatrix[k][j] = (sum + checkmatrix[k][j]) % 2;
			}
			//			if (checkmatrix[k][j] != 0)
			//				system("pause");
		}
	/*
	for(i=0;i<m;i++)
	{
		printf("\n");
		for(j=0;j<original_m;j++)
			printf("%d ",checkmatrix[i][j]);
	}
	*/
	//尋找maximum degree
	*maxdegree = 0;
	for (j = 0; j < m; j++)
	{
		l = 0;
		for (k = 0; k < n; k++)
		{
			if (H_original[j][k] == 1)
				l += 1;
		}
		if (l > *maxdegree)
			*maxdegree = l;
	}
	return *maxdegree;
	//delete (H);
	delete [] rearrange_order;
	//delete (H_temp);
	//delete (temprow);
	//delete (temp3);
	//delete (temp_original);
	delete [] temp2;
	//delete (H_temp2);
	delete [] checkmatrix;
	//delete ();
	//printf("maxdegree is %d\n",maxdegree);
	//尋找maximum column degree
	//maxcoldegree=0;
	//for (j = 0; j < n; j++)
	//{
	//	l = 0;
	//	for (k = 0; k < m; k++)
	//	{
	//		if (H_original[k][j] == 1)
	//			l += 1;
	//	}
	//	if (l > *maxcoldegree)
	//		*maxcoldegree = l;
	//}
	////printf("maximum column degree is %d\n",maxcoldegree);
	//return *maxcoldegree;
}
void RCmatrix(int maxcoldegree, int** R, int** C, int n, int m, int** H_original)
{
	//****************************R&C*****************************	
	int i, j, k, l;
	for (j = 0; j < m; j++)
	{
		l = 0;
		for (k = 0; k < n; k++)
		{
			if (H_original[j][k] == 1)
			{
				R[j][l] = k + 1;
				l += 1;

				for (i = 0; i < (int)maxcoldegree; i++)
				{
					if (R[j][l - 1] != 0)
					{
						if (C[R[j][l - 1] - 1][i] == 0)
						{
							C[R[j][l - 1] - 1][i] = j + 1;	//創出檔案C
							break;
						}
					}
				}
			}

		}
	}
}