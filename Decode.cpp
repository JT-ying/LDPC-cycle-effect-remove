#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"

// 4-cycle ?±È?ÈªëÂ???(?ÉË? >= 2 Ê¨°Á? Variable Nodes)
static const int HOTSPOT_NODES[] = {
	28, 56, 57, 81, 127, 132, 141,
	149, 155, 158, 173, 183, 188
};
static const int HOTSPOT_COUNT = 13;

static bool is_hotspot(int v_node_index)
{
	for (int i = 0; i < HOTSPOT_COUNT; i++)
	{
		if (HOTSPOT_NODES[i] == v_node_index)
		{
			return true;
		}
	}
	return false;
}

double SumproductAlgorithm(double* Pi, double** qij0, double** qij1, int m, int** R, int** C, double** rji0, double** rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row)
{
	int i, j, l, q;
	double K;
	double Qi0 = 0;
	double Qi1 = 0;
	double product_qij0;
	double product_qij1;

	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double product_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;

	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	for (i = 0; i < n; i++)
		r_column[i] = 0;
	for (i = 0; i < m; i++)
		q_column[i] = 0;
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "SPA_Qi.dat", "a+");
	for (j = 0; j < m; j++)
	{
		for (l = 0; l < maxdegree; l++)
		{
			counter = 0;
			for (q = 0; q < maxdegree; q++)
				if (avoid_two_cycle_usage == 0)//?ÑÂ? 2-cycle by willy
				{
					temp_row[counter] = qij1[j][q];
					//printf("%f ", temp_row[counter]);
					counter++;
				}
				else
					if (q != l)
					{
						temp_row[counter] = qij1[j][q];
						//printf("%f ", temp_row[counter]);
						counter++;
					}


			if (avoid_two_cycle_usage == 0)
				sumproduct1(temp_row, &rji, maxdegree);
			else if (avoid_two_cycle_usage == 1)
				sumproduct2(temp_row, &rji, maxdegree);

			product_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)	

				//store
			//printf("rji:%f \n", product_rji);
			rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = 0.5 + 0.5 * product_rji;
			rji1[R[j][l] - 1][r_column[R[j][l] - 1]] = 0.5 - 0.5 * product_rji;
			//fprintf(fid3, "(0)r%d %d: %f\n", j, R[j][l] - 1, 0.5 + 0.5 * product_rji);
			//fprintf(fid3, "(1)r%d %d: %f\n", j, R[j][l] - 1, 0.5 - 0.5 * product_rji);
			//printf("rji0:%f rji1:%f\n", 0.5 + 0.5 * product_rji, 0.5 - 0.5 * product_rji);

			r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
			//}//if(qij1[j][l] != 0)
		}//for(l=0;l<maxdegree;l++)
	}// for(j=0;j<m;j++)
	//computation of {LLR_qij} 
	for (j = 0; j < n; j++)
	{
		for (l = 0; l < maxcoldegree; l++)
		{
			if (C[j][l] != 0)
			{
				product_qij0 = 1;
				product_qij1 = 1;
				for (i = 0; i < maxcoldegree; i++)
				{
					if (i != l)
					{
						product_qij0 = product_qij0 * rji0[j][i];//rji0 ??check-to-variable messages
						product_qij1 = product_qij1 * rji1[j][i];
					}
				}
				if (avoid_two_cycle_usage == 0)
				{
					product_qij0 = product_qij0 * rji0[j][l];
					product_qij1 = product_qij1 * rji1[j][l];
				}
				Qi0 = product_qij0 * rji0[j][l];
				Qi1 = product_qij1 * rji1[j][l];

				product_qij0 = product_qij0 * (1 - Pi[j]);
				product_qij1 = product_qij1 * Pi[j];

				if (product_qij0 == 0)
					product_qij0 = 0.0000000001;
				if (product_qij1 == 0)
					product_qij1 = 0.0000000001;

				K = product_qij0 + product_qij1;

				product_qij0 = product_qij0 / K;
				product_qij1 = product_qij1 / K;

				//fprintf(fid3, "(0)q%d %d: %f\n", j, C[j][l] - 1, product_qij0);
				//fprintf(fid3, "(1)q%d %d: %f\n", j, C[j][l] - 1, product_qij1);
				//store
				qij0[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij0;
				qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij1;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}
		//store
		Qi0 = Qi0 * (1 - Pi[j]);
		Qi1 = Qi1 * Pi[j];

		if (Qi0 == 0)
			Qi0 = 0.0000000001;
		if (Qi1 == 0)
			Qi1 = 0.0000000001;

		K = Qi0 + Qi1;
		Qi0 = Qi0 / K;
		Qi1 = Qi1 / K;

		Q1[j] = Qi1;


		//?§Êñ∑ codeword
		if (Q1[j] > 0.5)
			c_[j] = 1;
		else c_[j] = 0;
	}
	//fclose(fid3);
	//delete (temp_row);

	return 0;
}

double SumproductAlgorithm2(double* Pi, double** qij0, double** qij1, int m, int** R, int** C, double** rji0, double** rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row)
{
	int i, j, l, q;
	double K;
	double Qi0 = 0;
	double Qi1 = 0;
	double product_qij0;
	double product_qij1;

	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double product_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;

	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	for (i = 0; i < n; i++)
		r_column[i] = 0;
	for (i = 0; i < m; i++)
		q_column[i] = 0;
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "SPA_Qi.dat", "a+");
	for (j = 0; j < m; j++)	  //?êÂÄ?check node
	{
		for (l = 0; l < maxdegree; l++)		 //?êÂÄãË???row degree ?ßÁ???
		{
			counter = 0;
			for (q = 0; q < maxdegree; q++)
				if (avoid_two_cycle_usage == 0)	  //?ÑÂ? 2-cycle by willyÔºå‰??ôÂ??¨Á? cycle-2 Ë®àÁ??πÂ?
				{
					temp_row[counter] = qij1[j][q];
					//printf("%f ", temp_row[counter]);
					counter++;
				}
				else
					if (q != l)	   //?íÈô§ cycle-2 Â∞çÊ???
					{
						temp_row[counter] = qij1[j][q];
						//printf("%f ", temp_row[counter]);
						counter++;
					}


			if (avoid_two_cycle_usage == 0)
				sumproduct1(temp_row, &rji, maxdegree);		// rji = rji * (1 - 2 * temp_row[maxdegree]);
			else if (avoid_two_cycle_usage == 1)
				sumproduct2(temp_row, &rji, maxdegree);

			product_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)

				//store
			//printf("rji:%f \n", product_rji);
			rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = 0.5 + 0.5 * product_rji;
			rji1[R[j][l] - 1][r_column[R[j][l] - 1]] = 0.5 - 0.5 * product_rji;
			//fprintf(fid3, "(0)r%d %d: %f\n", j, R[j][l] - 1, 0.5 + 0.5 * product_rji);
			//fprintf(fid3, "(1)r%d %d: %f\n", j, R[j][l] - 1, 0.5 - 0.5 * product_rji);
			//printf("rji0:%f rji1:%f\n", 0.5 + 0.5 * product_rji, 0.5 - 0.5 * product_rji);

			r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
			//}//if(qij1[j][l] != 0)
		}//for(l=0;l<maxdegree;l++)
	}// for(j=0;j<m;j++)
	//computation of {LLR_qij} 
	for (j = 0; j < n; j++)	  //?êÂÄ?variable node
	{
		for (l = 0; l < maxcoldegree; l++)	 //?êÂÄãË???column degree ?ßÁ???
		{
			if (C[j][l] != 0)	   //?âÈÄ???ÇÊ??¥Êñ∞
			{
				product_qij0 = 1;
				product_qij1 = 1;
				for (i = 0; i < maxcoldegree; i++)
				{
					if (i != l)	   //?íÈô§ cycle-2 Â∞çÊ???
					{
						product_qij0 = product_qij0 * rji0[j][i];	  //rji0 ??check-to-variable messages
						product_qij1 = product_qij1 * rji1[j][i];
					}
				}
				if (avoid_two_cycle_usage == 0)	  //?ÑÂ? cycle-2 ?ÇÔ??ôË£°‰πü‰??ôÂ??âÁ? cycle-2 ??
				{
					product_qij0 = product_qij0 * rji0[j][l];
					product_qij1 = product_qij1 * rji1[j][l];
				}

				product_qij0 = product_qij0 * (1 - Pi[j]);
				product_qij1 = product_qij1 * Pi[j];

				if (product_qij0 == 0)
					product_qij0 = 0.0000000001;
				if (product_qij1 == 0)
					product_qij1 = 0.0000000001;

				K = product_qij0 + product_qij1;	   //Ê≠???ñÔ?ËÆ?0 ??1 ?ÑÊ??áÁ∏Ω?åÁÇ∫ 1

				product_qij0 = product_qij0 / K;
				product_qij1 = product_qij1 / K;

				//fprintf(fid3, "(0)q%d %d: %f\n", j, C[j][l] - 1, product_qij0);
				//fprintf(fid3, "(1)q%d %d: %f\n", j, C[j][l] - 1, product_qij1);
				//store
				qij0[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij0;   //?≤Â? q Ë®äÊÅØ
				qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij1;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}

		//fclose(fid3);
		//delete (temp_row);
	}
	return 0;
}

double SumproductAlgorithm_cycle(double* Pi, double** qij0, double** qij1, double** temp_qij0, double** temp_qij1, int m, int** R, int** C, double** rji0, double** rji1, double** temp_rji0, double** temp_rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row)
{
	int i, j, l, q;
	double K;
	double Qi0 = 0;
	double Qi1 = 0;
	double product_qij0;
	double product_qij1;

	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double product_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;

	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	int Qnumber;
	int cyclenumber;

	for (Qnumber = 0; Qnumber < n; Qnumber++)
	{
		for (i = 0; i < n; i++)
			r_column[i] = 0;
		for (i = 0; i < m; i++)
			q_column[i] = 0;
		for (j = 0; j < m; j++)
		{
			for (l = 0; l < maxdegree; l++)
			{
				counter = 0;
				for (q = 0; q < maxdegree; q++)
				{
					temp_row[counter] = qij1[j][q];
					counter++;
				}
				//printf("\n");
				//errno_t err_fopen1;
				//FILE* fid3;
				//err_fopen1 = fopen_s(&fid3, "rji.dat", "a+");
				//fprintf(fid3, "%d %d\n", j,l);

				sumproduct3(temp_row, &rji, maxdegree, Qnumber, j, l, R, C, n, m, Pi, maxcoldegree);		//Ë®àÁ? r Ë®äÊÅØ

				//fprintf(fid3, "min1:%f \n", rji);
				//fclose(fid3);

				product_rji = rji;
				rji = 0;
				//}//for (k=0;k<maxdegree;k++)	

					//store
				//printf("rji:%f \n", product_rji);
				if (R[j][l] == 0)
				{
					continue;
				}

				int v_dest = R[j][l] - 1;

				if (is_hotspot(v_dest))
				{
					temp_rji0[v_dest][r_column[v_dest]] = 0.5;
					temp_rji1[v_dest][r_column[v_dest]] = 0.5;
				}
				else
				{
					temp_rji0[v_dest][r_column[v_dest]] = 0.5 + 0.5 * product_rji;
					temp_rji1[v_dest][r_column[v_dest]] = 0.5 - 0.5 * product_rji;
				}
				r_column[v_dest] = r_column[v_dest] + 1;
				//}//if(qij1[j][l] != 0)
			}//for(l=0;l<maxdegree;l++)
		}// for(j=0;j<m;j++)
		//computation of {LLR_qij} 
		for (j = 0; j < n; j++)
		{
			for (l = 0; l < maxcoldegree; l++)
			{
				if (C[j][l] != 0)
				{
					product_qij0 = 1;
					product_qij1 = 1;
					for (i = 0; i < maxcoldegree; i++)
					{
						if (i != l)
						{
							product_qij0 = product_qij0 * temp_rji0[j][i];//rji0 ??check-to-variable messages
							product_qij1 = product_qij1 * temp_rji1[j][i];
						}
					}
					Qi0 = product_qij0 * temp_rji0[j][l];
					Qi1 = product_qij1 * temp_rji1[j][l];

					product_qij0 = product_qij0 * (1 - Pi[j]);		  //Ë®àÁ? q Ë®äÊÅØ
					product_qij1 = product_qij1 * Pi[j];

					if (product_qij0 == 0)
						product_qij0 = 0.0000000001;
					if (product_qij1 == 0)
						product_qij1 = 0.0000000001;

					K = product_qij0 + product_qij1;

					product_qij0 = product_qij0 / K;
					product_qij1 = product_qij1 / K;

					//store
					temp_qij0[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij0;		  //?´Â??¥Êñ∞ÂæåÁ? q Ë®äÊÅØ
					temp_qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij1;
					q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
				}
			}
		}
		for (cyclenumber = 0; cyclenumber < avoid_SPA_any_cycle_usage; cyclenumber++)
		{
			for (i = 0; i < n; i++)
				r_column[i] = 0;
			for (i = 0; i < m; i++)
				q_column[i] = 0;
			for (j = 0; j < m; j++)
			{
				for (l = 0; l < maxdegree; l++)
				{
					counter = 0;
					for (q = 0; q < maxdegree; q++)
					{
						temp_row[counter] = temp_qij1[j][q];
						counter++;
					}
					//printf("\n");
					//errno_t err_fopen1;
					//FILE* fid3;
					//err_fopen1 = fopen_s(&fid3, "rji.dat", "a+");
					//fprintf(fid3, "%d %d\n", j,l);

					sumproduct3(temp_row, &rji, maxdegree, Qnumber, j, l, R, C, n, m, Pi, maxcoldegree);

					//fprintf(fid3, "min1:%f \n", rji);
					//fclose(fid3);

					product_rji = rji;
					rji = 0;
					//}//for (k=0;k<maxdegree;k++)	

						//store
					//printf("rji:%f \n", product_rji);
					if (R[j][l] == 0)
					{
						continue;
					}

					int v_dest = R[j][l] - 1;

					if (is_hotspot(v_dest))
					{
						temp_rji0[v_dest][r_column[v_dest]] = 0.5;
						temp_rji1[v_dest][r_column[v_dest]] = 0.5;
					}
					else
					{
						temp_rji0[v_dest][r_column[v_dest]] = 0.5 + 0.5 * product_rji;
						temp_rji1[v_dest][r_column[v_dest]] = 0.5 - 0.5 * product_rji;
					}
					r_column[v_dest] = r_column[v_dest] + 1;
					//}//if(qij1[j][l] != 0)
				}//for(l=0;l<maxdegree;l++)
			}// for(j=0;j<m;j++)
			//computation of {LLR_qij} 
			for (j = 0; j < n; j++)
			{
				for (l = 0; l < maxcoldegree; l++)
				{
					if (C[j][l] != 0)
					{
						product_qij0 = 1;
						product_qij1 = 1;
						for (i = 0; i < maxcoldegree; i++)
						{
							if (i != l)
							{
								product_qij0 = product_qij0 * temp_rji0[j][i];//rji0 ??check-to-variable messages
								product_qij1 = product_qij1 * temp_rji1[j][i];
							}
						}

						product_qij0 = product_qij0 * (1 - Pi[j]);
						product_qij1 = product_qij1 * Pi[j];

						if (product_qij0 == 0)
							product_qij0 = 0.0000000001;
						if (product_qij1 == 0)
							product_qij1 = 0.0000000001;

						K = product_qij0 + product_qij1;

						product_qij0 = product_qij0 / K;
						product_qij1 = product_qij1 / K;

						//store
						temp_qij0[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij0;
						temp_qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = product_qij1;
						q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
					}
				}
			}
		}
		Qi0 = 1;
		Qi1 = 1;
		for (i = 0; i < maxcoldegree; i++)
		{
			j = C[Qnumber][i] - 1;
			for (int i2 = 0; i2 < maxdegree; i2++)
				if (R[j][i2] - 1 == Qnumber)
					l = i2;
			counter = 0;

			//fprintf(fid3, "(2)r%d %d:\n", j, R[j][l] - 1);

			for (q = 0; q < maxdegree; q++)
				if (q != l)
				{
					temp_row[counter] = temp_qij1[j][q];
					//fprintf(fid3, "q%d %d: %f \n", R[j][q]-1, j, temp_qij1[j][q]);
					//printf("%d %d %d %d %f\n", Qnumber, j, l,q, temp_qij1[j][q]);
					counter++;
				}

			sumproduct2(temp_row, &rji, maxdegree);

			//fprintf(fid3, "min*alpha:%f \n", rji*alpha);
			//printf("%d %d %f\n",j,l,rji*alpha);
			Qi0 = Qi0 * (0.5 + 0.5 * rji);
			Qi1 = Qi1 * (0.5 - 0.5 * rji);
		}

		//store		
		Qi0 = Qi0 * (1 - Pi[Qnumber]);
		Qi1 = Qi1 * Pi[Qnumber];

		if (Qi0 == 0)
			Qi0 = 0.0000000001;
		if (Qi1 == 0)
			Qi1 = 0.0000000001;

		K = Qi0 + Qi1;
		Qi0 = Qi0 / K;
		Qi1 = Qi1 / K;

		Q1[Qnumber] = Qi1;

		//?§Êñ∑ codeword
		if (Q1[Qnumber] > 0.5)
			c_[Qnumber] = 1;
		else c_[Qnumber] = 0;

	}
	//delete (temp_row);

	return 0;
}

void sumproduct1(double* row, double* rji, int maxdegree)
{
	int i;
	double product = 1;
	for (i = 0; i < maxdegree; i++)
	{
		product = product * (1 - 2 * row[i]);
	}

	*rji = product;
}

void sumproduct2(double* row, double* rji, int maxdegree)
{
	int i;
	double product = 1;
	for (i = 0; i < maxdegree - 1; i++)
	{
		product = product * (1 - 2 * row[i]);
	}

	*rji = product;
}

//void sumproduct3(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R)
//{
//	int i;
//	double product = 1;
//	for (i = 0; i < maxdegree; i++)
//	{
//		if (i != l && Qnumber != R[j][i] - 1)
//			product = product * (1 - 2 * row[i]);
//		else if (Qnumber == R[j][i] - 1)
//			if (row[i] >= 0.5)
//				//product = product * (1 - 2 * 0.51);
//				product = -product;
//			else if (row[i] < 0.5)
//				//product = product * (1 - 2 * 0.49);
//				product = product;
//	}
//
//	*rji = product;
//}

int find_parent_index(int level4_index, int n, int m, int** R, int** C, int maxdegree)
{
	 int level3_index, level2_index, level1_index;

	 int level3_found = 0;
	 for (int i = 0; i < m; i++) {
		  for (int j = 0; j < maxdegree; j++) {
			   if (R[i][j] == level4_index + 1) {
					level3_index = i;
					level3_found = 1;
					break;
			   }
		  }
		  if (level3_found) 
			   break;
	 }

	 int level2_found = 0;
	 for (int i = 0; i < n; i++) {
		  for (int j = 0; j < maxdegree; j++) {
			   if (C[i][j] == level3_index + 1) {
					level2_index = i;
					level2_found = 1;
					break;
			   }
		  }
		  if (level2_found) 
			   break;
	 }

	 // ?ûÂÇ≥ level2 ?ÑÁà∂ÁØÄÈª?
	 return level2_index;
}


#if 0
#if 0
void sumproduct3(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R, int** C, int n, int m, double* Pi, int maxcoldegree) {
    int i;
    double product = 1.0;
    bool has_root_source = false;

    // 1. Ê™¢Êü•Ê≠§Ê™¢È©óÁ?Èª?(j) ?Ñ„ÄåË??Ø‰?Ê∫ê„ÄçÊòØ?¶Â??´Ê†πÁØÄÈª?(Qnumber)
    for (i = 0; i < maxdegree; i++) {
        if (R[j][i] == 0) continue; // ?? ?≤Ë≠∑ÔºöÁï•?é‰?Ë¶èÂ??©Èô£?ÑË??∂Á©∫‰Ω?

        // Ê¢ù‰ª∂ÔºöÂ??úÊ??ãÁõ∏?∞Ë??∏Á?ÈªûÂ?Â•ΩÊòØ?πÁ?ÈªûÔ?‰∏îÂ??ê‰??Ø„ÄëÈÄôÊ¨°Ë¶ÅÂÇ≥?ûÁ??ÆÊ?Â∞çË±°(l)
        if (i != l && (R[j][i] - 1) == Qnumber) {
            has_root_source = true;
            break; // ?™Ë?Ëß∏ÁôºÊ¢ù‰ª∂ÔºåÁ??ª‰∏≠?∑Â???
        }
    }

    // 2. ?éØ ?∑Ë??åÊç®Ê£ÑÊñπÁ®ãÂ??çÈ?Ëº?
    if (has_root_source) {
        // ?¥Êé•Ëº∏Âá∫ 0.0ÔºåÂ??∑ÈÄôÂÄ?check node ?ÑÊ??âÊ???
        *rji = 0.0;  
        return; 
    }

    // 3. ?•ÁÇ∫ÂÆâÂÖ®?ÑÊ™¢È©óÁ?Èª?(?™Ë¢´Ëø¥Â?Ê±ôÊ?)ÔºåÂ?Ê≠?∏∏Ë®àÁ?Â§ñÂú®Ë®äÊÅØ
    for (i = 0; i < maxdegree; i++) {
        if (i != l) {
            if (R[j][i] == 0) continue; // ?? ?≤Ë≠∑ÔºöÈÅø?çÊ?Á©∫‰??∂Ê??âÊ?ÁØÄÈªû‰??≤Âéª
            product *= (1.0 - 2.0 * row[i]);
        }
    }

    *rji = product;
}
#endif
#endif

void sumproduct3(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R, int** C, int n, int m, double* Pi, int maxcoldegree)
{
	int i;
	double product = 1.0;

	for (i = 0; i < maxdegree; i++)
	{
		if (i == l || R[j][i] == 0)
		{
			continue;
		}

		product *= (1.0 - 2.0 * row[i]);
	}

	*rji = product;
}

double LogSumproductAlgorithm(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = ?Ä?âËº∏?•Ë??ØÁ∏Ω??
	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double LLR_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;

	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	for (i = 0; i < n; i++)
		r_column[i] = 0;
	for (i = 0; i < m; i++)
		q_column[i] = 0;
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "Qi.dat", "a+");
	for (j = 0; j < m; j++)
	{
		for (l = 0; l < maxdegree; l++)
		{
			counter = 0;
			for (q = 0; q < maxdegree; q++)
				if (avoid_two_cycle_usage == 0)//?ÑÂ? 2-cycle by willy
				{
					temp_row[counter] = qij1[j][q];
					counter++;
				}
				else
					if (q != l)
					{
						temp_row[counter] = qij1[j][q];
						counter++;
					}

			//errno_t err_fopen1;
			//FILE* fid3;
			//err_fopen1 = fopen_s(&fid3, "rji.dat", "a+");
			//fprintf(fid3, "%d %d\n", j,l);

			logsumproduct(temp_row, &rji, maxdegree);

			//fprintf(fid3, "min1:%f \n", rji);
			//fclose(fid3);

			LLR_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)	

				//store

			rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;
		
			r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
			//}//if(qij1[j][l] != 0)
		}//for(l=0;l<maxdegree;l++)
	}// for(j=0;j<m;j++)
	//computation of {LLR_qij} 
	for (j = 0; j < n; j++)
	{
		for (l = 0; l < maxcoldegree; l++)
		{
			if (C[j][l] != 0)
			{
				sigma = 0;
				for (i = 0; i < maxcoldegree; i++)
				{
					sigma += rji0[j][i];//rji0 ??check-to-variable messages
				}
				Qi = sigma;
				if (avoid_two_cycle_usage == 1) //?íÈô§ 2-cycle ÂΩ±Èüø
				{
					sigma -= rji0[j][l];
				}
				sigma += LLR_Pi1[j];
				//fprintf(fid3, "q%d %d: %f\n", j, C[j][l]-1, sigma);
				//store
				qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = sigma;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}
		//store		
		LQ[j] = LLR_Pi1[j] + Qi;

		//errno_t err_fopen1;
		//FILE* fid3;
		//err_fopen1 = fopen_s(&fid3, "Qi.dat", "a+");
		//fprintf(fid3, "%d %d\n", j, l);
		//fprintf(fid3, "%f \n", Qi);
		//fclose(fid3);

		//?§Êñ∑ codeword
		if (LQ[j] < 0)
			c_[j] = 1;
		else c_[j] = 0;
	}
	//fclose(fid3);
	//delete (temp_row);

	return 0;
}

double LogSumproductAlgorithm2(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = ?Ä?âËº∏?•Ë??ØÁ∏Ω??
	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double LLR_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;

	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	for (i = 0; i < n; i++)
		r_column[i] = 0;
	for (i = 0; i < m; i++)
		q_column[i] = 0;
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "Qi.dat", "a+");
	for (j = 0; j < m; j++)
	{
		for (l = 0; l < maxdegree; l++)
		{
			counter = 0;
			for (q = 0; q < maxdegree; q++)
				if (q != l)
				{
					temp_row[counter] = qij1[j][q];
					counter++;
				}

			//errno_t err_fopen1;
			//FILE* fid3;
			//err_fopen1 = fopen_s(&fid3, "rji.dat", "a+");
			//fprintf(fid3, "%d %d\n", j,l);

			logsumproduct(temp_row, &rji, maxdegree);

			//fprintf(fid3, "min1:%f \n", rji);
			//fclose(fid3);

			LLR_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)	

				//store

			rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;

			r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
			//}//if(qij1[j][l] != 0)
		}//for(l=0;l<maxdegree;l++)
	}// for(j=0;j<m;j++)
	//computation of {LLR_qij} 
	for (j = 0; j < n; j++)
	{
		for (l = 0; l < maxcoldegree; l++)
		{
			if (C[j][l] != 0)
			{
				sigma = 0;
				for (i = 0; i < maxcoldegree; i++)
				{
					sigma += rji0[j][i];//rji0 ??check-to-variable messages
				}
				Qi = sigma;
				sigma -= rji0[j][l];
				sigma += LLR_Pi1[j];
				//fprintf(fid3, "q%d %d: %f\n", j, C[j][l]-1, sigma);
				//store
				qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = sigma;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}
	}
	//fclose(fid3);
	return 0;
}

double LogSumproductAlgorithm_anycycle(double* LLR_Pi1, double** qij1, double** temp_qij1, int m, int** R, int** C, double** rji0, double** temp_rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = ?Ä?âËº∏?•Ë??ØÁ∏Ω??
	//double pai;//pai = ?´Â??®Ë???
	//double phai;//phai = ?´Â??®Ë???
	//double fabs;
	//double min;
	double LLR_rji;

	//double num1,num2;
	double rji;
	//double sign;
	//double a,b;
	int Qnumber;
	int cyclenumber;
	//double *temp_row;
	//temp_row = new double [maxdegree-1];
	//int start;
	int counter;
	//array ?ùÂ???
	for (Qnumber = 0; Qnumber < n; Qnumber++)
	{
		//fprintf(fid3, "Q%d\n", Qnumber);
		for (i = 0; i < n; i++)
			r_column[i] = 0;
		for (i = 0; i < m; i++)
			q_column[i] = 0;
		for (j = 0; j < m; j++)
		{
			for (l = 0; l < maxdegree; l++)
			{
				for (q = 0; q < maxdegree; q++)
					temp_row[q] = qij1[j][q];

				//fprintf(fid3, "(1)r%d %d:", j, R[j][l] - 1);
				//for (q = 0; q < maxdegree; q++)
				//{
				//	if (Qnumber == R[j][q] - 1)
				//		fprintf(fid3, "4-cycle-q:");
				//	fprintf(fid3, "%f ", temp_row[q]);
				//}
				//fprintf(fid3, "\n");
				logsumproduct_cycle(temp_row, &rji, maxdegree, Qnumber, j, l, R);
				//fprintf(fid3, "min*0.75:%f \n",rji*alpha);

				LLR_rji = rji;
				rji = 0;
				//}//for (k=0;k<maxdegree;k++)	

					//store

				temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;

				r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
				//}//if(qij1[j][l] != 0)
			}//for(l=0;l<maxdegree;l++)
		}// for(j=0;j<m;j++)
		//computation of {LLR_qij} 
		for (j = 0; j < n; j++)
		{
			for (l = 0; l < maxcoldegree; l++)
			{
				sigma = 0;
				for (i = 0; i < maxcoldegree; i++)
					sigma += temp_rji0[j][i];//rji0 ??check-to-variable messages
				sigma -= temp_rji0[j][l]; //??ô§ 2-cycle Â∞çÊ???
				sigma += LLR_Pi1[j]; //?†‰??öÈ??ùÂ? LLR
				//store
				//fprintf(fid3, "(1)q%d %d: %f\n", j, C[j][l]-1,sigma);
				temp_qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = sigma;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}
		for (cyclenumber = 0; cyclenumber < avoid_MSA_any_cycle_usage; cyclenumber++)
		{
			for (i = 0; i < n; i++)
				r_column[i] = 0;
			for (i = 0; i < m; i++)
				q_column[i] = 0;
			for (j = 0; j < m; j++)
			{
				for (l = 0; l < maxdegree; l++)
				{
					for (q = 0; q < maxdegree; q++)
						temp_row[q] = temp_qij1[j][q];

					logsumproduct_cycle(temp_row, &rji, maxdegree, Qnumber, j, l, R);


					LLR_rji = rji;
					rji = 0;
					//}//for (k=0;k<maxdegree;k++)	

					//store
					temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;

					r_column[R[j][l] - 1] = r_column[R[j][l] - 1] + 1;
					//}//if(qij1[j][l] != 0)
				}//for(l=0;l<maxdegree;l++)
			}// for(j=0;j<m;j++)
			//computation of {LLR_qij} 
			for (j = 0; j < n; j++)
			{
				for (l = 0; l < maxcoldegree; l++)
				{
					sigma = 0;
					for (i = 0; i < maxcoldegree; i++)
						sigma += temp_rji0[j][i];//rji0 ??check-to-variable messages
					sigma -= temp_rji0[j][l]; //??ô§ 2-cycle Â∞çÊ???
					sigma += LLR_Pi1[j]; //?†‰??öÈ??ùÂ? LLR
					//store
					temp_qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = sigma;
					q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
				}
			}
		}
		LLR_rji = 0;
		for (i = 0; i < maxcoldegree; i++)
		{
			j = C[Qnumber][i] - 1;
			for (int i2 = 0; i2 < maxdegree; i2++)
				if (R[j][i2] - 1 == Qnumber)
					l = i2;
			counter = 0;

			//fprintf(fid3, "(2)r%d %d:\n", j, R[j][l] - 1);

			for (q = 0; q < maxdegree; q++)
				if (q != l)
				{
					temp_row[counter] = temp_qij1[j][q];
					//fprintf(fid3, "q%d %d: %f \n", R[j][q]-1, j, temp_qij1[j][q]);
					//printf("%d %d %d %d %f\n", Qnumber, j, l,q, temp_qij1[j][q]);
					counter++;
				}

			logsumproduct(temp_row, &rji, maxdegree);
			//printf("%f\n", rji);
			//fprintf(fid3, "min*alpha:%f \n", rji*alpha);
			//printf("%d %d %f\n",j,l,rji*alpha);
			LLR_rji += rji;
		}
		LQ[Qnumber] = LLR_Pi1[Qnumber] + LLR_rji;

		//fprintf(fid3, "Q%d : %f\n",Qnumber, LQ[Qnumber]);

		//?§Êñ∑ codeword
		if (LQ[Qnumber] < 0)
			c_[Qnumber] = 1;
		else c_[Qnumber] = 0;
	}
	//fclose(fid3);

	//delete (temp_row);

	return 0;
}


void logsumproduct(double* row, double* rji, int maxdegree)
{
	double* sign_row;
	sign_row = new double[maxdegree];
	int i;
	double sign = 1;
	double temp_rji = 0;
	for (i = 0; i < maxdegree - 1; i++)
	{
		if (row[i] > 0)
			sign_row[i] = 1;
		else
			sign_row[i] = -1;

		sign = sign * sign_row[i];
	}
	for (i = 0; i < maxdegree - 1; i++)
	{
		//printf("%f\n", temp_rji);
		temp_rji += -log(tanh(0.5 * fabs(row[i]) ));
	}
	//if (isnan(temp_rji) == true)
	//{
	//	for (i = 0; i < maxdegree - 1; i++)
	//	{
	//		printf("%f\n", row[i]);
	//	}
	//}
	temp_rji = -log(tanh(0.5 * temp_rji));
	//printf("rji:%f\n", temp_rji);
	if (isinf(temp_rji) == 1)
		temp_rji = 999;
	else if (isinf(temp_rji) == -1)
		temp_rji = -999;

	*rji = sign * temp_rji;
	//*rji = sign;

	delete[] sign_row;
}

void logsumproduct_cycle(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R)
{
	double* sign_row;
	sign_row = new double[maxdegree];
	int i;
	double sign = 1;
	double temp_rji = 0;
	for (i = 0; i < maxdegree; i++)
	{
		if (i != l) //?àË?ÁÆóÁ¨¶?ü‰?Á©çÔ??øÂ? 2-cycle ÂΩ±Èüø sign Ë®àÁ?
		{
			if (row[i] > 0)
				sign_row[i] = 1;
			else
				sign_row[i] = -1;

			sign = sign * sign_row[i];
		}
	}
	for (i = 0; i < maxdegree; i++) //?çË?ÁÆ?magnitudeÔºåÊ???4-cycle
	{
		if (i != l && Qnumber != R[j][i] - 1)
		{
			temp_rji += -log(tanh(0.5 * fabs(row[i])));
		}
		//else if (Qnumber == R[j][i] - 1)
		//{
		//	temp_rji += -log(tanh(0.5 * 0));
		//}
	}

	temp_rji = -log(tanh(0.5 * temp_rji)); //?çÁ??ûË??ØÂÄ?
	//printf("rji:%f\n", temp_rji);
	if (isinf(temp_rji) == 1)
		temp_rji = 999;
	else if (isinf(temp_rji) == -1)
		temp_rji = -999;

	*rji = sign * temp_rji;
	//*rji = sign;

	delete[] sign_row;
}
