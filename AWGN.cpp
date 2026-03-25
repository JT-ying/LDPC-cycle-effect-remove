#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Configuration.h"
//**********************************高斯雜訊***************************************
   //X=0
   //for i = 1 to N
   //   U = uniform()
   //   X = X + U
   //end
	
   /* for uniform randoms in [0,1], mu = 0.5 and var = 1/12 */
   /* adjust X so mu = 0 and var = 1 */
	
   //X = X - N/2                /* set mean to 0 */
   //X = X * sqrt(12 / N)       /* adjust variance to 1 */

   //When the algorithm finishes, X will be our unit normal random. 
   //X can be further modified to have a particular mean and variance,

   // e.g.: X' = mean + sqrt(variance) * X

   //The drawback to this method is that X will be in the range [-N, N], 
   //instead of (-Infinity, Infinity) and if the calls to uniform are not truly independent,
   //then the noise will no longer be white. 
   //Jeruchim, et. al., recommend N >= 20 for good results.
 //********************************************************************************
double uniform()
{
	double u;
	u = rand();
	u = u/RAND_MAX;
	return(u);
}
double gaussian(double a,int n,double noise_power)//a = mean , d = dev(variance開根號) , n = block length
{
	//standard normal distribution
	double U,X=0,X_,S;
	int i;	
	//double variance = gau_dev * gau_dev;
	for(i=0;i<n;i++)
	{
		U = uniform();
		X = X + U;
	}
	X = X - n/2;//adjust X so that mean = 0;
	S = sqrt(12 / (double)n);// adjust S so that var = 1;
	X = X * S;
	//normal distribution with the zero mean and variance
	X_ = a + ( sqrt(noise_power) * X );
	return(X_);
}
double	variance(int n,double* noise_pattern)
{	
	int i;
	double E=0;
	double var=0;
	for (i = 0; i < n; i++)
		E += noise_pattern[i];
	E = E / n;
	for (i = 0; i < n; i++)
		var += pow(noise_pattern[i]-E,2);
	var = var / n;
	return(var);
}
void gaussian_noise(int *c,double *yi,int n,double noise_power,double SNR,double Rnoise_power)
{	
	int i;
	int modulation;
	double* noise_pattern;
	noise_pattern = new double[n];
	double var;
	double noise_db;
	double j;
	int db_check = 0;
	while (db_check == 0 && SNR_offset_usage!=0)
	{
		for (i = 0; i < n; i++)
		{
			//BPSK調變
			if (c[i] == 0)
				modulation = 1;
			else modulation = -1;
			noise_pattern[i] = gaussian(0, n, noise_power);
			yi[i] = modulation + noise_pattern[i];
		}
		Rnoise_power = variance(n, noise_pattern);
		noise_db = 10 * log10(1 / Rnoise_power);
		if (fabs(SNR - noise_db) < SNR_offset_usage)
			db_check = 1;
	}
	if (SNR_offset_usage == 0)
	{
		for (i = 0; i < n; i++)
		{
			//BPSK調變
			if (c[i] == 0)
				modulation = 1;
			else modulation = -1;
			noise_pattern[i] = gaussian(0, n, noise_power);
			yi[i] = modulation + noise_pattern[i];
		}
		if (noise_estimation_errors_usage == 0)
			Rnoise_power = variance(n, noise_pattern);
	}
}
void gaussian_noise_Minsum_c(double *yi,int n,double noise_power)
{
	int i;
	for (i=0;i<n;i++)
		yi[i] = yi[i]*2/noise_power;
}