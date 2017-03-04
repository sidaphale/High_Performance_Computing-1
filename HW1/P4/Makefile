all : Run1 Run2 Run3

Run1 : timer.C p4_blas_gcc.cpp
	g++ -Wall  -o Run1 timer.C p4_blas_gcc.cpp
	
Run2 : timer.C p4_blas_intel.cpp
	icpc -Wall  -o Run2 timer.C p4_blas_intel.cpp
	
Run3 : timer.C p4_cblas.cpp
	g++ -Wall  -I/util/common/octave/OpenBLAS-0.2.14/lib/ -L/util/common/octave/OpenBLAS-0.2.14/lib/ timer.C p4_cblas.cpp -lopenblas -o Run3
	
clean :
	rm *.out Run1 Run2 Run3
