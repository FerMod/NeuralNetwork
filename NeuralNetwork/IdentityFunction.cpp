#include "pch.h"
#include "IdentityFunction.hpp"

using namespace NeuralNetwork;

IdentityFunction::IdentityFunction(double value): value(value) {
}

double IdentityFunction::calculate(double x) {
	return 0.0;
}

double IdentityFunction::derivative(double x) {
	return 0.0;
}

FunctionType IdentityFunction::getFunctionType() {
	return FunctionType::Identity;
}


IdentityFunction::~IdentityFunction() {
}
