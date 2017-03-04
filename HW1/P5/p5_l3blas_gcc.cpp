//HPC-1 Assignment-1, Problem No. -5
//Program to calcuate matrix matrix multiplication (L3 BLAS Function)
//Aim- To plot the performance

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include "timer.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
  srand(time(NULL)); //randomize the time to generate random numbers for the two matrices
  int a = 11;
  double mul = 1;
  double sum;
  std::vector<int> n(a, 0.0);
  n[0] = 1;
  for (int i = 1; i < a; i++)
    {
      mul = mul*2;
      n[i] = mul;
    }
  
  int p = n.size();
  timespec before, after, time_diff;
  double time_s[p];
  double performance[p];

 
  for (int l = 0; l < p; l++)
    {
      double** A = new double* [n[l]];
      double** B = new double* [n[l]];
      double** C = new double* [n[l]];

      for (int i = 0; i < n[l]; i++)
	{
	  A[i] = new double [n[l]];
	  B[i] = new double [n[l]];
	  C[i] = new double [n[l]];
	}
      for (int i = 0; i < n[l]; i++)
	{
	  for (int j = 0; j < n[l]; j++)
	    {
	      A[i][j] = rand()%10;
	      B[i][j] = rand()%10;
	    }
	}

      /*for (int i = 0; i < n[l]; i++)
	{
	  for (int j = 0; j < n[l]; j++)
	    {
	      std::cout << A[i][j] << " ";
	    }
	  std::cout << "\n";
	}

      for (int i = 0; i < n[l]; i++)
	{
	  for (int j = 0; j < n[l]; j++)
	    {
	      std::cout << B[i][j] << " ";
	    }
	  std::cout << "\n";
	  }*/
      
      get_time(&before);
      for (int i = 0; i < n[l]; i++)
	{
	  for (int j = 0; j < n[l]; j++)
	    {
	      sum = 0;
	      for (int k = 0; k < n[l]; k++)
		{
		  sum = sum+ A[i][k]*B[k][j];
		}
	      C[i][j] = sum;
	    }
	}
  
      get_time(&after);
  
      diff(&before,&after,&time_diff);

      /*for (int i = 0; i < n[l]; i++)
	{
	  for (int j = 0; j < n[l]; j++)
	    {
	      std::cout <<  C[i][j] << " ";
	    }
	  std::cout << "\n";
	  }*/
  
      // Time in seconds
      time_s[l] = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;
      performance[l] = (2*n[l]*n[l]*n[l])/(time_s[l]*pow(10,6));
      
      
      delete [] A;
      delete [] B;
      delete [] C;
    }

  std::ofstream write_l3blas("Run1.dat");
  assert(write_l3blas.is_open());
  for (int i = 0; i < p; i++)
    {
      write_l3blas << (n[i]*n[i]*8) << "\t" << performance[i] << endl;
    }
  return 0;
}
  
