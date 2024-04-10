#include "../headers/Input.h"
#include "../headers/Matrix.h"
#include "../headers/Func_info.h"

using namespace std;

int main()
{
        string filename;
        cin >> filename;
        Input input(filename);
        cout << input << endl;

	Matrix A(3, 3, "random"), B(100, 100, "random"), C(1000, 1000, "random");

        cout << "验证矩阵乘法与cblas给出结果一致：" << endl;
        if (A * A == cblas_times(A, A))
                cout << "Same calculation result" << endl;
        if (B * B == cblas_times(B, B))
                cout << "Same calculation result" << endl;
        if (C * C == cblas_times(C, C))
                cout << "Same calculation result" << endl;
        cout << endl;
        
        


        double d[] = {3.5, 0, 1.5, 
                        0, 3, 0,
                      1.5, 0, 3.5};
        Matrix D(3, 3, d, 9);
        Matrix E(100, 100, "symmetric"), value_d(1, 3), value_e(1, 100);
        Matrix F(1000, 1000, "symmetric"), value_f(1, 1000);
        cout << "3*3维度矩阵及其对角化：" << endl;
        D.diagonalise(value_d.d);
        cout << value_d;
        cout << D;
        //cout << "100*100维度矩阵及其对角化：" << endl;
        E.diagonalise(value_e.d);
        //cout << value_e;
        //cout << E;
        //cout << "1000*1000维度矩阵及其对角化：" << endl;
        F.diagonalise(value_f.d);
        //cout << value_f;
        //cout << F;

	cout << setw(25) << right << "NAME";
	cout << setw(10) << right << "CALLS";
	cout << setw(15) << right << "TIME(Sec)";
	cout << setw(15) << right << "AVG";
	cout << setw(16) << right << "PER" << endl;
	Func_info::timer_print();
        return 0;
}
