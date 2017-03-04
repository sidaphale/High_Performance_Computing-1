all : Run1 Run2 Run3

Run1 : timer.C p5_l3blas_gcc.cpp
	g++ -Wall  -o Run1 timer.C p5_l3blas_gcc.cpp
	
Run2 : timer.C p5_l3blas_intel.cpp
	icpc -Wall  -o Run2 timer.C p5_l3blas_intel.cpp
	
Run3 : timer.C p5_dgemm.cpp
	icpc -Wall  -o Run3 timer.C p5_dgemm.cpp -mkl

	
clean : 
	*.o *.out Run1 Run2 Run3
