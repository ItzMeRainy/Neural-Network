#include "NeuralNetwork.hpp"
#include <iostream>

void NeuralNetwork::addLayer(int numOfNeurons, double (*activationFunc)(double), double (*activationFuncDerivative)(double))
{
    if (!layers.empty())
    {
        int prevOutputRows = layers.back().getNumOfNeurons();
        layers.push_back(Layer(numOfNeurons, prevOutputRows, activationFunc, activationFuncDerivative));
    }

    else
        layers.push_back(Layer(numOfNeurons, this->numOfInputs, activationFunc, activationFuncDerivative));
}

Matrix NeuralNetwork::forward(const Matrix &input)
{
    Matrix output = input;
    int batchSize = input.getCols();

    for (auto &layer : layers)
    {
        if (output.getRows() != layer.getNumOfInputs() || output.getCols() != batchSize)
            throw std::runtime_error("NEURAL NETWORK ERROR: Incompatible input passed to layer.");

        output = layer.forward(output);
    }

    return output;
}
