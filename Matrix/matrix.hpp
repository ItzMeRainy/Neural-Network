#pragma once

class matrix
{
    double* data;
    int rows, cols;

public:
    matrix();
    matrix(int rows, int cols, bool randomize = false, double min = -0.5, double max = 0.5);
    matrix(const matrix &copyMatrix);
    matrix(matrix &&moveMatrix) noexcept;
    ~matrix();

    matrix& operator=(const matrix &copyMatrix);
    matrix& operator=(matrix &&moveMatrix) noexcept;

    matrix operator+(const matrix &operandMatrix) const;
    matrix operator*(const matrix &operandMatrix) const;
    matrix operator*(double scalar) const;
    matrix transpose() const;

    void applyFunction(double (*func)(double x));
    matrix mapFunction(double (*func)(double x)) const;

    int getRows() const { return rows; };
    int getCols() const { return cols; };
    double& at(int i, int j) { return data[i*cols + j]; };
    const double& at(int i, int j) const { return data[i*cols + j]; };

    void print() const;
    void randomize(double min, double max);
};