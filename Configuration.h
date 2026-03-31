#include <stdio.h>

//參數設定
//跑模擬時要注意system("pause")有沒有關掉
const int simulation_times = 7;

//const double SNR[simulation_times] = {2.5};
//const double SNR[simulation_times] = {1.0,1.25,1.5,1.75,2.0,2.25,2.5,2.75,3.0,3.25,3.5};
const double SNR[simulation_times] = {1.0,1.25,1.5,1.75,2.0,2.25,2.5}; //(dB)，做7個db，simulation_times也要變動
//const double SNR[simulation_times] = {2.5,2.75,3.0,3.25,3.5};//(dB)，做多個db，simulation_times也要變動
//const double SNR[simulation_times] = { 3.75, 4.0 };    //補高SNR
//const double SNR[simulation_times] = {1.0,1.25,1.5};
//const double SNR[simulation_times] = {1.75,2.0,2.25};
//const double SNR[simulation_times] = {2.25,2.5,2.75};
//const double SNR[simulation_times] = {2.5,2.75,3.0};
//const double SNR[simulation_times] = {3.0,3.25,3.5};
//const double SNR[simulation_times] = {3.25,3.5};
//const double rate = 0.4;

const int iteration = 50; //最大迭代次數
const int effective_exam_number = 100000; //有效模擬次數 若需僅採計迭代次數未達到最大迭代次數時使用(搭配Max_iteration_usage)
const int noise_estimation_errors_usage = 1; //1為考慮SNR估計誤差(除以設定SNR power)，0為不考慮(除以實際噪音SNR power)，需使用SNR_offset_usage
const int exam_number = 1000; //總模擬次數
const int Max_iteration_usage = 0;// 任何模擬中，達到最大迭代次數的模擬是否捨棄，0為保留，1為捨棄
const double SNR_offset_usage = 0; //控制產生的noise pattern之db不能高於或低於設定的db超過SNR_offset_usage，設定0則不限制


const int random_usage = 1;// 1是使用隨機變數(time32(NULL)),其他數字是使用該數字做為變數種子(固定變數)
const int boxsum_usage = 0;// 1就是使用boxsum,0是使用minsum
const int iteration_output_usage = 0;// SPA,MSA且不做極值化時，加上條件:i>=iteration_output_usage時 才能脫離迭代

const int sumproduct_usage = 1;//1是使用sumproduct,0是使用minsum
const int log_sumproduct_usage = 0; //1是使用對數域的SPA,0是使用機率域的SPA
const int avoid_SPA_any_cycle_usage = 0; //SPA刪除4-cycle->0 6cycle以下->1 8cycle以下->2 10cycle以下->3，不使用請輸入-1

const double alpha = 0.75; // NMSA所使用的alpha值
const int alpha_usage = 1; // 1就是使用NMSA,0就是MSA與boxsum,NMSA = normalized MSA
const int avoid_MSA_any_cycle_usage = -1; //MSA刪除4-cycle->0 6cycle以下->1 8cycle以下->2 10cycle以下->3，不使用請輸入-1

const int avoid_two_cycle_usage = 1; // 1是排除2-cycle(原演算法),0則是還原2-cycle (不是每個算法都有用，需檢查)

double uniform();
double gaussian(double a,int n,double noise_power);       
void gaussian_noise(int* c, double* yi, int n, double noise_power, double SNR, double Rnoise_power);
void gaussian_noise_Minsum_c(double* yi, int n, double noise_power);
double	variance(int n, double* noise_pattern);

void Encode(int *message,int *c,int **G,int n,int m);
int Preprocess(int maxcoldegree, int* maxdegree, int** G_temp, int** H_original, int* return_real_row_num, char filename[99]);
void RCmatrix(int maxcoldegree,int **R,int **C,int n,int m,int **H_original);

double MinSumCAlgorithm(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);
double MinSumCAlgorithm2(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);
double MinSumCAlgorithm_anycycle(double* LLR_Pi1, double** qij1, double** temp_qij1, int m, int** R, int** C, double** rji0, double** temp_rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);

double SumproductAlgorithm(double* Pi, double** qij0, double** qij1, int m, int** R, int** C, double** rji0, double** rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row);
double SumproductAlgorithm2(double* Pi, double** qij0, double** qij1, int m, int** R, int** C, double** rji0, double** rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row);
double SumproductAlgorithm_cycle(double* Pi, double** qij0, double** qij1, double** temp_qij0, double** temp_qij1, int m, int** R, int** C, double** rji0, double** rji1, double** temp_rji0, double** temp_rji1, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* Q1, double* temp_row);

double LogSumproductAlgorithm(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);
double LogSumproductAlgorithm2(double* LLR_Pi1, double** qij1, int m, int** R, int** C, double** rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);
double LogSumproductAlgorithm_anycycle(double* LLR_Pi1, double** qij1, double** temp_qij1, int m, int** R, int** C, double** rji0, double** temp_rji0, int n, int maxdegree, int maxcoldegree, int* c_, int* r_column, int* q_column, double* LQ, double* temp_row);

void minsum1(double* row, double* rji, int maxdegree, int l);
void minsum2(double* row, double* rji, int maxdegree);
void minsum5(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R);

void sumproduct1(double* row, double* rji, int maxdegree);
void sumproduct2(double* row, double* rji, int maxdegree);
int find_parent_index(int level4_index, int n, int m, int** R, int** C, int maxdegree);
void sumproduct3(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R, int** C, int n, int m, double* Pi, int maxcoldegree);

void logsumproduct(double* row, double* rji, int maxdegree);
void logsumproduct_cycle(double* row, double* rji, int maxdegree, int Qnumber, int j, int l, int** R);
