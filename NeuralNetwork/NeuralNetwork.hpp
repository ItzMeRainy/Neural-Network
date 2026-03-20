#pragma once
#include "Layer/layer.hpp"
#include <vector>

class NeuralNetwork
{
    int numOfInputs;
    std::vector<Layer> layers;

public:
    NeuralNetwork(int numOfInputs) : numOfInputs(numOfInputs) {}

    void addLayer(int numOfNeurons, double (*activationFunc)(double), double (*activationFuncDerivative)(double));
    int getNumLayers() const { return layers.size(); }

    Matrix forward(const Matrix &input);
};