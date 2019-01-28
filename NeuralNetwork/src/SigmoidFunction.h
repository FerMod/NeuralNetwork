#pragma once
#include "ActivationFunction.h"

namespace NeuralNetwork {

	class SigmoidFunction: public ActivationFunction {
	public:
		SigmoidFunction(double value);
		~SigmoidFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
