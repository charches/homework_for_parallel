#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <limits>
#include "cblas.h"
#include "lapacke.h"
#include <iomanip>

using namespace std;

class Matrix {
private:
        int nr = 0;
        int nc = 0;
public:
        double* d = nullptr;

        Matrix();
        Matrix(const int& nrows, const int& ncols, const string& function = "zero");
        Matrix(const Matrix& other);
        Matrix(const int& nrows, const int& ncols, const double* array, const int& length);
        ~Matrix();

        int nrows(void) const;
        int ncols(void) const;
        void set_zero();
        double maxi();
        double mini();
        void diagonalise(double* eigenvalue);
        bool is_sym();
        Matrix transpos();
        
        Matrix& operator=(const Matrix& other);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        double& operator()(const int& r, const int& c) const;
        friend bool operator==(const Matrix& A, const Matrix& B);
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend Matrix cblas_times(const Matrix& A, const Matrix &B);
        friend ostream& operator<<(ostream& os, const Matrix& A);
};

#endif
