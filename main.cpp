
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "Configuration.h"
#include <string.h>
#include <omp.h>

int main()
{
	system("chcp 65001");

	int times;
	int* error_exam1;
	int* total_error_bit1;
	double* BER1;
	int* hard_decoding_error1;
	double* hard_decoding_BER1;
	int* total_iteration1;
	int* real_row_num1;
	int* exam_number1;

	if (sumproduct_usage == 1 && log_sumproduct_usage == 0)
		printf("Sum-Product\n");
	else if (sumproduct_usage == 1 && log_sumproduct_usage == 1)
		printf("Log-Sum-Product\n");
	else if (alpha_usage == 0)
		printf("MSA\n");
	else
		printf("NMSA\n");
	if (iteration_output_usage != 0)
		printf("First output at iteration = %d\n", iteration_output_usage);
	if (Max_iteration_usage == 1)
		printf("Exams reached the maximum number of iterations aren't counted\n");
	if (avoid_two_cycle_usage == 0)
		printf("還原 2-cycle\n");
	if (avoid_MSA_any_cycle_usage == 0 || avoid_SPA_any_cycle_usage == 0)
		printf("刪除 4-cycle\n");
	if (avoid_MSA_any_cycle_usage == 1 || avoid_SPA_any_cycle_usage == 1)
		printf("刪除 6-cycle 以下的 cycle\n");
	if (avoid_MSA_any_cycle_usage == 2 || avoid_SPA_any_cycle_usage == 2)
		printf("刪除 8-cycle 以下的 cycle\n");
	if (avoid_MSA_any_cycle_usage == 3 || avoid_SPA_any_cycle_usage == 3)
		printf("刪除 10-cycle 以下的 cycle\n");
	if (random_usage != 1)
		printf("The noise pattern is fixed, seed:%d\n", random_usage);
	if (noise_estimation_errors_usage == 0)
		printf("Not considering noise estimation errors\n");

	printf("OpenMP enabled, max threads = %d\n", omp_get_max_threads());

	for (times = 0; times < simulation_times; times++)
	{
		error_exam1 = new int[simulation_times];
		total_error_bit1 = new int[simulation_times];
		BER1 = new double[simulation_times];
		hard_decoding_error1 = new int[simulation_times];
		hard_decoding_BER1 = new double[simulation_times];
		total_iteration1 = new int[simulation_times];
		real_row_num1 = new int[simulation_times];
		exam_number1 = new int[simulation_times];

		int exam;
		int error_exam = 0;
		double total_error_bit = 0;
		int n, m, maxdegree = 0, maxcoldegree = 0;

		FILE* fid;
		errno_t err;
		char filename[99];

		//***********************************讀檔名稱與位置****************************
		//strcpy(filename,"../G4_1.dat");
		//strcpy(filename,"(18,9)H.dat");
		//strcpy(filename,"(6,3)H.dat");
		//strcpy(filename, "(6,3)H_irregular.dat");
		//strcpy(filename,"../96.3.967.dat"); 
		//strcpy(filename,"../204.33.486.dat");
		//strcpy(filename,"252.252.3.252.dat");
		//strcpy(filename,"../408.3.854.dat"); 
		//strcpy(filename,"../../816.3.174.dat");
		//strcpy(filename,"../../504.504.3.504.dat");
		//strcpy(filename,"(96,48)\\96.33.968.dat");
		//strcpy(filename,"(408,204)\\G6_1.dat");
		//strcpy(filename,"(204,102)\\G4_20.dat");
		//strcpy(filename,"Margulis2640.1320.3.dat");
		//strcpy(filename,"(816,408)\\(816,408)G8.dat");
		//strcpy(filename,"t252x504.dat");
		//strcpy(filename,"PEGReg252x504.dat");

		//strcpy(filename,"(96,48)Mackay.dat");
		//strcpy(filename, "96.44.443.dat");
		strcpy(filename, "408.3.854.dat");
		//strcpy(filename, "(504,252)Mackay.dat");
		//strcpy(filename,"816.3.174.dat");
		//strcpy(filename,"PEGReg252x504_0623.dat");
		//strcpy(filename, "(816,408)G4.dat");
		//strcpy(filename, "PEGReg252x504_new.dat");
		//*****************************************************************************

		err = fopen_s(&fid, filename, "r");
		if (err != 0 || fid == NULL) {
			printf("錯誤：無法開啟輸入檔 %s！請確認檔案是否存在於執行目錄。\n", filename);
			system("pause");
			return -1;
		}

		// 如果程式跑到這裡，代表檔案讀取成功
		fscanf_s(fid, "%d", &n);
		fscanf_s(fid, "%d", &m);
		fscanf_s(fid, "%d", &maxcoldegree);

		int original_m = m;
		errno_t err_fopen;
		FILE* fid2;
		char filename2[99];

		//***********************************寫檔名稱與位置****************************
		strcpy(filename2, "408_SPA_Imax50_discard_check_equation.dat");
		//strcpy(filename2, "0_816.3.174_SPA_test_20250623.dat");
		//strcpy(filename2, "0_(816,408)G4_SPA_without_4-cycle_effect_20250623.dat");
		//strcpy(filename2, "0_(816,408)G4_SPA_test_20250623.dat");
		//strcpy(filename2, "0_PEGReg252x504_new_SPA_without_4-cycle_effect_20250623.dat");
		//strcpy(filename2, "0_PEGReg252x504_new_SPA_test_20250623.dat");
		////strcpy(filename2, "0_408.3.854_SPA_without_4-cycle_effect_iter=25_20250626.dat");
		//strcpy(filename2, "0_408.3.854_SPA_test_20250624.dat");
		//strcpy(filename2, "0_96.44.443_SPA_without_4-cycle_effect_20250619.dat");
		//strcpy(filename2,"decoding_test(18,9).dat"); 
		//strcpy(filename2, "decoding_test96.3.967.dat"); 
		//strcpy(filename2,"decoding_test204.33.486.dat");
		//strcpy(filename2, "decoding_test408.3.854.dat");
		//strcpy(filename2,"decoding_test816.3.174.dat");
		//strcpy(filename2,"decoding_test504.504.3.504.dat");
		//***********************************宣告變數****************************

		int i, j, k;

		double hard_decoding_error = 0;
		int total_iteration = 0;
		double BER = 0;
		double hard_decoding_BER = 0;
		double temp_m = m, temp_n = n;
		double rate = 1 - (temp_m / temp_n);

		int** H_original;
		H_original = new int* [m];
		for (i = 0; i < m; i++)
			H_original[i] = new int[n];
		for (j = 0; j < m; j++)
			for (i = 0; i < n; i++)
				H_original[j][i] = 0;

		int** G;
		G = new int* [abs(n - m)];
		for (i = 0; i < abs(n - m); i++)
			G[i] = new int[n];

		for (j = 0; j < abs(n - m); j++)
			for (i = 0; i < n; i++)
				G[j][i] = 0;

		int real_row_num;

		//*************************前處理***********************
		Preprocess(maxcoldegree, &maxdegree, G, H_original, &real_row_num,filename);
		int** R;
		R = new int* [m];
		for (j = 0; j < m; j++)
			R[j] = new int[maxdegree];
		for (j = 0; j < m; j++)
			for (k = 0; k < maxdegree; k++)
				R[j][k] = 0;
		//*********************************************************
		int** C;
		C = new int* [n];
		for (j = 0; j < n; j++)
			C[j] = new int[maxcoldegree];
		for (j = 0; j < n; j++)
			for (k = 0; k < (int)maxcoldegree; k++)
				C[j][k] = 0;

		RCmatrix(maxcoldegree, R, C, n, m, H_original);

		int limit = 0;

		double omp_start = omp_get_wtime();

		//*****************************exam 平行模擬 (OpenMP 平行化)*****************************
		#pragma omp parallel for reduction(+:total_error_bit, error_exam, hard_decoding_error, total_iteration, limit) schedule(dynamic)
		for (exam = 0; exam < exam_number; exam++)
		{
			// === 每個執行緒獨立的亂數種子 ===
			unsigned int thread_seed;
			if (random_usage == 1)
				thread_seed = (unsigned int)(exam * 97 + omp_get_thread_num() * 7919 + (unsigned int)time(NULL));
			else
				thread_seed = (unsigned int)(random_usage + exam);
			srand(thread_seed);

			// === 每個執行緒專屬的陣列 (Thread-Local) ===
			int* r_column = new int[n];
			for (int jj = 0; jj < n; jj++) r_column[jj] = 0;
			int* q_column = new int[m];
			for (int jj = 0; jj < m; jj++) q_column[jj] = 0;

			double* LLR_Pi1 = new double[n];
			for (int jj = 0; jj < n; jj++) LLR_Pi1[jj] = 0;
			double* Pi = new double[n];
			for (int jj = 0; jj < n; jj++) Pi[jj] = 0;

			double* temp_row = new double[maxdegree];

			int* c_ = new int[n];
			for (int jj = 0; jj < n; jj++) c_[jj] = 0;
			int* c = new int[n];
			for (int jj = 0; jj < n; jj++) c[jj] = 0;
			int* message = new int[abs(n - m)];
			for (int jj = 0; jj < abs(n - m); jj++) message[jj] = 0;
			double* yi = new double[n];
			for (int jj = 0; jj < n; jj++) yi[jj] = 0;
			int* syndrom = new int[m];
			for (int jj = 0; jj < m; jj++) syndrom[jj] = 0;

			double* LQ = new double[n];
			for (int jj = 0; jj < n; jj++) LQ[jj] = 0;
			double* Q1 = new double[n];
			for (int jj = 0; jj < n; jj++) Q1[jj] = 0;

			double** rji0 = new double* [n];
			for (int jj = 0; jj < n; jj++) rji0[jj] = new double[(int)maxcoldegree];
			for (int jj = 0; jj < n; jj++)
				for (int ii = 0; ii < (int)maxcoldegree; ii++)
					rji0[jj][ii] = 0;

			double** rji1 = new double* [n];
			for (int jj = 0; jj < n; jj++) rji1[jj] = new double[(int)maxcoldegree];
			for (int jj = 0; jj < n; jj++)
				for (int ii = 0; ii < (int)maxcoldegree; ii++)
					rji1[jj][ii] = 0;

			double** qij0 = new double* [m];
			for (int jj = 0; jj < m; jj++) qij0[jj] = new double[maxdegree];
			for (int jj = 0; jj < m; jj++)
				for (int ii = 0; ii < maxdegree; ii++)
					qij0[jj][ii] = 0;

			double** qij1 = new double* [m];
			for (int jj = 0; jj < m; jj++) qij1[jj] = new double[maxdegree];
			for (int jj = 0; jj < m; jj++)
				for (int ii = 0; ii < maxdegree; ii++)
					qij1[jj][ii] = 0;

			double** temp_rji0 = new double* [n];
			for (int jj = 0; jj < n; jj++) temp_rji0[jj] = new double[maxcoldegree];
			for (int jj = 0; jj < n; jj++)
				for (int ii = 0; ii < maxcoldegree; ii++)
					temp_rji0[jj][ii] = 0;

			double** temp_qij1 = new double* [m];
			for (int jj = 0; jj < m; jj++) temp_qij1[jj] = new double[maxdegree];
			for (int jj = 0; jj < m; jj++)
				for (int ii = 0; ii < maxdegree; ii++)
					temp_qij1[jj][ii] = 0;

			double** temp_rji1 = new double* [n];
			for (int jj = 0; jj < n; jj++) temp_rji1[jj] = new double[maxcoldegree];
			for (int jj = 0; jj < n; jj++)
				for (int ii = 0; ii < maxcoldegree; ii++)
					temp_rji1[jj][ii] = 0;

			double** temp_qij0 = new double* [m];
			for (int jj = 0; jj < m; jj++) temp_qij0[jj] = new double[maxdegree];
			for (int jj = 0; jj < m; jj++)
				for (int ii = 0; ii < maxdegree; ii++)
					temp_qij0[jj][ii] = 0;

			// === 進度輸出 (每 1000 次顯示一次，避免多執行緒輸出過多) ===
			if (exam % 1000 == 0)
			{
				#pragma omp critical
				printf("exam = %d (thread %d)\n", exam, omp_get_thread_num());
			}

			int errorbit = 0;
			int c_check;
			//***************編碼*************
			Encode(message, c, G, n, m);
			//***************加入雜訊與 AWGN****************
			double noise_power;
			double Rnoise_power = 0;
			noise_power = 1/pow(10.0, (SNR[times] / 10));

			if (sumproduct_usage == 1 && log_sumproduct_usage == 0)
			{
				gaussian_noise(c, yi, n, noise_power,SNR[times], Rnoise_power);
				if (noise_estimation_errors_usage == 0)
					gaussian_noise_Minsum_c(yi, n, Rnoise_power);
				else
					gaussian_noise_Minsum_c(yi, n, noise_power);
				for (int ii = 0; ii < n; ii++)
					yi[ii] = 1 / (1 + exp(yi[ii]));
				for (int ii = 0; ii < n; ii++) 
					Pi[ii] = yi[ii];
				for (int ii = 0; ii < m; ii++)
					for (int jj = 0; jj < maxdegree; jj++)
						if (R[ii][jj] != 0)
							qij1[ii][jj] = Pi[R[ii][jj] - 1];
			}
			else
			{
				gaussian_noise(c, yi, n, noise_power, SNR[times], Rnoise_power);
				if (noise_estimation_errors_usage == 0)
				{
					gaussian_noise_Minsum_c(yi, n, Rnoise_power);
				}
				else
					gaussian_noise_Minsum_c(yi, n, noise_power);
				for (int ii = 0; ii < n; ii++)
					LLR_Pi1[ii] = yi[ii];
				for (int ii = 0; ii < m; ii++)
					for (int jj = 0; jj < maxdegree; jj++)
						if (R[ii][jj] != 0)
							qij1[ii][jj] = LLR_Pi1[R[ii][jj] - 1];
			}

			//*****************************hard-decoding****************************
			int hard_decoding_output;
			double local_hard_decoding_error = 0;
			if (sumproduct_usage == 1 && log_sumproduct_usage == 0)
			{
				for (int ii = 0; ii < n; ii++)
				{
					if (yi[ii] > 0.5)
						hard_decoding_output = 1;
					else hard_decoding_output = 0;
					if (hard_decoding_output != c[ii])
					{
						local_hard_decoding_error += 1;
					}
				}
			}
			else
			{
				for (int ii = 0; ii < n; ii++)
				{
					if (yi[ii] > 0)
						hard_decoding_output = 0;
					else hard_decoding_output = 1;
					if (hard_decoding_output != c[ii])
					{
						local_hard_decoding_error += 1;
					}
				}
			}
			//*****************************soft-decoding****************************	
			int iter_i = 0;
			while (iter_i < iteration)
			{
				if (sumproduct_usage == 1 && log_sumproduct_usage == 0 && avoid_SPA_any_cycle_usage>=0)
				{
					if (iter_i == 0)
						iter_i = iter_i + 2+ avoid_SPA_any_cycle_usage;
					SumproductAlgorithm2(Pi, qij0, qij1, m, R, C, rji0, rji1, n, maxdegree, maxcoldegree, c_, r_column, q_column, Q1, temp_row);
					SumproductAlgorithm_cycle(Pi, qij0, qij1, temp_qij0, temp_qij1, m, R, C, rji0, rji1, temp_rji0, temp_rji1, n, maxdegree, maxcoldegree, c_, r_column, q_column, Q1, temp_row);
					c_check = 0;
					for (int jj = 0; jj < m; jj++)
						syndrom[jj] = 0;
					for (int jj = 0; jj < m; jj++)
					{
						for (int kk = 0; kk < maxdegree; kk++)
						{
							if (R[jj][kk] != 0)
								syndrom[jj] += c_[R[jj][kk] - 1];
						}
						syndrom[jj] = syndrom[jj] % 2;
						if (syndrom[jj] == 0)
							c_check = c_check + 1;
					}
					if (c_check == m)
						break;
					else
						iter_i++;
				}

				else if (sumproduct_usage == 1 && log_sumproduct_usage == 1 && avoid_SPA_any_cycle_usage >=0)
				{
					if (iter_i == 0)
						iter_i = iter_i + 2 + avoid_SPA_any_cycle_usage;
					LogSumproductAlgorithm2(LLR_Pi1, qij1, m, R, C, rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					LogSumproductAlgorithm_anycycle(LLR_Pi1, qij1, temp_qij1, m, R, C, rji0, temp_rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					c_check = 0;
					for (int jj = 0; jj < m; jj++)
						syndrom[jj] = 0;
					for (int jj = 0; jj < m; jj++)
					{
						for (int kk = 0; kk < maxdegree; kk++)
						{
							if (R[jj][kk] != 0)
								syndrom[jj] += c_[R[jj][kk] - 1];
						}
						syndrom[jj] = syndrom[jj] % 2;
						if (syndrom[jj] == 0)
							c_check = c_check + 1;
					}
					if (c_check == m)
						break;
					else
						iter_i++;
				}
				else if (sumproduct_usage == 1 && log_sumproduct_usage == 0 && avoid_SPA_any_cycle_usage < 0)
				{
					 SumproductAlgorithm(Pi, qij0, qij1, m, R, C, rji0, rji1, n, maxdegree, maxcoldegree, c_, r_column, q_column, Q1, temp_row);
					 c_check = 0;
					 for (int jj = 0; jj < m; jj++)
						 syndrom[jj] = 0;
					 for (int jj = 0; jj < m; jj++)
					 {
						 for (int kk = 0; kk < maxdegree; kk++)
						 {
							 if (R[jj][kk] != 0)
								 syndrom[jj] += c_[R[jj][kk] - 1];
						 }
						 syndrom[jj] = syndrom[jj] % 2;
						 if (syndrom[jj] == 0)
							 c_check = c_check + 1;
					 }
					 if (c_check == m && iter_i>=iteration_output_usage)
						 break;
					 else
						 iter_i++;
				}
				else if (sumproduct_usage == 1 && log_sumproduct_usage == 1 && avoid_SPA_any_cycle_usage < 0)
				{
					LogSumproductAlgorithm(LLR_Pi1, qij1, m, R, C, rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					c_check = 0;
					for (int jj = 0; jj < m; jj++)
						syndrom[jj] = 0;
					for (int jj = 0; jj < m; jj++)
					{
						for (int kk = 0; kk < maxdegree; kk++)
						{
							if (R[jj][kk] != 0)
								syndrom[jj] += c_[R[jj][kk] - 1];
						}
						syndrom[jj] = syndrom[jj] % 2;
						if (syndrom[jj] == 0)
							c_check = c_check + 1;
					}
					if (c_check == m && iter_i >= iteration_output_usage)
						break;
					else
						iter_i++;
				}
				else if (avoid_MSA_any_cycle_usage >= 0)
				{
					if (iter_i == 0)
						iter_i = iter_i + 2 + avoid_MSA_any_cycle_usage;
					MinSumCAlgorithm2(LLR_Pi1, qij1, m, R, C, rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					MinSumCAlgorithm_anycycle(LLR_Pi1, qij1, temp_qij1, m, R, C, rji0, temp_rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					c_check = 0;
					for (int jj = 0; jj < m; jj++)
						syndrom[jj] = 0;
					for (int jj = 0; jj < m; jj++)
					{
						for (int kk = 0; kk < maxdegree; kk++)
						{
							if (R[jj][kk] != 0)
								syndrom[jj] += c_[R[jj][kk] - 1];
						}
						syndrom[jj] = syndrom[jj] % 2;
						if (syndrom[jj] == 0)
							c_check = c_check + 1;
					}
					if (c_check == m)
						break;
					else
						iter_i++;
				}
				else
				{
					MinSumCAlgorithm(LLR_Pi1, qij1, m, R, C, rji0, n, maxdegree, maxcoldegree, c_, r_column, q_column, LQ, temp_row);
					c_check = 0;
					for (int jj = 0; jj < m; jj++)
						syndrom[jj] = 0;
					for (int jj = 0; jj < m; jj++)
					{
						for (int kk = 0; kk < maxdegree; kk++)
						{
							if (R[jj][kk] != 0)
								syndrom[jj] += c_[R[jj][kk] - 1];
						}
						syndrom[jj] = syndrom[jj] % 2;
						if (syndrom[jj] == 0)
							c_check = c_check + 1;
					}
					if (c_check == m && iter_i>=iteration_output_usage)
						break;
					else
						iter_i++;
				}
			}//while(iter_i < iteration)

			// === 統計結果 (使用 reduction 累加變數) ===
			if (Max_iteration_usage == 0) 
			{
				total_iteration += iter_i + 1;
				for (int ii = 0; ii < n; ii++)
					if (c[ii] != c_[ii])
						errorbit = errorbit + 1;
				if (errorbit != 0)
					error_exam = error_exam + 1;

				total_error_bit = total_error_bit + errorbit;
				limit = limit + 1;
			}
			else if (iter_i < 50)
			{
				total_iteration += iter_i + 1;
				for (int ii = 0; ii < n; ii++)
					if (c[ii] != c_[ii])
						errorbit = errorbit + 1;
				if (errorbit != 0)
					error_exam = error_exam + 1;

				total_error_bit = total_error_bit + errorbit;
				limit = limit + 1;
			}

			hard_decoding_error += local_hard_decoding_error;

			// === 釋放本次 exam 的所有記憶體 ===
			for (int ii = 0; ii < m; ii++)
			{
				delete[] qij0[ii];
				delete[] qij1[ii];
				delete[] temp_qij0[ii];
				delete[] temp_qij1[ii];
			}
			delete[] qij0;
			delete[] qij1;
			delete[] temp_qij0;
			delete[] temp_qij1;

			for (int ii = 0; ii < n; ii++)
			{
				delete[] rji0[ii];
				delete[] rji1[ii];
				delete[] temp_rji0[ii];
				delete[] temp_rji1[ii];
			}
			delete[] rji0;
			delete[] rji1;
			delete[] temp_rji0;
			delete[] temp_rji1;

			delete[] Pi;
			delete[] LQ;
			delete[] Q1;
			delete[] temp_row;
			delete[] r_column;
			delete[] q_column;
			delete[] syndrom;
			delete[] yi;
			delete[] LLR_Pi1;
			delete[] c_;
			delete[] c;
			delete[] message;

		}//exam 迴圈 (OpenMP parallel for)

		double omp_end = omp_get_wtime();
		printf("Time cost: %f sec\n", omp_end - omp_start);

		// === 釋放一次性陣列 (R, C, G, H_original) ===
		for (i = 0; i < m; i++)
		{
			delete[] R[i];
			delete[] H_original[i];
		}
		delete[] R;
		delete[] H_original;

		for (i = 0; i < n; i++)
		{
			delete[] C[i];
		}
		delete[] C;

		for (i = 0; i < abs(n - m); i++)
			delete[] G[i];
		delete[] G;

		if (err == 0)
		{
			printf("The file %s was opened\n", filename2);
		}

		BER = total_error_bit / (n * exam_number);
		hard_decoding_BER = hard_decoding_error / (n * exam_number);

		error_exam1[times] = error_exam;
		total_error_bit1[times] = total_error_bit;
		BER1[times] = BER;
		hard_decoding_error1[times] = hard_decoding_error;
		hard_decoding_BER1[times] = hard_decoding_BER;
		total_iteration1[times] = total_iteration;
		real_row_num1[times] = real_row_num;
		exam_number1[times] = limit;
		err_fopen = fopen_s(&fid2, filename2, "a+");
		fprintf(fid2, "\nSNR is %e \n", SNR[times]);
		if(SNR_offset_usage !=0)
			fprintf(fid2, "SNR_offset_usage is %f \n", SNR_offset_usage);
		fprintf(fid2, "The number of error exam is %d\n", error_exam1[times]);
		fprintf(fid2, "The total error bit is %d\n", total_error_bit1[times]);
		fprintf(fid2, "The BER is %.10f\n", BER1[times]);
		fprintf(fid2, "The number of hard decoding error bit is %d\n", hard_decoding_error1[times]);
		fprintf(fid2, "The hard decoding BER is %.10f\n", hard_decoding_BER1[times]);
		fprintf(fid2, "The number of total iteration  is %d\n", total_iteration1[times]);
		fprintf(fid2, "Matrix rank is %d\n", real_row_num1[times]);
		fprintf(fid2, "Total effective exam number is %d\n ", exam_number1[times]);
		fprintf(fid2, "The iteration number for one exam %d\n", iteration);
		if (sumproduct_usage == 1 && log_sumproduct_usage==0)
			fprintf(fid2, "This is Sum-Product\n");
		else if (sumproduct_usage==1 && log_sumproduct_usage==1)
			fprintf(fid2, "This is Log-Sum-Product\n");
		else if (alpha_usage == 0)
			fprintf(fid2, "This is MSA\n");
		else
			fprintf(fid2, "This is NMSA\n");
		if(iteration_output_usage!=0)
			fprintf(fid2, "First output at iteration == %d\n", iteration_output_usage);
		if (Max_iteration_usage == 1)
			fprintf(fid2, "Exams reached the maximum number of iterations aren't counted\n");
		if (avoid_two_cycle_usage == 0)
			fprintf(fid2, "已還原 2-cycle\n");
		if (avoid_MSA_any_cycle_usage == 0 || avoid_SPA_any_cycle_usage==0)
			fprintf(fid2, "已排除 4-cycle\n");
		if (avoid_MSA_any_cycle_usage == 1 || avoid_SPA_any_cycle_usage==1)
			fprintf(fid2, "已排除 6-cycle 以下的 cycle\n");
		if (avoid_MSA_any_cycle_usage == 2 || avoid_SPA_any_cycle_usage==2)
			fprintf(fid2, "已排除 8-cycle 以下的 cycle\n");
		if (avoid_MSA_any_cycle_usage == 3 || avoid_SPA_any_cycle_usage==3)
			fprintf(fid2, "已排除 10-cycle 以下的 cycle\n");
		if(random_usage!=1)
			fprintf(fid2, "The noise pattern is fixed, seed:%d\n", random_usage);
		if (noise_estimation_errors_usage == 0)
			fprintf(fid2, "Not considering noise estimation errors\n");
		fprintf(fid2, "OpenMP threads used: %d\n", omp_get_max_threads());

		fprintf(fid2, "\n");

		fclose(fid2);
		delete [] error_exam1;
		delete [] total_error_bit1;
		delete [] BER1;
		delete [] hard_decoding_error1;
		delete [] hard_decoding_BER1;
		delete [] total_iteration1;
		delete [] real_row_num1;
		delete [] exam_number1;
	}
	system("pause");
}
