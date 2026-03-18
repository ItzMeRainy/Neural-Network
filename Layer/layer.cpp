#include "layer.hpp"

Layer::Layer(int numOfNeurons, int numOfInputs, double (*activationFunc)(double x))
{
    this->numOfInputs = numOfInputs;
    this->numOfNeurons = numOfNeurons;
    this->weights = Matrix(numOfNeurons, numOfInputs, true);
    this->bias = Matrix(numOfNeurons, 1);
    this->activationFunc = activationFunc;
}

Matrix Layer::forward(const Matrix &input) const
{
    return ((weights * input) + bias).mapFunction(activationFunc);
}
