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

	Matrix A(3, 3), B(3, 3, "random"), C(B);
        cout << "三个矩阵分别为：" << endl;
        cout << A << B << C << endl;

        cout << "输出行数列数:" << endl;
        cout << A.nrows() << " " << A.ncols() << endl << endl;

        cout << "置于0：" << endl;
        C.set_zero();
        cout << C;

        cout << "求最大最小值：" << endl;
        cout << B.maxi() << " " << B.mini() << endl << endl;

        cout << "赋值：" << endl;
        C = B;
        cout << C;

        cout << "加法减法：" << endl;
        B += C;
        cout << B;
        B -= C;
        cout << B;
        cout << B + C;
        cout << B - C;

        cout << "直接读取元素：" << endl;
        cout << B(1, 2) << endl << endl;

	cout << setw(25) << right << "NAME";
	cout << setw(10) << right << "CALLS";
	cout << setw(15) << right << "TIME(Sec)";
	cout << setw(15) << right << "AVG";
	cout << setw(16) << right << "PER" << endl;
	Func_info::timer_print();
        return 0;
}
