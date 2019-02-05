#pragma once
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "ActivationFunction.h"
#include "Connection.h"
#include "LayerAlias.h"

namespace NeuralNetwork {

	class Neuron {
	public:
		Neuron();
		Neuron(unsigned numOutputs, unsigned index);
		~Neuron();

		double getOutputVal() const;
		void setOutputVal(double val);

		unsigned getIndex() const;
		void setIndex(unsigned index);

		double getGradient() const;
		void setGradient(double gradient);

		std::vector<Connection> getOutputConnections() const;
		void setOutputConnections(const std::vector<Connection> &outputConnections);

		void feedForward(const Layer &prevLayer, ActivationFunction* activationFunction);
		void calcOutputGradients(double targetVal, ActivationFunction* activationFunction);
		void calcHiddenGradients(const Layer &nextLayer, ActivationFunction* activationFunction);
		void updateInputWeights(double learningRate, double momentum, Layer &layer);

		friend void to_json(nlohmann::json& j, const Neuron& n);
		friend void from_json(const nlohmann::json& j, Neuron& n);

	private:

		void createConnections(unsigned numOutputs);

		static double randomWeight();

		double sumDOW(const Layer &nextLayer);

		unsigned index;
		double outputVal;
		double gradient;
		std::vector<Connection> outputConnections;

	};

}
