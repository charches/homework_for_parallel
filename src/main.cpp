#include "../headers/Input.h"
#include "../headers/Matrix.h"
#include "../headers/Func_info.h"

using namespace std;

int main(int argc, char** argv)
{

        #ifdef __MPI
        MPI_Init(&argc, &argv);
        #endif

        Input input("test");
        
        ofstream output_file;
        #ifdef __MPI
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        stringstream ss;
        if (input.prt_mpi_log)
        {
                ss << "result" << rank << ".txt";
        }
        else
        {
                ss << "result.txt";
        }
        string filename = ss.str();
        if (input.prt_mpi_log)
        {
                output_file.open(filename);
                if (output_file.is_open())
                        output_file << "Hello from rank" << rank << endl;
        }
        else
        {
                output_file.open(filename, ios_base::app);
                if (output_file.is_open())
                        output_file << "Hello" << endl;
        }
        #endif

        #ifndef __MPI
        output_file.open("sequential_result.txt");
        if (output_file.is_open())
                output_file << "Hello" << endl;
        #endif

	Matrix A(3, 3, "random"), B(100, 100, "random"), C(1000, 1000, "random");

        output_file << "验证矩阵乘法与cblas给出结果一致：" << endl;
        if (A * A == cblas_times(A, A) && B * B == cblas_times(B, B) && C * C == cblas_times(C, C))
        {
                if (output_file.is_open())
                {
                        output_file << "Same calculation result" << endl;
                }
        }
        if (output_file.is_open())
                output_file << endl;
        
        double d[] = {3.5, 0, 1.5, 
                        0, 3, 0,
                      1.5, 0, 3.5};
        Matrix D(3, 3, d, 9);
        Matrix E(100, 100, "symmetric"), value_d(1, 3), value_e(1, 100);
        Matrix F(1000, 1000, "symmetric"), value_f(1, 1000);

        if (output_file.is_open())
                output_file << "3*3维度矩阵及其对角化：" << endl;

        D.diagonalise(value_d.d);

        if (output_file.is_open())
        {
                output_file << value_d;
                output_file << D;
        }

        E.diagonalise(value_e.d);
        
        F.diagonalise(value_f.d);

	//cout << setw(25) << right << "NAME";
	//cout << setw(10) << right << "CALLS";
	//cout << setw(15) << right << "TIME(Sec)";
	//cout << setw(15) << right << "AVG";
	//cout << setw(16) << right << "PER" << endl;
	//Func_info::screen_timer_print();

        if (output_file.is_open())
        {
                output_file << setw(25) << right << "NAME";
                output_file << setw(10) << right << "CALLS";
                output_file << setw(15) << right << "TIME(Sec)";
                output_file << setw(15) << right << "AVG";
                output_file << setw(16) << right << "PER" << endl;
                Func_info::file_timer_print(output_file);
        }

        #ifdef __MPI
        MPI_Finalize();
        #endif
        return 0;
}

Matrix& append(const double* array, const int& length)