#include "NeuralNetwork.hpp"
#include <iostream>

void NeuralNetwork::addLayer(int numOfNeurons, double (*activationFunc)(double))
{
    if (!layers.empty())
    {
        int prevOutputRows = layers.back().getOutputRows();
        layers.push_back(Layer(numOfNeurons, prevOutputRows, activationFunc));
    }

    else
        layers.push_back(Layer(numOfNeurons, this->numOfInputs, activationFunc));
}

Matrix NeuralNetwork::forward(const Matrix &input)
{
    if (input.getRows() != numOfInputs)
        throw std::runtime_error("Neural Network Error: Input incompatible with Neural Network.");

    Matrix output = input;

    for (auto &layer : layers)
        output = layer.forward(output);

    return output;
}
