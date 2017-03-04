//Program to calculate the value of 'pi' using midpoint rule
//HPC-1 Fall-2016 Homework-2 Problem - 4, serial code

#include <iostream>
#include <cmath>
#include "timer.h"
#include <fstream>
#include <cassert>

using namespace std;

int main(int argc, char* argv[])
{
  long long int N = 3000000000;
  double a = 0.0, b = 1.0;
  double pi = 0.0;
  double sum = 0.0;
  timespec before, after, time_diff;
  
  get_time(&before);
  for (int k = 0; k < N; k++)
    {
      sum = sum + ((b - a)/N)*(sqrt(1-pow((a + (k - 0.5)*((b - a)/N)),2)));
    }
  pi = 4*sum;
  get_time(&after);
  diff(&before, &after, &time_diff);

  //Time in seconds
  double time_s = time_diff.tv_sec+(double)(time_diff.tv_nsec)/1.0e9;

  

  ofstream write_serial("piserial.dat");
  //write_serial.setf(std::ios::scientific);
  write_serial.precision(20);
  write_serial << "Value of pi = " << pi << "\n";
  write_serial << "Time required to calculate pi = " << time_s << "\n";
  
  return 0;
}
