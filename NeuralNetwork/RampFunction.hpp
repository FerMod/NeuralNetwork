#pragma once
#include "ActivationFunction.hpp"

namespace NeuralNetwork {

	class RampFunction: public ActivationFunction {
	public:
		RampFunction(double value);
		~RampFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
