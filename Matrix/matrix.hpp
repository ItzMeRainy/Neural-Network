#pragma once

class Matrix
{
    double* data;
    int rows, cols;

public:
    Matrix();
    Matrix(int rows, int cols, bool randomize = false, double min = -0.5, double max = 0.5);
    Matrix(const Matrix &copyMatrix);
    Matrix(Matrix &&moveMatrix) noexcept;
    ~Matrix();

    Matrix& operator=(const Matrix &copyMatrix);
    Matrix& operator=(Matrix &&moveMatrix) noexcept;

    Matrix operator+(const Matrix &operandMatrix) const;
    Matrix operator-(const Matrix &operandMatrix) const;
    Matrix operator*(const Matrix &operandMatrix) const;
    Matrix operator*(double scalar) const;
    Matrix elementWiseMultiply(const Matrix &operandMatrix) const;
    Matrix transpose() const;

    void applyFunction(double (*func)(double x));
    Matrix mapFunction(double (*func)(double x)) const;

    int getRows() const { return rows; };
    int getCols() const { return cols; };
    double& at(int i, int j) { return data[i*cols + j]; };
    double at(int i, int j) const { return data[i*cols + j]; };

    void print() const;
    void randomize(double min, double max);
};