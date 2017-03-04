//HPC-1, Assignment 2, Siddhant S. Aphale, Person # 50164327
//Program to verify the Goldbach Conjecture - Serial code

#include <iostream>
#include <cmath>
#include <vector>
#include "timer.h"
#include <cassert>
#include <fstream>
#include <cstdlib>
#include <papi.h>

using namespace std;

//Function to check prime number
bool is_prime(int n);

int main(int argc, char* argv[])
{
  //Various number ranges to be checked for
  vector<int> N{5000000};
  
  vector<double> time_s(N.size(), 0.0);
  

  for (int l = 0; l < N.size(); l++)
    {
      int p = 0;
      /*float real_time, proc_time, mflops;
      long long flpops;
      float ireal_time, iproc_time, imflops;
      long long iflpops;
      int retval;*/
      long long values[2];
      int PAPI_events[] = {PAPI_L1_TCM, PAPI_L2_TCM};
	int w;
      int a = 0;
      int p_1 = 0, p_2 = 0;
      timespec before, after, time_diff;
      /*if ((retval = PAPI_flops(&ireal_time, &iproc_time, &iflpops, &imflops)) < PAPI_OK)
	{
	  std::cout << "Could not initialize PAPI_flops \n";
	  std::cout << "retval : " << retval << "\n";
	  return(1);
	}*/
      get_time(&before);
      PAPI_library_init(PAPI_VER_CURRENT);
	w = PAPI_start_counters(PAPI_events, 2);
      for (long int i = 2; i <= N[l]/2; i++)
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

      /*if ((retval=PAPI_flops(&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
	{
	  std::cout << "retval : " << retval << "\n";
	  return(1);
	}*/
      PAPI_read_counters(values, 2);
      
      diff(&before,&after,&time_diff);

      // Time in seconds
      time_s[l] = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;
      cout << time_s[l] << "\n";
      cout << "L1 cache misses = " << values[0] << "\n" << "L2 cache misses = " << values[1] << "\n";
      //std::cout << "Real time : " << real_time << "\tProc time : " << proc_time << "\tTotal flpops : " << flpops << "\tMFLOPS : " << mflops << "\n";
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
