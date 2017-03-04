//Program to perform matrix addition - HPC1 Assignment - 1
//Problem No. - 3, Siddhant S. Aphale, 50164327
//First looping over rows and then columns

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include "timer.h"
#include <papi.h>
#include <ctime>



using namespace std;

int main(int argc,char* argv[])
{

  
  //Input the size of matrix
  int n=10000;
  srand(time(NULL));
  /*long long values[2];
  int PAPI_NUM_EVENTS[] = {PAPI_L1_TCM, PAPI_L2_TCM};*/
  float real_time, proc_time, mflops;
  long long flpops;
  float ireal_time, iproc_time, imflops;
  long long iflpops;
  int retval;
  //std::cout << "Enter the size of matrix a and b" << "\n";
  //  std::cin >> n;
  std::vector<std::vector<double> > a(n, std::vector<double>(n, 0.0));
  std::vector<std::vector<double> > b(n, std::vector<double>(n, 0.0));
  std::vector<std::vector<double> > c(n, std::vector<double>(n, 0.0));
  
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  a[i][j] = rand()%100;
	}
    }
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  b[i][j] = rand()%100;
	}
    }

  if ((retval = PAPI_flops(&ireal_time, &iproc_time, &iflpops, &imflops)) < PAPI_OK)
    {
      std::cout << "Could not initialize PAPI flops \n";
      std::cout << "Your platform may not support floating point operation \n";
      std::cout << "retval : " << retval << "\n";
      return(1);
    }
  
  /*PAPI_library_init(PAPI_VER_CURRENT);
  int w;
  w = PAPI_start_counters(PAPI_NUM_EVENTS, 2);*/


  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  c[i][j] = a[i][j] + b[i][j];
	}
    }

  //PAPI_read_counters(values, 2);

  if ((retval = PAPI_flops(&real_time, &proc_time, &flpops, &mflops)) < PAPI_OK)
    {
      std::cout << "retval : " << retval << "\n";
      return(1);
    }

  ofstream write_flpopsr("rowfpops1.dat");
  assert(write_flpopsr.is_open());
  write_flpopsr << "Real time : " << real_time << "\t" << "Proc time : " << proc_time << "\t" << "Total flpops : " << flpops << "\t" << "MFLOPS : " << mflops << "\n";

  /*ofstream write_cacher("rowcache1.dat");
  assert(write_cacher.is_open());
  write_cacher << "L1 cache miss = " << values[0] << "\n" << "L2 cache miss = " << values[1] << "\n";*/

  return 0;
}






