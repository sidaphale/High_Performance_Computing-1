//Program to calculate the value of 'pi' using midpoint rule
//HPC-1 Fall-2016 Homework-2 Problem - 4, OpenMP Dynamic Scheduling

#include <iostream>
#include <cmath>
#include "timer.h"
#include <fstream>
#include <cassert>
#include <omp.h>
#include <ctime>


int main(int argc, char* argv[])
{
  long long int N = 1000000000;
  double a = 0.0, b = 1.0;
  double pi = 0.0;
  double sum;
  int k, tid=0;
  timespec before, after, time_diff;
  double time_s[12];

  for (int p = 0; p < 12; p++)
    {
      omp_set_num_threads(p);
  
  get_time(&before);
  
  sum = 0.0;
#pragma omp parallel for shared(a,b,N) private(k, tid) schedule(dynamic, 10000) reduction(+:sum)
  
    //#pragma omp for schedule(static) reduction(+:sum)
  for (k = 0; k < N; k++)
    {
      //tid = omp_get_thread_num();
      sum = sum + ((b - a)/N)*(sqrt(1-pow((a + (k - 0.5)*((b - a)/N)),2)));
      /*if (tid==0)
	{
	  std::cout << "thread = " << tid << ",k = " << k << "\n";
	}*/
    }
  
  pi = 4*sum;

 get_time(&after);
 diff(&before, &after, &time_diff);

  //Time in seconds
  time_s[p] = time_diff.tv_sec+(double)(time_diff.tv_nsec)/1.0e9;
  std::cout <<  "\npi: " << pi << "\n";
    }

  

  std::ofstream write_dynamic("dynamic.dat");
  write_dynamic.precision(20);
  for (int i = 0; i < 12; i++)
    { 
      write_dynamic << i << "\t" << time_s[i] << "\n";
    }
  
  return 0;
}
