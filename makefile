vpath %.cpp ./src
vpath %.h ./headers

main.exe:main.o Matrix.o Input.o
	g++ -o main.exe $^
main.o:main.cpp Matrix.h Input.h
	g++ -c $< -o main.o
Matrix.o:Matrix.cpp Matrix.h
	g++ -c $< -o Matrix.o
Input.o:Input.cpp Input.h
	g++ -c $< -o Input.o

.PHONY:clear
clear:
	rm -f *.o *.exe
