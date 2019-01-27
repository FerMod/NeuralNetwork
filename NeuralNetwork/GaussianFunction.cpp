#include "pch.h"
#include "GaussianFunction.hpp"

using namespace NeuralNetwork;

GaussianFunction::GaussianFunction(double value): value(value) {
}

double GaussianFunction::calculate(double x) {
	return 0.0;
}

double GaussianFunction::derivative(double x) {
	return 0.0;
}

FunctionType GaussianFunction::getFunctionType() {
	return FunctionType::Gaussian;
}


GaussianFunction::~GaussianFunction() {
}
