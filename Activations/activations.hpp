#pragma once
#include <cmath>

double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double relu(double x) { return x > 0 ? x : 0; }
double tanhFunc(double x) { return tanh(x); }

double sigmoidDerivative(double x) { return sigmoid(x) * (1 - sigmoid(x)); }
double reluDerivative(double x) { return x > 0 ? 1 : 0; }
double tanhDerivative(double x) { return 1 - (tanh(x) * tanh(x)); }