/*HPC-1, Fall-2016, Assignment-3, Siddhant S. Aphale, Person # - 50164327
 MPI Program to estimate the value of Pi using Midpoint Rule
 Study of Strong and Weak Scaling*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <mpi.h>
#include <sstream>

int main(int argc, char* argv[])
{
  long long int N = 10e9;
  long long int start, end, r;
  double a = 0.0, b = 1.0;
  double dx, f, x;
  double pi;
  double sum = 0.0, global_sum=0.0;
  int nproc, my_proc, ierr;
  double t1, t2;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_proc);

  t1 = MPI_Wtime();
  start = (N/nproc)*my_proc;
  end = (N/nproc)*(my_proc+1);
  dx = (b-a)/(N-1);
  for (long int k = start; k <= end; k++)
    {
      x = ((k*dx + (k-1)*dx)*double(0.5));
      f = 4.0/(1 + x*x);
      sum += dx*f;
    }

  ierr = MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  t2 = MPI_Wtime() - t1;

  pi = global_sum;


  MPI_Finalize();

  if (my_proc==0)
    {
      std::cout << "MPI code with tasks = " << nproc << "\n";
      std::cout << "Number of divisions = " << N << "\n";

      std::string data2 = "nproc";
      std::ofstream write_pi;
      std::stringstream p2;
      p2 << nproc;

      std::string dataname = "write_pi"+p2.str()+".dat";
      write_pi.open(dataname.c_str());
      write_pi << nproc << "\t" << t2;
      write_pi.close();
      p2.str("");

      std::cout << "pi = " << pi << "\n";
      std::cout << "time = " << t2 << "\n";

      std::string data1 = "t2";
      std::ofstream write_time;
      std::stringstream p1;
      p1 << nproc;

      std::string dataname1 = "write_time"+p1.str()+".dat";
      write_time.open(dataname1.c_str());
      write_time << t2;
      write_time.close();
      p1.str("");
    }
      
  
  return 0;
}
