#include "pch.h"
#include "NeuralNet.h"
#include <cassert>
#include "Neuron.h"
#include "../lib/nlohmann/ordered_json.hpp"

using namespace NeuralNetwork;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

NeuralNet::NeuralNet() {

	activationFunction = std::move(ActivationFunction::createActivationFunction(FunctionType::Tanh));

	learningRate = 0.15;
	momentum = 0.1;
	recentAverageSmoothingFactor = 100.0;

}

NeuralNet::NeuralNet(const std::vector<unsigned> &topology): NeuralNet() {

	size_t numLayers = topology.size();
	for(size_t layerNum = 0; layerNum < numLayers; layerNum++) {

		// Number of outputs (number of neurons in the next layer) 
		unsigned numOutputs = (layerNum == numLayers - 1) ? 0 : topology[layerNum + 1];

		//------ TODO: Move to Layer class
		// layers.push_back(Layer(topology[layerNum], numOutputs));

		// Create a new layer
		layers.push_back(Layer());

		// Fill the new layer with neurons and add bias neurons
		for(size_t neuronNum = 0; neuronNum <= topology[layerNum]; neuronNum++) {
			layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		// Force the bias node value to 1.0
		layers.back().back().setOutputVal(1.0);

		// -----
	}

}

void NeuralNet::feedForward(const std::vector<double> &inputVals) {

	// ------ TODO: Move to Layer class
	// Asign (latch) the input values into the input neurons
	// layers[0].setOutputVals(inputVals);
	
	// Check that number input values equals number input neurons
	assert(inputVals.size() == layers[0].size() - 1);


	// Asign (latch) the input values into the input neurons
	for(size_t i = 0; i < inputVals.size(); i++) {
		layers[0][i].setOutputVal(inputVals[i]);
	}
	// ------

	// Forward propagate
	for(size_t layerNum = 1; layerNum < layers.size(); layerNum++) {
		Layer &prevLayer = layers[layerNum - 1];
		// ------ TODO: Move to Layer class
		// layers[layerNum].feedForward(prevLayer, activationFunction);
		for(size_t neuronNum = 0; neuronNum < layers[layerNum].size() - 1; neuronNum++) {
			layers[layerNum][neuronNum].feedForward(prevLayer, activationFunction.get());
		}
		// ------
	}

}

void NeuralNet::backProp(const std::vector<double>& targetVals) {

	// Calculate overall net error (RMS of output neuron errors)
	// RMS = "Root Mean Square Error"
	calculateOverallNetError(targetVals);

	// Recent average error measurement
	calculateRecentAverageError(recentAverageError, error);

	// Calculate output layer gradients
	calcOutputLayerGradients(targetVals);

	// Calculate gradients on hidden layers
	calcHiddenLayerGradients();

	// Update connection weights in the output and hidden layers.  
	updateConnectionWeights();

}

void NeuralNet::updateConnectionWeights() {

	for(size_t layerNum = layers.size() - 1; layerNum > 0; layerNum--) {

		Layer &layer = layers[layerNum];
		Layer &prevLayer = layers[layerNum - 1];

		for(size_t neuronNum = 0; neuronNum < layer.size() - 1; neuronNum++) {
			layer[neuronNum].updateInputWeights(learningRate, momentum, prevLayer);
		}

	}

}

void NeuralNet::calcHiddenLayerGradients() {
	for(size_t layerNum = layers.size() - 2; layerNum > 0; layerNum--) {

		Layer &hiddenLayer = layers[layerNum];
		Layer &nextLayer = layers[layerNum + 1];

		for(size_t neuronNum = 0; neuronNum < hiddenLayer.size(); neuronNum++) {
			hiddenLayer[neuronNum].calcHiddenGradients(nextLayer, activationFunction.get());
		}

	}
}

void NeuralNet::calcOutputLayerGradients(const std::vector<double> &targetVals) {
	
	Layer &outputLayer = layers.back();

	for(size_t neuronNum = 0; neuronNum < outputLayer.size() - 1; neuronNum++) {
		outputLayer[neuronNum].calcOutputGradients(targetVals[neuronNum], activationFunction.get());
	}

}

std::vector<double> NeuralNet::getResults() const {
	std::vector<double> resultVals;
	for(size_t neuronNum = 0; neuronNum < layers.back().size() - 1; neuronNum++) {
		resultVals.push_back(layers.back()[neuronNum].getOutputVal());
	}
	return resultVals;
}

void NeuralNet::calculateRecentAverageError(double smoothingFactor, double error) {
	recentAverageError = (recentAverageError * smoothingFactor + error) / (smoothingFactor + 1.0);
}

double NeuralNet::getRecentAverageError() const {
	return recentAverageError;
}

void NeuralNet::setRecentAverageError(double recentAverageError) {
	this->recentAverageError = recentAverageError;
}

double NeuralNet::getRecentAverageSmoothingFactor() const {
	return recentAverageSmoothingFactor;
}

void NeuralNet::setRecentAverageSmoothingFactor(double recentAverageSmoothingFactor) {
	this->recentAverageSmoothingFactor = recentAverageSmoothingFactor;
}

std::vector<Layer> NeuralNet::getLayers() const {
	return layers;
}

void NeuralNet::setLayers(const std::vector<Layer> &layers) {
	this->layers = layers;
}

void NeuralNet::setMomentum(double momentum) {
	this->momentum = momentum;
}

double NeuralNet::getMomentum() const {
	return momentum;
}

void NeuralNet::setLearningRate(double learningRate) {
	this->learningRate = learningRate;
}

double NeuralNet::getLearningRate() const {
	return learningRate;
}

void NeuralNet::calculateOverallNetError(const std::vector<double> & targetVals) {
	
	Layer &outputLayer = layers.back();
	error = 0.0;

	for(size_t neuronNum = 0; neuronNum < outputLayer.size() - 1; neuronNum++) {
		double delta = targetVals[neuronNum] - outputLayer[neuronNum].getOutputVal();
		error += delta * delta;
	}

	error /= outputLayer.size() - 1; // Average error squared
	error = std::sqrt(error);        // Root Mean Square Error
	
}

double NeuralNet::getError() const {
	return error;
}

void NeuralNet::setError(double error) {
	this->error = error;
}

void NeuralNetwork::to_json(json& j, const NeuralNet& nn) {

	double learningRate = 0.0;
	double momentum = 0.0;

	ordered_json layersJson;
	size_t size = nn.layers.size();
	for(size_t numLayer = 0; numLayer < size; numLayer++) {

		ordered_json neuronsJson;
		for(const Neuron& neuron : nn.layers[numLayer]) {

			unsigned index = neuron.getIndex();
			neuronsJson[std::to_string(index)] = json(neuron);

		}
		layersJson[std::to_string(numLayer)] = neuronsJson;

	}

	ordered_json netState;
	netState["learningRate"] = learningRate;
	netState["momentum"] = momentum;
	netState["layers"] = layersJson;

	j = netState;

}

void NeuralNetwork::from_json(const json& j, NeuralNet& nn) {

	j.at("learningRate").get_to(nn.learningRate);
	j.at("momentum").get_to(nn.momentum);

	json layersJson = j.at("layers");
	nn.layers = std::vector<Layer>(layersJson.size());
	for(auto&[layerKey, layerValue] : layersJson.items()) {

		unsigned layerIndex = std::stoi(layerKey);

		Layer layer(layerValue.size());
		for(auto&[neuronKey, neuronValue] : layerValue.items()) {

			Neuron neuron = neuronValue.get<Neuron>();

			unsigned index = std::stoi(neuronKey);
			neuron.setIndex(index);

			layer[index] = neuron;

		}
		nn.layers[layerIndex] = layer;

	}

}
