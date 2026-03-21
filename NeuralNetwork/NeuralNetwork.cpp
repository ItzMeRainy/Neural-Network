#include "NeuralNetwork.hpp"
#include <iostream>
#include <Loss/loss.hpp>
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

void NeuralNetwork::backward(const Matrix &target, double learningRate)
{
    Matrix delta = layers.back().computeDelta(target);
    layers.back().updateParameters(delta, learningRate);

    for (int idx = layers.size() - 2; idx >= 0; idx--)
    {
        delta = layers[idx].computeDelta(layers[idx + 1].getWeights(), delta);
        layers[idx].updateParameters(delta, learningRate);
    }
}

void NeuralNetwork::train(const Matrix &input, const Matrix &target, double learningRate, int epochs, bool log)
{
    for (int epoch = 0; epoch < epochs; epoch++)
    {
        Matrix output = forward(input);
        double loss = meanSquaredError(output, target);
        if (log) std::cout << "epoch: " << epoch << "; Loss: " << loss << "\n";
        backward(target, learningRate);
    }
}
