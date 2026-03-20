#include "loss.hpp"
#include <iostream>
#include <vector>

double meanSquaredError(const Matrix &prediction, const Matrix &target)
{
    if (prediction.getRows() != target.getRows() || prediction.getCols() != target.getCols())
        throw std::runtime_error("LOSS ERROR: Prediction and target matrix dimensions incompatible.");
    
    int predRows = prediction.getRows();
    int predCols = prediction.getCols();
    
    double sum = 0;
    for (int i = 0; i < predRows; i++)
    {
        for (int j = 0; j < predCols; j++)
        {
            double diff = prediction.at(i, j) - target.at(i, j);
            sum += diff * diff;
        }
    }

    return sum / (predRows * predCols);
}