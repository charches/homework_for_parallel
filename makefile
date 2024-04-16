vpath %.cpp ./src
vpath %.h ./headers

MPI = 1#0是串行编译，1是并行编译

ifeq ($(MPI), 1)
	CXX = mpicxx
	CXXFLAGS = -D__MPI
else
	CXX = g++
	CXXFLAGS =
endif 


main.exe:main.o Matrix.o Input.o Func.o Func_info.o
	$(CXX) -o main.exe $^ -llapacke -llapack -lcblas -lrefblas -lgfortran
main.o:main.cpp Matrix.h Input.h Func_info.h Func.h
	$(CXX) $(CXXFLAGS) -c $< -o main.o
Matrix.o:Matrix.cpp Matrix.h Func_info.h Func.h
	$(CXX) $(CXXFLAGS) -c $< -o Matrix.o
Input.o:Input.cpp Input.h Func_info.h Func.h
	$(CXX) $(CXXFLAGS) -c $< -o Input.o
Func.o:Func.cpp Func.h Func_info.h
	$(CXX) $(CXXFLAGS) -c $< -o Func.o
Func_info.o:Func_info.cpp Func.h Func_info.h
	$(CXX) $(CXXFLAGS) -c $< -o Func_info.o

.PHONY:clear
clear:
	rm -f *.o *.exe
