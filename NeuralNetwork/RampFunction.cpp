#include "pch.h"
#include "RampFunction.hpp"

using namespace NeuralNetwork;

RampFunction::RampFunction(double value): value(value) {
}

double RampFunction::calculate(double x) {
	return 0.0;
}

double RampFunction::derivative(double ) {
	return 0.0;
}

FunctionType RampFunction::getFunctionType() {
	return FunctionType::Ramp;
}


RampFunction::~RampFunction() {
}
