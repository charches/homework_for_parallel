#include "../headers/Matrix.h"
#include "../headers/Func_info.h"
#include "cblas.h"
#include "lapacke.h"

using namespace std;

Matrix::Matrix(){}

Matrix::Matrix(const int& nrows, const int& ncols, const string& function)
{
	Func_info::tick("Matrix::constructor1");
	nr = nrows;
	nc = ncols;
	d = new double [nr * nc];
	if (function == "zero")
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i * nr + j] = 0;
	else if (function == "random")
		for (int i = 0; i < nr; i++)
			for (int j = 0; j < nc; j++)
				d[i * nr + j] = rand() / 100.0;
	else if (function == "symmetric")
	{
		if (nr != nc)
		{
			cout << "Invalid operation!";
			exit(0);
		}
		else
		{
			for (int i = 0; i < nr; i++)
				for (int j = 0; j <= i; j++)
					{
						d[i * nr + j] = rand() / 100.0;
						d[j * nr + i] =  d[i * nr + j];
					}
		}
	}
	Func_info::tick("Matrix::constructor1");	
}

Matrix::Matrix(const int& nrows, const int& ncols, const double* array, const int& length)
{
	Func_info::tick("Matrix::constructor2");
	if (length > nrows * ncols)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	nr = nrows;
	nc = ncols;
	d = new double [nr * nc];
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
		{
			if (i * nr + j >= length)
				d[i * nr + j] = 0;
			else
				d[i * nr + j] = array[i * nr + j];
				
		}
	Func_info::tick("Matrix::constructor2");
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
	d = new double [nr * nc];
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i * nr + j] = other.d[i * nr + j];
	Func_info::tick("Matrix::copy_constructor");
}

Matrix::~Matrix() {
	Func_info::tick("Matrix::destructor");
	if (d != nullptr)
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
				d[i * nr + j] = 0;
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
				if (maxi < d[i * nr + j])
					maxi = d[i * nr + j];
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
				if (mini > d[i * nr + j])
					mini = d[i * nr + j];
	}
	Func_info::tick("Matrix::mini");
	return mini;
}

Matrix Matrix::transpos()
{
	Matrix temp(nc, nr);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
				temp(j, i) = (*this)(i, j);
	return temp;
}

bool operator==(const Matrix& A, const Matrix& B)
{
	Func_info::tick("Matrix_is_equal");
	if (A.nr != B.nr || A.nc != B.nc)
	{
		Func_info::tick("Matrix_is_equal");
		return false;
	}
	for (int i = 0; i < A.nr; i++)
		for (int j = 0; j < A.nc; j++)
			if (A(i, j) != B(i, j))
			{
				Func_info::tick("Matrix_is_equal");
				return false;
			}
	Func_info::tick("Matrix_is_equal");
	return true;
}

Matrix& Matrix::operator=(const Matrix& other)
{
	Func_info::tick("Matrix::assignment");
	if (d != nullptr)
	{
		delete[] d;
	}
	nr = other.nr;
	nc = other.nc;
	d = new double [nr * nc];
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			d[i * nr + j] = other.d[i * nr + j];
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
			d[i * nr + j] += other.d[i * nr + j];
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
			d[i * nr + j] -= other.d[i * nr + j];
	Func_info::tick("Matrix::self_decrease");
	return *this;
}

double& Matrix::operator()(const int& r, const int& c) const
{
	if (r >= nr || c >= nc)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	return d[r * nr + c];
}

bool Matrix::is_sym()
{
	Func_info::tick("Matrix::is_sym");
	if(nr != nc)
	{
		Func_info::tick("Matrix::is_sym");
		return false;
	}
	else 
	{
		for (int i = 0; i < nr; i++)
			for (int j = 0; j <= i; j++)
				if(d[i * nr + j] != d[j * nr + i])
				{
					Func_info::tick("Matrix::is_sym");
					return false;
				}
		Func_info::tick("Matrix::is_sym");
		return true;
	}
}

void Matrix::diagonalise(double* eigenvalue)//Input:an array to storage eigenvalue
{
	Func_info::tick("Matrix::diagonalise");
	if(!is_sym())
	{
		cout << "Invalid operation!";
		exit(0);
	}
	lapack_int info;
	info = LAPACKE_dsyev(LAPACK_ROW_MAJOR, 'V', 'U', nr, d, nr, eigenvalue);
	if (info)
	{
		cout << "Calculation failed!";
		exit(0);
	}
	Func_info::tick("Matrix::diagonalise");

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
			temp.d[i * nr + j] = A.d[i * nr + j] + B.d[i * nr + j];
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
			temp.d[i * nr + j] = A.d[i * nr + j] + B.d[i * nr + j];
	Func_info::tick("Matrix_minus");
	return temp;
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
	Func_info::tick("Matrix_times");
	if (A.nc != B.nr)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	int nr = A.nr;
	int nc = B.nc;
	Matrix temp(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			for (int k = 0; k < A.nc; k++)
				temp.d[i * nr + j] += A.d[i * A.nr + k] * B.d[k * B.nr + j];
	Func_info::tick("Matrix_times");
	return temp;
	
}

Matrix cblas_times(const Matrix& A, const Matrix &B)//Input:two matrixs, A is a m*n matrix and B is a n*r matrix
{
	Func_info::tick("cblas_times");
	if (A.nc != B.nr)
	{
		cout << "Invalid operation!";
		exit(0);
	}
	int nr = A.nr;
	int nc = B.nc;
	Matrix temp(nr, nc);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nr, nc, A.nc, 1, A.d, A.nc, B.d, B.nc, 0, temp.d, temp.nc);
	Func_info::tick("cblas_times");
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
			os << setw(15) << A.d[i * A.nr + j] << " ";
		os << endl;
	}
	os << endl;
	Func_info::tick("print_Matrix");
	return os;
}


