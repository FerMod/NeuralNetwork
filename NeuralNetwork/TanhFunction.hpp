#pragma once
#include "ActivationFunction.hpp"

namespace NeuralNetwork {

	class TanhFunction: public ActivationFunction {
	public:
		TanhFunction(double value);
		~TanhFunction();

		double calculate(double x) override;
		double derivative(double x) override;
		FunctionType getFunctionType() override;

	private:
		double value;

	};

}
