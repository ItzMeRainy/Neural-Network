#include <iostream>
#include "Matrix/matrix.hpp"

int main()
{
    // Create matrix A
    matrix A(2,2);

    A.at(0,0) = 1;
    A.at(0,1) = 2;
    A.at(1,0) = 3;
    A.at(1,1) = 4;

    std::cout << "Matrix A:\n";
    A.print();

    // Transpose
    std::cout << "Transpose of A:\n";
    matrix AT = A.transpose();
    AT.print();

    // Scalar multiplication
    std::cout << "A * 2:\n";
    matrix scalar = A * 2;
    scalar.print();

    // Addition
    std::cout << "A + A:\n";
    matrix add = A + A;
    add.print();

    // Matrix multiplication
    std::cout << "A * A:\n";
    matrix mult = A * A;
    mult.print();

    // Test another matrix for multiplication
    matrix B(2,3);

    B.at(0,0) = 1;
    B.at(0,1) = 2;
    B.at(0,2) = 3;
    B.at(1,0) = 4;
    B.at(1,1) = 5;
    B.at(1,2) = 6;

    std::cout << "Matrix B:\n";
    B.print();

    std::cout << "A * B:\n";
    matrix C = A * B;
    C.print();

    return 0;
}