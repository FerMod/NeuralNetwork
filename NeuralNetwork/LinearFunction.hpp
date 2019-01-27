#pragma once
#include "ActivationFunction.hpp"

namespace NeuralNetwork {

	class LinearFunction: public ActivationFunction {
	public:
		LinearFunction(double value);
		~LinearFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}

