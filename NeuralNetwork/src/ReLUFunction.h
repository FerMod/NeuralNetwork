#pragma once
#include "ActivationFunction.h"

namespace NeuralNetwork {

	class ReLUFunction: public ActivationFunction {
	public:
		ReLUFunction(double value);
		~ReLUFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
