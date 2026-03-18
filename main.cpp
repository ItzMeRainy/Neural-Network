#include "Matrix/matrix.hpp"
#include "Activations/activations.hpp"
#include "Layer/layer.hpp"
#include <iostream>

int main()
{
    Matrix input(3, 4, true);
    std::cout << "Inputs: \n";
    input.print();
    std::cout << "\n";

    Layer layer(3, 2, relu);
    std::cout << "Weights: \n";
    layer.printWeights();
    std::cout << "\n";
    std::cout << "Bias: \n";
    layer.printBias();
    std::cout << "\n";

    Matrix output = layer.forward(input);
    std::cout << "Output: \n";
    output.print();
    std::cout << "\n";

    return 0;
}