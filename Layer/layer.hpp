#pragma once
#include "Matrix/matrix.hpp"

class Layer
{
    int numOfInputs;
    int numOfNeurons;
    double (*activationFunc)(double x);
    Matrix weights;
    Matrix bias;
    Matrix input;
    Matrix z;
    Matrix output;

public:
    Layer(int numOfNeurons, int numOfInputs, double (*activationFunc)(double x));

    Matrix forward(const Matrix &input);

    void printWeights() const { weights.print(); }
    void printBias() const { bias.print(); }

    int getNumOfNeurons() const { return numOfNeurons; }
    int getNumOfInputs() const { return numOfInputs; }
};