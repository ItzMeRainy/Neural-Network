#pragma once
#include "Layer/layer.hpp"
#include <vector>

class NeuralNetwork
{
    int numOfInputs;
    std::vector<Layer> layers;

public:
    NeuralNetwork(int numOfInputs) : numOfInputs(numOfInputs) {}

    void addLayer(int numOfNeurons, double (*activationFunc)(double));
    Matrix forward(const Matrix &input);

    int getNumLayers() const { return layers.size(); }
};