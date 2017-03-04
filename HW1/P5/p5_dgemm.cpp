#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <vector>
#include <fstream>
#include "mkl.h"
#include <ctime>
#include "timer.h"

using namespace std;

int main(int argc, char* argv[])
{
  srand(time(NULL));
  int a = 11;
  double mul = 1;
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
      int m, q, s, alpha, beta, i, j;
      m = n[l];
      q = n[l];
      s = n[l];
      alpha = 1; beta = 0;

      for (i = 0; i < n[l]; i++)
	{
	  A[i] = new double [n[l]];
	  B[i] = new double [n[l]];
	  C[i] = new double [n[l]];
	}

      double* D = new double[n[l]*n[l]];
      double* E = new double[n[l]*n[l]];
      double* F = new double[n[l]*n[l]];

      for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      A[i][j] = rand()%10;
	      B[i][j] = rand()%10;
	    }
	}

      /*for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      std::cout << "A = " << A[i][j] << " ";
	    }
	  std::cout << "\n";
	}

      for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      std::cout << "B = " << B[i][j] << " ";
	    }
	  std::cout << "\n";
	}

      for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      D[i*n[l]+j] = A[i][j];
	      E[i*n[l]+j] = B[i][j];
	    }
	    }*/

      get_time(&before);
      cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, q, s, alpha, D, s, E, q, beta, F, q);
      get_time(&after);

      diff(&before,&after,&time_diff);
      // Time in seconds
      time_s[l] = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;
      performance[l] = (2*n[l]*n[l]*n[l])/(time_s[l]*pow(10,6));

      for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      C[i][j] = F[i*n[l]+j];
	    }
	}

      /*for (i = 0; i < n[l]; i++)
	{
	  for (j = 0; j < n[l]; j++)
	    {
	      std::cout << "C = " <<  C[i][j] << " ";
	    }
	  std::cout << "\n";
	  }*/

      delete [] A;
      delete [] B;
      delete [] C;
      delete [] D;
      delete [] E;
      delete [] F;
    }

  std::ofstream write_dgemm("Run3.dat");
  assert(write_dgemm.is_open());
  for (int i = 0; i < p; i++)
    {
      write_dgemm << (n[i]*n[i]*8) << "\t" <<  performance[i] << endl;
    }

  return 0;
}



      
  
  







