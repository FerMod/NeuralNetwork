#include "pch.h"
#include "LinearFunction.hpp"

using namespace NeuralNetwork;

LinearFunction::LinearFunction(double value): value(value) {
}

double LinearFunction::calculate(double x) {
	return 0.0;
}

double LinearFunction::derivative(double x) {
	return 0.0;
}

FunctionType LinearFunction::getFunctionType() {
	return FunctionType::Linear;
}


LinearFunction::~LinearFunction() {
}
