#include <iostream>
#include "../headers/Input.h"
#include "../headers/Matrix.h"
#include "../headers/Func_info.h"
#include <iomanip>

using namespace std;

int main()
{
        string filename;
        cin >> filename;
        Input input(filename);
        cout << input << endl;

	Matrix A(3, 3, "random"), B(100, 100, "random"), C(1000, 1000, "random");

        if (A * A == cblas_times(A, A))
                cout << "Same calculation result" << endl;
        if (B * B == cblas_times(B, B))
                cout << "Same calculation result" << endl;
        if (C * C == cblas_times(C, C))
                cout << "Same calculation result" << endl;

	cout << setw(25) << right << "NAME";
	cout << setw(10) << right << "CALLS";
	cout << setw(15) << right << "TIME(Sec)";
	cout << setw(15) << right << "AVG";
	cout << setw(16) << right << "PER" << endl;
	Func_info::timer_print();
        return 0;
}
