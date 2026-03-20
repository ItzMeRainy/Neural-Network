#include "layer.hpp"

Layer::Layer(int numOfNeurons, int numOfInputs, double (*activationFunc)(double x), double (*activationFuncDerivative)(double x))
{
    this->numOfInputs = numOfInputs;
    this->numOfNeurons = numOfNeurons;
    this->weights = Matrix(numOfNeurons, numOfInputs, true);
    this->bias = Matrix(numOfNeurons, 1);
    this->activationFunc = activationFunc;
    this->activationFuncDerivative = activationFuncDerivative;
}

Matrix Layer::forward(const Matrix &input)
{
    this->input = input;
    this->z = weights * input + bias;
    this->output = z.mapFunction(activationFunc);
    return output;
}

Matrix Layer::computeDelta(const Matrix &target) const
{
    Matrix error = output - target;
    Matrix delta = error.elementWiseMultiply(z.mapFunction(activationFuncDerivative));
    return delta;
}

Matrix Layer::computeDelta(const Matrix &nextLayerWeights, const Matrix &nextLayerDelta) const
{
    return (nextLayerWeights.transpose() * nextLayerDelta).elementWiseMultiply(z.mapFunction(activationFuncDerivative));
}

void Layer::updateParameters(const Matrix &delta, double learningRate)
{
    Matrix weightGradient = delta * input.transpose();
    
    Matrix biasGradient(numOfNeurons, 1);
    int samples = delta.getCols();
    for (int row = 0; row < numOfNeurons; row++)
    {
        double sum = 0;
        for (int sample = 0; sample < samples; sample++)
            sum += delta.at(row, sample);
        biasGradient.at(row, 0) = sum;
    }

    weights = weights - (weightGradient * learningRate);
    bias = bias - (biasGradient * learningRate);
}
