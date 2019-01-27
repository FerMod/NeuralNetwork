#pragma once
#include <memory>

namespace NeuralNetwork {

	enum FunctionType {
		None, Tanh, Logistic, Linear, Ramp, Gaussian, Identity, ReLU
	};

	class ActivationFunction {
	public:
		virtual ~ActivationFunction() = default;

		/**
		@params FunctionType functionType 
				The activation function type to create 
		@params double value = 1.0
				The corfficient value of the function				
		@returns std::unique_ptr<ActivationFunction>
				Unique pointer to the created function type 
		**/
		static std::unique_ptr<ActivationFunction> createActivationFunction(FunctionType functionType, double value = 1.0);
		virtual double calculate(double x) = 0;
		virtual double derivative(double x) = 0;
		virtual FunctionType getFunctionType() = 0;

	};

}
