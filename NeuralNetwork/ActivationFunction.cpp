#include "pch.h"
#include "ActivationFunction.hpp"
#include "TanhFunction.hpp"
#include "SigmoidFunction.hpp"
#include "LinearFunction.hpp"
#include "RampFunction.hpp"
#include "GaussianFunction.hpp"
#include "IdentityFunction.hpp"
#include "ReLUFunction.hpp"

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
		case None:
		default:
			return std::unique_ptr<ActivationFunction>();
	}
}
