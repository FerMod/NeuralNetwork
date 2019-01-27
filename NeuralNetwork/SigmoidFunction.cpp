#include "pch.h"
#include "SigmoidFunction.hpp"
#include <cmath>

using namespace NeuralNetwork;

SigmoidFunction::SigmoidFunction(double value): value(value) {
}

double SigmoidFunction::calculate(double x) {
	return 1.0 / (1.0 + exp(-value * x));
}

double SigmoidFunction::derivative(double x) {
	double fx = calculate(x);
	return fx * (1.0 - fx);
}

FunctionType SigmoidFunction::getFunctionType() {
	return FunctionType::Logistic;
}


SigmoidFunction::~SigmoidFunction() {
}
