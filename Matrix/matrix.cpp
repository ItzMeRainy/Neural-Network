#include "matrix.hpp"
#include <iostream>
#include <random>

matrix::matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}

matrix::matrix(int rows, int cols, bool randomize = false, double min = -0.5, double max = 0.5)
{
    this->rows = rows;
    this->cols = cols;
    data = new double[rows * cols];

    if (randomize)
        this->randomize(min, max);
    else
        for (int idx = 0; idx < rows * cols; idx++)
            data[idx] = 0;
}

matrix::matrix(const matrix &copyMatrix)
{
    this->rows = copyMatrix.rows;
    this->cols = copyMatrix.cols;
    data = new double[rows * cols];

    for (int idx = 0; idx < rows * cols; idx++)
        data[idx] = copyMatrix.data[idx];
}

matrix::~matrix()
{
    delete[] data;
}

matrix& matrix::operator=(const matrix &copyMatrix)
{
    if (this == &copyMatrix) return *this;

    delete[] data;

    this->rows = copyMatrix.rows;
    this->cols = copyMatrix.cols;
    data = new double[rows * cols];

    for (int idx = 0; idx < rows * cols; idx++)
        data[idx] = copyMatrix.data[idx];
    
    return *this;
}

matrix matrix::operator+(const matrix &operandMatrix) const
{
    if (this->rows != operandMatrix.getRows() || this->cols != operandMatrix.getCols())
        throw "MATRIX ERROR: Unable to add matrices (Incompatible dimensions)";

    matrix result(this->rows, this->cols);

    for (int idx = 0; idx < rows * cols; idx++)
        result.data[idx] = data[idx] + operandMatrix.data[idx];

    return result;
}

matrix matrix::operator*(const matrix &operandMatrix) const
{
    if (this->cols != operandMatrix.rows)
        throw "MATRIX ERROR: Unable to multiply matrices (Incompatible dimensions)";

    matrix result(this->rows, operandMatrix.cols);

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < operandMatrix.cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < this->cols; k++)
            {
                sum += this->at(i, k) * operandMatrix.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }

    return result;
}

matrix matrix::operator*(int scalar) const
{
    matrix result(this->rows, this->cols);

    for (int idx = 0; idx < rows * cols; idx++)
        result.data[idx] = scalar * data[idx];

    return result;
}

matrix matrix::transpose() const
{
    matrix transposed(this->cols, this->rows);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            transposed.at(j, i) = this->at(i, j);

    return transposed;
}

void matrix::applyFunction(double (*func)(double x))
{
    for (int idx = 0; idx < this->rows * this->cols; idx++)
        this->data[idx] = func(this->data[idx]);
}

void matrix::print() const
{
    for (int i = 0; i < this->rows; i++)
    {
        std::cout << "|";
        for (int j = 0; j < this->cols; j++)
        {
            if (j != this->cols - 1)
                std::cout << this->at(i, j) << " ";
            else
                std::cout << this->at(i, j);
        }
        std::cout << "|\n";
    }
}

void matrix::randomize(double min, double max)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(min, max);

    for (int i = 0; i < rows * cols; i++)
        data[i] = dis(gen);
}
