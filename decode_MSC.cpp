#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"

double MinSumCAlgorithm(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = �s�[���Ÿ��U
	//double pai;//pai = �s���Ÿ��S
	//double phai;//phai = �X
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
	//array �k�s	 
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
				if (avoid_two_cycle_usage == 0)//�٭�2-cycle�T�� by willy
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

			FILE* fid3;
			fid3 = fopen("rji.dat", "a+");
			//fprintf(fid3, "%d %d\n", j,l);

			if (avoid_two_cycle_usage == 0)
				minsum1(temp_row, &rji, maxdegree, l);
			else if (avoid_two_cycle_usage == 1)
				minsum2(temp_row, &rji, maxdegree);

			//fprintf(fid3, "min1:%f \n", rji);
			fclose(fid3);

			LLR_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)	

				//store
			if (alpha_usage == 0)
				rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;
			else
				rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji * alpha;
			fprintf(fid3, "r%d %d: %f\n", j, R[j][l]-1, LLR_rji * alpha);
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
					sigma += rji0[j][i];//rji0�s���Oc-v messages						
				}
				Qi = sigma;
				if (avoid_two_cycle_usage == 1) //�٭�2-cycle�T��
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

		//�P�_codeword
		if (LQ[j] < 0)
			c_[j] = 1;
		else c_[j] = 0;
	}
	//fclose(fid3);
	//delete (temp_row);

	return 0;
}

double MinSumCAlgorithm2(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = �s�[���Ÿ��U
	//double pai;//pai = �s���Ÿ��S
	//double phai;//phai = �X
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
	//array �k�s	 
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
				if (avoid_two_cycle_usage == 0)//�٭�2-cycle�T�� by willy
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
			//fid3 = fopen("rji.dat", "a+");
			//fprintf(fid3, "%d %d\n", j,l);

			if (avoid_two_cycle_usage == 0)
				minsum1(temp_row, &rji, maxdegree, l);
			else if (avoid_two_cycle_usage == 1)
				minsum2(temp_row, &rji, maxdegree);

			//fprintf(fid3, "min1:%f \n", rji);
			//fclose(fid3);


			LLR_rji = rji;
			rji = 0;
			//}//for (k=0;k<maxdegree;k++)	

				//store
			if (alpha_usage == 0)
				rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;
			else
				rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji * alpha;

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
					sigma += rji0[j][i];//rji0�s���Oc-v messages						
				}
				Qi = sigma;
				if (avoid_two_cycle_usage == 1) //�٭�2-cycle�T��
				{
					sigma -= rji0[j][l];
				}
				sigma += LLR_Pi1[j];
				//store
				qij1[C[j][l] - 1][q_column[C[j][l] - 1]] = sigma;
				q_column[C[j][l] - 1] = q_column[C[j][l] - 1] + 1;
			}
		}
	}

	//delete (temp_row);

	return 0;
}

