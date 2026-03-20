#include "layer.hpp"

Layer::Layer(int numOfNeurons, int numOfInputs, double (*activationFunc)(double x))
{
    this->numOfInputs = numOfInputs;
    this->numOfNeurons = numOfNeurons;
    this->weights = Matrix(numOfNeurons, numOfInputs, true);
    this->bias = Matrix(numOfNeurons, 1);
    this->activationFunc = activationFunc;
}

Matrix Layer::forward(const Matrix &input)
{
    this->input = input;
    this->z = weights * input + bias;
    this->output = this->z.mapFunction(activationFunc);
    return this->output;
}
