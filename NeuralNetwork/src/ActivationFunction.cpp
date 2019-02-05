#include "pch.h"
#include "ActivationFunction.h"
#include "TanhFunction.h"
#include "SigmoidFunction.h"
#include "LinearFunction.h"
#include "RampFunction.h"
#include "GaussianFunction.h"
#include "IdentityFunction.h"
#include "ReLUFunction.h"

using namespace NeuralNetwork;

std::unique_ptr<ActivationFunction> ActivationFunction::createActivationFunction(FunctionType functionType, double value) {
	switch(functionType) {
		case Tanh:
			return std::make_unique<TanhFunction>(value);
		case Logistic:
			return std::make_unique<SigmoidFunction>(value);
		case Linear:
			return std::make_unique<LinearFunction>(value);
		case Ramp:
			return std::make_unique<RampFunction>(value);
		case Gaussian:
			return std::make_unique<GaussianFunction>(value);
		case Identity:
			return std::make_unique<IdentityFunction>(value);
		case ReLU:
			return std::make_unique<ReLUFunction>(value);
		default:
			return std::unique_ptr<ActivationFunction>();
	}
}
