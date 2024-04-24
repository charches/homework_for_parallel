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

        #ifndef __MPI
        int n, m;
        cin >> n >> m;
        Matrix A(n, m), B(n, m);
        cin >> A >> B;
        output_file << A + B;
        #endif

        #ifdef __MPI
        int size = 0;
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        MPI_Status status;
        
        if (rank == 0)
        {
                int n, m;
                cin >> n >> m;
                Matrix A(n, m), B(n, m);
                cin >> A >> B;
                int row_num = max(n / (size - 1), 1);
                int pos = 0;
                for (int i = 1; i < size; i++)
                {
                        MPI_Send(&n, 1, MPI_INT, i, 99, MPI_COMM_WORLD);
                        MPI_Send(&m, 1, MPI_INT, i, 99, MPI_COMM_WORLD);
                        MPI_Send(&row_num, 1, MPI_INT, i, 99, MPI_COMM_WORLD);
                }
                for (int i = 1; i < min(size, n + 1); i++)
                {
                        if (i < size - 1)
                        {
                                MPI_Send(A.d + pos, row_num * m, MPI_DOUBLE, i, 99, MPI_COMM_WORLD);
                                MPI_Send(B.d + pos, row_num * m, MPI_DOUBLE, i, 99, MPI_COMM_WORLD);
                                pos += row_num * m;
                        }
                        else
                        {
                                
                                MPI_Send(A.d + pos, m * n - pos, MPI_DOUBLE, i, 99, MPI_COMM_WORLD);
                                MPI_Send(B.d + pos, m * n - pos, MPI_DOUBLE, i, 99, MPI_COMM_WORLD);
                        }

                }
                Matrix C(n, m);
                pos = 0;
                for (int i = 1; i < min(size, n + 1); i++)
                {
                        if (i < min(size - 1, n))
                        {
                                MPI_Recv(C.d + pos, row_num * m, MPI_DOUBLE, i, 99, MPI_COMM_WORLD, &status);
                                
                                pos += row_num * m;
                        }
                        else
                        {
                                MPI_Recv(C.d + pos, m*n - pos, MPI_DOUBLE, i, 99, MPI_COMM_WORLD, &status);
                        }
                }
                output_file << C;
                int sig = 1;
                for (int i = 1; i < size; i++)
                {
                        MPI_Send(&sig, 1, MPI_INT, i, 99, MPI_COMM_WORLD);
                }
        }
        else
        {
                int n, m, row_num;
                MPI_Recv(&n, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
                MPI_Recv(&m, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
                MPI_Recv(&row_num, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
                double* a = new double[m * n];
                double* b = new double[n * m];
                double* c = new double[n * m];
                
                if (rank < min(size - 1, n))
                {
                        MPI_Recv(a, row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD, &status);
                        MPI_Recv(b, row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD, &status);
                        for (int i = 0; i < row_num * m; i++)
                                c[i] = a[i] + b[i];
                        MPI_Send(c, row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
                }
                else if(rank == min(size - 1, n))
                {
                        MPI_Recv(a, m * n - (min(size - 1, n) - 1) * row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD, &status);
                        MPI_Recv(b, m * n - (min(size - 1, n) - 1) * row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD, &status);
                        for (int i = 0; i < m * n - (min(size - 1, n) - 1) * row_num * m; i++)
                                c[i] = a[i] + b[i];
                        MPI_Send(c, m * n - (min(size - 1, n) - 1) * row_num * m, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD);
                }
                int sig = 1;
                MPI_Recv(&sig, 1, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
                delete []a;
                delete []b;
                delete []c;
        }
        #endif

        if (output_file.is_open())
        {
                #ifdef __MPI
                if (rank == 0)
                {
                        output_file << setw(25) << right << "NAME";
                        output_file << setw(10) << right << "CALLS";
                        output_file << setw(15) << right << "TIME(Sec)";
                        output_file << setw(15) << right << "AVG";
                        output_file << setw(16) << right << "PER" << endl;
                        Func_info::file_timer_print(output_file);
                }
                #endif
                #ifndef __MPI
                output_file << setw(25) << right << "NAME";
                output_file << setw(10) << right << "CALLS";
                output_file << setw(15) << right << "TIME(Sec)";
                output_file << setw(15) << right << "AVG";
                output_file << setw(16) << right << "PER" << endl;
                Func_info::file_timer_print(output_file);
                #endif
        }

        #ifdef __MPI
        MPI_Finalize();
        #endif
        return 0;
}