double MinSumCAlgorithm_anycycle(double* LLR_Pi1, double** qij1, double** temp_qij1, int m, int** R, int** C, double** rji0, double** temp_rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row)
{
	int i, j, l, q;
	double Qi = 0;
	double sigma;//sigma = �s�[���Ÿ��U
	//double pai;//pai = �s���Ÿ��S
	//double phai;//phai = �X
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
	//array �k�s	 

	int Qnumber;
	int cyclenumber;
	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "Qi2.dat", "a+");
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
				minsum5(temp_row, &rji, maxdegree, Qnumber, j, l, R);
				//fprintf(fid3, "min*0.75:%f \n",rji*alpha);

				LLR_rji = rji;
				rji = 0;
				//}//for (k=0;k<maxdegree;k++)	

					//store
				if (alpha_usage == 0)
					temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;
				else
					temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji * alpha;

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
					sigma += temp_rji0[j][i];//rji0�s���Oc-v messages						
				sigma -= temp_rji0[j][l]; //2-cycle����
				sigma += LLR_Pi1[j]; //�[�J��l���v
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

					minsum5(temp_row, &rji, maxdegree, Qnumber, j, l, R);


					LLR_rji = rji;
					rji = 0;
					//}//for (k=0;k<maxdegree;k++)	

						//store
					if (alpha_usage == 0)
						temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji;
					else
						temp_rji0[R[j][l] - 1][r_column[R[j][l] - 1]] = LLR_rji * alpha;

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
						sigma += temp_rji0[j][i];//rji0�s���Oc-v messages						
					sigma -= temp_rji0[j][l]; //2-cycle����
					sigma += LLR_Pi1[j]; //�[�J��l���v
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

			minsum2(temp_row, &rji, maxdegree);
			//printf("%f\n", rji);
			//fprintf(fid3, "min*alpha:%f \n", rji*alpha);
			//printf("%d %d %f\n",j,l,rji*alpha);
			if (alpha_usage == 0)
				LLR_rji += rji;
			else
				LLR_rji += rji * alpha;
		}
		LQ[Qnumber] = LLR_Pi1[Qnumber] + LLR_rji;

		//fprintf(fid3, "Q%d : %f\n",Qnumber, LQ[Qnumber]);

		//�P�_codeword
		if (LQ[Qnumber] < 0)
			c_[Qnumber] = 1;
		else c_[Qnumber] = 0;
	}
	//fclose(fid3);

	//delete (temp_row);

	return 0;
}

void minsum1(double* row, double* rji, int maxdegree, int l)
{
	double temp_sign;
	int i;
	double min1;
	double sign = 1;

	for (i = 0; i < maxdegree; i++)
	{
		if (i != l)
		{
			if (row[i] > 0)
				temp_sign = 1;
			else
				temp_sign = -1;

			sign = sign * temp_sign;
		}
	}

	min1 = fabs(row[0]);
	for (i = 1; i < maxdegree; i++)
		if (fabs(row[i]) < min1)
			min1 = fabs(row[i]);

	//errno_t err_fopen1;
	//FILE* fid3;
	//err_fopen1 = fopen_s(&fid3, "row.dat", "a+");
	//for (i = 0; i < maxdegree; i++)
	//{
	//	fprintf(fid3, "%f ",row[i]);
	//}
	//fclose(fid3);

	* rji = sign * min1;
}

void minsum2(double* row, double* rji, int maxdegree)
{
	double temp_sign;
	int i;
	double min1;
	double sign = 1;

	for (i = 0; i < maxdegree - 1; i++)
	{
		if (row[i] >= 0)
			temp_sign = 1;
		else
			temp_sign = -1;

		sign = sign * temp_sign;
	}

	min1 = fabs(row[0]);
	for (i = 1; i < maxdegree - 1; i++)
		if (fabs(row[i]) < min1)
			min1 = fabs(row[i]);

	/*errno_t err_fopen1;
	FILE* fid3;
	err_fopen1 = fopen_s(&fid3, "row2.dat", "a+");
	for (i = 0; i < maxdegree-1; i++)
	{
		fprintf(fid3, "%f ", row[i]);
	}
	fclose(fid3);*/


	* rji = sign * min1;
	//*rji = sign;
}

void minsum5(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R)
{
	double temp_sign;
	int i;
	double min1;
	double sign = 1;

	for (i = 0; i < maxdegree; i++)
	{
		if (i != l)
		{
			if (row[i] >= 0)
				temp_sign = 1;
			else
				temp_sign = -1;

			sign = sign * temp_sign;
		}
	}

	for (i = 0; i < maxdegree; i++)
		if (i != l && Qnumber != R[j][i] - 1)
		{
			min1 = fabs(row[i]);
			break;
		}

	for (i = 0; i < maxdegree; i++) //�v�@���
	{
		if (i != l && fabs(row[i]) < min1 && Qnumber != R[j][i] - 1)
		{
			min1 = fabs(row[i]);
		}
	}

	*rji = sign * min1;
}
