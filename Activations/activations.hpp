#pragma once
#include <cmath>

double sigmoid(double x) { return 1.0 / (1.0 + std::exp(-x)); }
double relu(double x) { return x > 0 ? x : 0; }
double tanh_func(double x) { return std::tanh(x); }