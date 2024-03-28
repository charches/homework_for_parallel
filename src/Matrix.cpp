#include <iostream>
#include <cstdlib>
#include <limits>
#include "../headers/Matrix.h"
#include "../headers/Func_info.h"

using namespace std;

Matrix::Matrix(){}

Matrix::Matrix(const int& nrows, const int& ncols, const string& function)
{
	Func_info::tick("Matrix::constructor1");
	nr = nrows;
	nc = ncols;
	d = new double* [nr];
	for (int i = 0; i < nr; i++)
		d[i] = new double[nc];
	if (function == "zero")
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i][j] = 0;
	else if (function == "random")
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i][j] = rand() / 100.0;
	Func_info::tick("Matrix::constructor1");	
}

Matrix::Matrix(const Matrix& other)
{
	Func_info::tick("Matrix::copy_constructor");
	if (other.nc * other.nr == 0)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	nr = other.nr;
	nc = other.nc;
	d = new double* [nr];
	for (int i = 0; i < nr; i++)
		d[i] = new double[nc];
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] = other.d[i][j];
	Func_info::tick("Matrix::copy_constructor");
}

Matrix::~Matrix() {
	Func_info::tick("Matrix::destructor");
	if (d != nullptr)
		for (int i = 0; i < nr; i++)
			delete[] d[i];
	delete[] d;
	Func_info::tick("Matrix::destructor");
}

int Matrix::nrows(void) const
{
	return nr;
}

int Matrix::ncols(void) const
{
	return nc;
}

void Matrix::set_zero()
{
	Func_info::tick("Matrix::set_zero");
	if (d != nullptr)
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i][j] = 0;
	Func_info::tick("Matrix::set_zero");
}

double Matrix::maxi()
{
	Func_info::tick("Matrix::maxi");
	double maxi = numeric_limits<double>::lowest();
	if (d != nullptr)
	{
		
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				if (maxi < d[i][j])
					maxi = d[i][j];
	}
	Func_info::tick("Matrix::maxi");
	return maxi;
}

double Matrix::mini()
{
	Func_info::tick("Matrix::mini");
	double mini = numeric_limits<double>::max();
	if (d != nullptr)
	{

		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				if (mini > d[i][j])
					mini = d[i][j];
	}
	Func_info::tick("Matrix::mini");
	return mini;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	Func_info::tick("Matrix::assignment");
	if (d != nullptr)
	{
		for (int i = 0; i < nr; i++)
			delete[] d[i];
		delete[] d;
	}
	nr = other.nr;
	nc = other.nc;
	d = new double* [nr];
	for (int i = 0; i < nr; i++)
		d[i] = new double [nc];
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] = other.d[i][j];
	Func_info::tick("Matrix::assignment");
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	Func_info::tick("Matrix::self_increase");
	if (nr != other.nr || nc != other.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] += other.d[i][j];
	Func_info::tick("Matrix::self_increase");
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	Func_info::tick("Matrix::self_decrease");
	if (nr != other.nr || nc != other.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] -= other.d[i][j];
	Func_info::tick("Matrix::self_decrease");
	return *this;
}

double& Matrix::operator()(const int& r, const int& c)
{
	if (r >= nr || c >= nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	return d[r][c];
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
	Func_info::tick("Matrix_plus");
	if (A.nr != B.nr || A.nc != B.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	int nr = A.nr;
	int nc = A.nc;
	Matrix temp(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nr; j++)
			temp.d[i][j] = A.d[i][j] + B.d[i][j];
	Func_info::tick("Matrix_plus");
	return temp;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
	Func_info::tick("Matrix_minus");
	if (A.nr != B.nr || A.nc != B.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	int nr = A.nr;
	int nc = A.nc;
	Matrix temp(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nr; j++)
			temp.d[i][j] = A.d[i][j] - B.d[i][j];
	Func_info::tick("Matrix_minus");
	return temp;
}

ostream& operator<<(ostream& os, const Matrix& A)
{
	Func_info::tick("print_Matrix");
	if (A.d == nullptr)
	{
		os << "Invalid operation!";
		exit(0);
	}
	for (int i = 0; i < A.nr; i++)
	{
		for (int j = 0; j < A.nc; j++)
			os << A.d[i][j] << " ";
		os << endl;
	}
	os << endl;
	Func_info::tick("print_Matrix");
	return os;
}


