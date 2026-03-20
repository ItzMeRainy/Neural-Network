#include "matrix.hpp"
#include <iostream>
#include <random>

Matrix::Matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}

Matrix::Matrix(int rows, int cols, bool randomize, double min, double max)
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

Matrix::Matrix(const Matrix &copyMatrix)
{
    this->rows = copyMatrix.rows;
    this->cols = copyMatrix.cols;
    data = new double[rows * cols];

    for (int idx = 0; idx < rows * cols; idx++)
        data[idx] = copyMatrix.data[idx];
}

Matrix::Matrix(Matrix &&moveMatrix) noexcept
{
    this->rows = moveMatrix.rows;
    this->cols = moveMatrix.cols;
    this->data = moveMatrix.data;

    moveMatrix.rows = 0;
    moveMatrix.cols = 0;
    moveMatrix.data = nullptr;
}

Matrix::~Matrix()
{
    delete[] data;
}

Matrix& Matrix::operator=(const Matrix &copyMatrix)
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

Matrix& Matrix::operator=(Matrix &&moveMatrix) noexcept
{
    if (this == &moveMatrix) return *this;

    delete[] data;

    this->rows = moveMatrix.rows;
    this->cols = moveMatrix.cols;
    this->data = moveMatrix.data;

    moveMatrix.rows = 0;
    moveMatrix.cols = 0;
    moveMatrix.data = nullptr;

    return *this;
}

Matrix Matrix::operator+(const Matrix &operandMatrix) const
{
    Matrix result(this->rows, this->cols);

    if (this->rows == operandMatrix.rows && this->cols == operandMatrix.cols)
    {
        for (int idx = 0; idx < rows * cols; idx++)
            result.data[idx] = data[idx] + operandMatrix.data[idx];
    
        return result;
    }

    else if (this->rows == operandMatrix.rows && operandMatrix.cols == 1)
    {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                result.at(i, j) = this->at(i, j) + operandMatrix.at(i, 0);
            }
        return result;
    }
    
    else
        throw std::runtime_error("MATRIX ERROR: Unable to add matrices (Incompatible dimensions)");
}

Matrix Matrix::operator-(const Matrix &operandMatrix) const
{
    Matrix result(this->rows, this->cols);

    if (this->rows == operandMatrix.rows && this->cols == operandMatrix.cols)
    {
        for (int idx = 0; idx < rows * cols; idx++)
            result.data[idx] = data[idx] + operandMatrix.data[idx];
    
        return result;
    }

    else if (this->rows == operandMatrix.rows && operandMatrix.cols == 1)
    {
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
            {
                result.at(i, j) = this->at(i, j) - operandMatrix.at(i, 0);
            }
        return result;
    }
    
    else
        throw std::runtime_error("MATRIX ERROR: Unable to subtract matrices (Incompatible dimensions)");
}

Matrix Matrix::operator*(const Matrix &operandMatrix) const
{
    if (this->cols != operandMatrix.rows)
        throw std::runtime_error("MATRIX ERROR: Unable to multiply matrices (Incompatible dimensions)");

    Matrix result(this->rows, operandMatrix.cols);

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

Matrix Matrix::operator*(double scalar) const
{
    Matrix result(this->rows, this->cols);

    for (int idx = 0; idx < rows * cols; idx++)
        result.data[idx] = scalar * data[idx];

    return result;
}

Matrix Matrix::elementWiseMultiply(const Matrix &operandMatrix) const
{
    if (this->rows != operandMatrix.rows || this->cols != operandMatrix.cols)
        throw std::runtime_error("MATRIX ERROR: Unable to multiply matrices (Incompatible dimensions)");

    Matrix result(this->rows, this->cols);

    for (int idx = 0; idx < rows * cols; idx++)
        result.data[idx] = this->data[idx] * operandMatrix.data[idx];

    return result;
}

Matrix Matrix::transpose() const
{
    Matrix transposed(this->cols, this->rows);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            transposed.at(j, i) = this->at(i, j);

    return transposed;
}

void Matrix::applyFunction(double (*func)(double x))
{
    for (int idx = 0; idx < this->rows * this->cols; idx++)
        this->data[idx] = func(this->data[idx]);
}

Matrix Matrix::mapFunction(double (*func)(double x)) const
{
    Matrix copiedMatrix = *this;
    copiedMatrix.applyFunction(func);
    return copiedMatrix;
}

void Matrix::print() const
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

void Matrix::randomize(double min, double max)
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis(min, max);

    for (int i = 0; i < rows * cols; i++)
        data[i] = dis(gen);
}
