//HPC-1, Assignment 2, Siddhant S. Aphale, Person # 50164327
//Program to verify the Goldbach Conjecture - OpenMP Dynamic Scheduling

#include <iostream>
#include <cmath>
#include <vector>
#include "timer.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <omp.h>



//Function to check prime number
bool is_prime(int n);

int main(int argc, char* argv[])
{
  //Various number ranges to be checked for
  std::vector<int> N{1000000};
  
  std::vector<double> time_s(16, 0.0);
  

  for (int l = 0; l < N.size(); l++)
    {
      int i;
      int a = 0;
      int p_1 = 0, p_2 = 0;
      timespec before, after, time_diff;
      for (int t = 0; t < 16; t++)
	{
	  int p = 0.0;
	  omp_set_num_threads(t);
	  get_time(&before);
#pragma omp parallel for private(i) reduction(+:p) schedule(dynamic, 10000)
	  for (i = 2; i <= N[l]/2; i++)
	    {
	      if (is_prime(i))
		{
		  if(is_prime(N[l]-i))
		    {
		      a = i + (N[l]-i);
		      if (a == N[l])
			{
			  p += 1;
			  p_1 = i;
			  p_2 = N[l] - i;
			  //cout << "Goldbach conjecture true for " << p_1 << "and " << p_2 << "\n";
			}
		    }
		}
	    }
	  get_time(&after);
	  
	  
	  diff(&before,&after,&time_diff);
	  
	  // Time in seconds
	  time_s[t] = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;
	}

      std::ofstream write_dynamic("dynamic.dat");
      write_dynamic.precision(20);
      for (int i = 0; i <16; i++)
	{
	  write_dynamic << i << "\t" << time_s[i] << "\n";
	}
      
    }

  return 0;
}


  

bool is_prime(int n)
{
  bool prime;

  prime = true;
  for (int i = 2; i < n/2; i++)
    {
      if (n%i == 0)
	{
	  prime = false;
	  break;
	}
    }
  return prime;
}
