#pragma once
#include "ActivationFunction.h"

namespace NeuralNetwork {

	class GaussianFunction: public ActivationFunction {
	public:
		GaussianFunction(double value);
		~GaussianFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
