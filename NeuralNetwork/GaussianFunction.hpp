#pragma once
#include "ActivationFunction.hpp"

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
