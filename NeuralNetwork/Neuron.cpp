#include "pch.h"
#include "Neuron.hpp"
#include "ordered_json.hpp"

using namespace NeuralNetwork;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

Neuron::Neuron() {
}

Neuron::Neuron(unsigned numOutputs, unsigned index) {

	this->index = index;
	createConnections(numOutputs);

}

Neuron::~Neuron() {
}

void Neuron::setOutputVal(double val) {
	outputVal = val;
}

double Neuron::getOutputVal() const {
	return outputVal;
}

void Neuron::setIndex(unsigned index) {
	this->index = index;
}

unsigned Neuron::getIndex() const {
	return index;
}

void Neuron::setGradient(double gradient) {
	this->gradient = gradient;
}

double Neuron::getGradient() const {
	return gradient;
}

void Neuron::setOutputConnections(const std::vector<Connection> &outputConnections) {
	this->outputConnections = outputConnections;
}

std::vector<Connection> Neuron::getOutputConnections() const {
	return outputConnections;
}

void Neuron::feedForward(const Layer &prevLayer, ActivationFunction* activationFunction) {

	// Sum the previous layers outputs (our current inputs), including
	// the bias node output from the previous layer

	double sum = 0.0;

	for(size_t neuronIndex = 0; neuronIndex < prevLayer.size(); neuronIndex++) {
		sum += prevLayer[neuronIndex].getOutputVal() * prevLayer[neuronIndex].outputConnections[index].weight;
	}

	outputVal = activationFunction->calculate(sum);

}

void Neuron::calcOutputGradients(double targetVal, ActivationFunction* activationFunction) {
	double delta = targetVal - outputVal;
	gradient = delta * activationFunction->derivative(outputVal);
}

void Neuron::calcHiddenGradients(const Layer &nextLayer, ActivationFunction* activationFunction) {
	double dow = sumDOW(nextLayer);
	gradient = dow * activationFunction->derivative(outputVal);
}

void Neuron::updateInputWeights(double learningRate, double momentum, Layer &prevLayer) {

	// Update the weights of the neurons connections in the previous layer
	for(size_t neuronNum = 0; neuronNum < prevLayer.size(); neuronNum++) {
		
		Neuron &neuron = prevLayer[neuronNum];
		Connection &connection = neuron.outputConnections[index];

		double oldDeltaWeight = connection.deltaWeight;

		// Individual input, magnidied by the gradient and train rate (learningRate: overall training rate)
		double newDeltaWeight = learningRate * neuron.getOutputVal() * gradient;
		// Add momentum rate (a fraction of the previous delta weight)
		newDeltaWeight += momentum * oldDeltaWeight;

		connection.deltaWeight = newDeltaWeight;
		connection.weight += newDeltaWeight;

	}

}

void Neuron::createConnections(unsigned numOutputs) {
	for(size_t i = 0; i < numOutputs; i++) {
		outputConnections.push_back(Connection());
		outputConnections.back().weight = Neuron::randomWeight();
	}
}

double Neuron::sumDOW(const Layer &nextLayer) {

	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed
	for(size_t neuronNum = 0; neuronNum < nextLayer.size() - 1; neuronNum++) {
		sum += outputConnections[neuronNum].weight * nextLayer[neuronNum].gradient;
	}

	return sum;
}

double Neuron::randomWeight() {
	return rand() / double(RAND_MAX);
}

void NeuralNetwork::to_json(json& j, const Neuron& n) {

	ordered_json neuronJson;
	neuronJson["output"] = n.outputVal;
	neuronJson["gradient"] = n.gradient;

	size_t size = n.outputConnections.size();
	for(size_t numConnection = 0; numConnection < size; numConnection++) {
		neuronJson["connections"][std::to_string(numConnection)] = json(n.outputConnections[numConnection]);
	}

	j = neuronJson;
}

void NeuralNetwork::from_json(const json& j, Neuron& n) {

	j.at("output").get_to(n.outputVal);
	j.at("gradient").get_to(n.gradient);

	json conn = j.at("connections");
	n.outputConnections = std::vector<Connection>(conn.size());
	for(auto&[key, value] : conn.items()) {
		n.outputConnections[std::stoi(key)] = value;
	}

}
