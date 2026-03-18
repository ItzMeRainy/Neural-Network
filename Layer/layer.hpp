#pragma once
#include "Matrix/matrix.hpp"

class Layer
{
    int numOfInputs;
    int numOfNeurons;
    double (*activationFunc)(double x);
    Matrix weights;
    Matrix bias;

public:
    Layer(int numOfInputs, int numOfNeurons, double (*activationFunc)(double x));

    void printWeights() const { weights.print(); };
    void printBias() const { bias.print(); };

    Matrix forward(const Matrix &input) const;
};