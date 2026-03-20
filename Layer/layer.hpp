#pragma once
#include "Matrix/matrix.hpp"

class Layer
{
    int numOfInputs;
    int numOfNeurons;
    double (*activationFunc)(double x);
    double (*activationFuncDerivative)(double x);
    Matrix weights;
    Matrix bias;
    Matrix input;
    Matrix z;
    Matrix output;

public:
    Layer(int numOfNeurons, int numOfInputs, double (*activationFunc)(double x), double (*activationFuncDerivative)(double x));

    Matrix forward(const Matrix &input);
    Matrix computeDelta(const Matrix &target) const;
    Matrix computeDelta(const Matrix &nextLayerWeights, const Matrix &nextLayerDelta) const;

    void printWeights() const { weights.print(); }
    void printBias() const { bias.print(); }

    int getNumOfNeurons() const { return numOfNeurons; }
    int getNumOfInputs() const { return numOfInputs; }
};