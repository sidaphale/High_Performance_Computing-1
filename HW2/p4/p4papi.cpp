//Program to calculate the value of 'pi' using midpoint rule
//HPC-1 Fall-2016 Homework-2 Problem - 4, serial code, performance check using PAPI

#include <iostream>
#include <cmath>
#include <papi.h>
#include <fstream>
#include <cassert>


using namespace std;

int main(int argc, char* argv[])
{
  long long int N = 3000000000;
  double a = 0.0, b = 1.0;
  double pi = 0.0;
  double sum = 0.0;
  /*int retval;
  float real_time, proc_time, mflops;
  long long flpops;
  float ireal_time, iproc_time, imflops;
  long long iflpops;*/
  
  int PAPI_events[] =  {PAPI_L1_TCM, PAPI_L2_TCM};
  long long values[2];

  /*if ((retval = PAPI_flops(&ireal_time, &iproc_time, &iflpops, &imflops)) < PAPI_OK)
    {
      cout << "Could not initialize PAPI Flops \n";
      cout << "Your platform may not support floating point operation \n";
      cout << "retval : " << retval << "\n";
      return(1);
      }*/

  PAPI_library_init(PAPI_VER_CURRENT);
  int w;
  w = PAPI_start_counters(PAPI_events, 2);
  
  for (int k = 0; k < N; k++)
    {
      sum = sum + ((b - a)/N)*(sqrt(1-pow((a + (k - 0.5)*((b - a)/N)),2)));
    }
  pi = 4*sum;

  PAPI_read_counters(values, 2);
  //std::cout << "L1 cache misses = " << values[1] << "\n";
  //std::cout << "L2 cache misses = " << values[0] << "\n";
  //cout << "Total floating point operations = " << values[3] << "\n";

  /*if ((retval = PAPI_flops(&real_time, &proc_time, &flpops, &mflops)) < PAPI_OK)
    {
      cout << "retval : " << retval << "\n";
     }*/
  

  /*ofstream write_serialperf("piperf_serial.dat");
  assert(write_serialperf.is_open());
  write_serialperf.precision(20);
  write_serialperf << "Value of pi = " << pi << "\n";
  write_serialperf << "Real time : " << real_time << "\t" << "Proc time : " << proc_time << "\t" << "Total flpops : " << flpops << "\t" << "MFLOPS : " << mflops << "\n";*/

  ofstream write_serialtcm("pitcm_serial3.dat");
  assert(write_serialtcm.is_open());
  write_serialtcm.precision(20);
  write_serialtcm << "L1 cache misses = " << values[0] << "\n";
  write_serialtcm << "L2 cache misses = " << values[1] << "\n";
  
  
  return 0;
}
