vpath %.cpp ./src
vpath %.h ./headers

main.exe:main.o Matrix.o Input.o Func.o Func_info.o
	g++ -o main.exe $^ -llapack -llapacke -lcblas -lrefblas -lgfortran
main.o:main.cpp Matrix.h Input.h Func_info.h Func.h
	g++ -c $< -o main.o
Matrix.o:Matrix.cpp Matrix.h Func_info.h Func.h
	g++ -c $< -o Matrix.o
Input.o:Input.cpp Input.h Func_info.h Func.h
	g++ -c $< -o Input.o
Func.o:Func.cpp Func.h Func_info.h
	g++ -c $< -o Func.o
Func_info.o:Func_info.cpp Func.h Func_info.h
	g++ -c $< -o Func_info.o

.PHONY:clear
clear:
	rm -f *.o *.exe
