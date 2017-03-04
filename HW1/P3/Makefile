all : Run1 Run2 Run3 Run4

Run1: timer.C p3_c_gcc.cpp
	g++ -Wall -o Run1 timer.C p3_c_gcc.cpp
	
Run2 : timer.C p3_c_intel.cpp
	icpc -Wall -o Run2 timer.C p3_c_intel.cpp
	
Run3 : timer.C p3_r_gcc.cpp
	g++ -Wall -o Run3 timer.C p3_r_gcc.cpp
	
Run4 : timer.C p3_r_intel.cpp
	icpc -Wall -o Run4 timer.C p3_r_intel.cpp
	
clean :
	rm *.out Run1 Run2 Run3 Run4
