#pragma once
#include <memory>

namespace NeuralNetwork {

	enum FunctionType {
		None, Tanh, Logistic, Linear, Ramp, Gaussian, Identity, ReLU
	};

	class ActivationFunction {
	public:
		virtual ~ActivationFunction() = default;

		/// <summary>
		/// Creates and returns the activation function, that will be used
		/// </summary>
		/// <param name="functionType">The activation function type to create</param>
		/// <param name="value">The corfficient value of the function</param>
		/// <returns>Unique pointer to the created function type</returns>
		static std::unique_ptr<ActivationFunction> createActivationFunction(FunctionType functionType, double value = 1.0);
		virtual double calculate(double x) = 0;
		virtual double derivative(double x) = 0;
		virtual FunctionType getFunctionType() = 0;

	};

}
