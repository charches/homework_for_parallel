#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdlib>
#include <limits>

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
        ~Matrix();

        int nrows(void) const;
        int ncols(void) const;
        void set_zero();
        double maxi();
        double mini();

        Matrix& operator=(const Matrix& other);
        Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        double& operator()(const int& r, const int& c);
        friend Matrix operator+(const Matrix& A, const Matrix& B);
        friend Matrix operator-(const Matrix& A, const Matrix& B);
        friend Matrix operator*(const Matrix& A, const Matrix& B);
        friend ostream& operator<<(ostream& os, const Matrix& A);
};

#endif
