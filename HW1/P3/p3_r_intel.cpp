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



using namespace std;

int main(int argc,char* argv[])
{

  
  //Input the size of matrix
  int n=20000;
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
  timespec before, after;
  get_time(&before);
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  c[i][j] = a[i][j] + b[i][j];
	}
    }
  get_time(&after);

  timespec time_diff;
  diff(&before, &after, &time_diff);

  // Time in seconds
  double time_s = time_diff.tv_sec + (double)(time_diff.tv_nsec)/1.0e9;

  std::ofstream write_rowintel("Run4.dat");
  assert(write_rowintel.is_open());
  write_rowintel << "Time taken when first looped over row and then column with intel compiler = " << time_s << "\n";

  return 0;
}






