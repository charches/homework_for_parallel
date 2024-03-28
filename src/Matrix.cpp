#include <iostream>
#include <cstdlib>
#include <limits>
#include "../headers/Matrix.h"

using namespace std;

Matrix::Matrix(){}

Matrix::Matrix(const int& nrows, const int& ncols, const string& function)
{
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
}

Matrix::Matrix(const Matrix& other)
{
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
}

Matrix::~Matrix() {
	if (d != nullptr)
		for (int i = 0; i < nr; i++)
			delete[] d[i];
	delete[] d;
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
	if (d != nullptr)
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i][j] = 0;
}

double Matrix::maxi()
{
	double maxi = numeric_limits<double>::lowest();
	if (d != nullptr)
	{
		
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				if (maxi < d[i][j])
					maxi = d[i][j];
	}
	return maxi;
}

double Matrix::mini()
{
	double mini = numeric_limits<double>::max();
	if (d != nullptr)
	{

		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				if (mini > d[i][j])
					mini = d[i][j];
	}
	return mini;
}

Matrix& Matrix::operator=(const Matrix& other)
{
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
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (nr != other.nr || nc != other.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] += other.d[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (nr != other.nr || nc != other.nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i][j] -= other.d[i][j];
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
	return temp;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
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
	return temp;
}

ostream& operator<<(ostream& os, const Matrix& A)
{
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
	return os;
}


