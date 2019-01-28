#pragma once
#include "ActivationFunction.h"

namespace NeuralNetwork {

	class IdentityFunction: public ActivationFunction {
	public:
		IdentityFunction(double value);
		~IdentityFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
