#include "pch.h"
//#include "Layer.hpp"
//#include <cassert>
//
//using namespace NeuralNetwork;
//
//Layer::Layer() {
//}
//
//Layer::Layer(size_t numNeurons, size_t numOutputs) {
//	
//	// Fill the new layer with neurons and add bias neurons
//	for(size_t i = 0; i <= numNeurons; i++) {
//		neurons.push_back(Neuron(numOutputs, i));
//	}
//
//	// Force the bias node value to 1.0
//	neurons.back().setOutputVal(1.0);
//
//}
//
//void Layer::feedForward(const Layer &prevLayer, ActivationFunction* activationFunction) {
//
//	for(size_t i = 0; i < neurons.size() - 1; i++) {
//		neurons[i].feedForward(prevLayer, activationFunction);
//	}
//
//}
//
//void Layer::setOutputVals(const std::vector<double>& inputVals) {
//
//	assert(inputVals.size() == neurons.size() - 1);
//
//	for(size_t i = 0; i < inputVals.size(); i++) {
//		neurons[i].setOutputVal(inputVals[i]);
//	}
//
//}
//
//std::vector<Neuron> NeuralNetwork::Layer::getNeurons() const {
//	return neurons;
//}
//
//void NeuralNetwork::Layer::setNeurons(const std::vector<Neuron> &neurons) {
//	this->neurons = neurons;
//}
//
//size_t NeuralNetwork::Layer::getSize() const {
//	return neurons.size();
//}
//
//Layer::~Layer() {
//}
