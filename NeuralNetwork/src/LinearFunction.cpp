#include "pch.h"
#include "LinearFunction.h"

using namespace NeuralNetwork;

/// <summary>
/// Finds the foo.
/// </summary>
/// <param name="value"></param>
LinearFunction::LinearFunction(double value): value(value) {
}

double LinearFunction::calculate(double x) {
	return x;
}

double LinearFunction::derivative(double x) {
	return value;
}

FunctionType LinearFunction::getFunctionType() {
	return FunctionType::Linear;
}


LinearFunction::~LinearFunction() {
}
