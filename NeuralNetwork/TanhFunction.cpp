#include "pch.h"
#include "TanhFunction.hpp"
#include <cmath>

using namespace NeuralNetwork;

TanhFunction::TanhFunction(double value): value(value) {
}

double TanhFunction::calculate(double x) {
	return tanh(x);
}

double TanhFunction::derivative(double x) {
	// tanh Derivative:
	// tanh(x) = 1 / cosh^2(x)
	// OR
	// tanh(x) = 1 - tanh^2(x)
	return 1.0 - pow(calculate(x), 2);
}

FunctionType TanhFunction::getFunctionType() {
	return FunctionType::Tanh;
}


TanhFunction::~TanhFunction() {
}
