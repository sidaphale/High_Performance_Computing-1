//HPC-1 Assignment-1, Problem No. -4
//Program to calcuate vector vector dot product (MKL Library)
//Aim- To plot the performance
//Code compatible to generate vectors of size 64MBytes = 65536 kBytes with n = 24 (n = 1, vector size = 8 bytes, n = 2, vector size = 16 bytes....n = 24, vector size = 67108864 bytes)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "timer.h"
#include <fstream>
#include <cmath>
#include "mkl.h"
#include <cassert>


using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL)); //randomize the time to generate random numbers for the vectors
	int n = 10000000;
	double *a, *b;
	double c, performance;
	
	std::ofstream write_mkl("Run4.dat");
	assert(write_mkl.is_open());

	for (int k=1; k<n; k=2*k)
	{
		a=new double [k];
		b=new double [k];
		for (int i=0; i<k; i++)
		{
			a[i]= rand()%10;
			b[i]= rand()%10;
		}
		timespec before, after, time_diff;
		get_time(&before);
		c=cblas_ddot(k,a,1,b,1);
		
		get_time(&after);
		diff(&before,&after,&time_diff);
	
		double time_s = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;
		performance = 2*k/(time_s*1000000);
		
		write_mkl << (k*8) << "\t" << performance << endl;
	}

	delete [] a;
	delete [] b;
        	
	return 0;

}
      

