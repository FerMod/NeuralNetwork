#include "pch.h"
#include "ReLUFunction.hpp"

using namespace NeuralNetwork;

ReLUFunction::ReLUFunction(double value): value(value) {
}

double ReLUFunction::calculate(double x) {
	return 0.0;
}

double ReLUFunction::derivative(double x) {
	return 0.0;
}

FunctionType ReLUFunction::getFunctionType() {
	return FunctionType::ReLU;
}


ReLUFunction::~ReLUFunction() {
}
