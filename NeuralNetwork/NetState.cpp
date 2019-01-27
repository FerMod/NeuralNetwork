#include "pch.h"
#include "NetState.hpp"
#include <iostream>
#include <ostream>
#include <iomanip> 
#include <fstream>
#include "Neuron.hpp"
#include "ordered_json.hpp"

using namespace NeuralNetwork;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

NetState::NetState(const std::string &putputFolder = "output") {
	this->putputFolder = fs::absolute(putputFolder);
	fs::create_directories(this->putputFolder);
}

/*
// Unordered json creation

void NetState::saveNetworkState(const NeuralNet &net, const std::string &filename) {

	ordered_json jsonFile = json(net);
	jsonFile["name"] = "test";

	// Combine directory and file path
	fs::path filePath = putputFolder / filename;
	std::ofstream outFile(filePath);
	if(!outFile.is_open()) {
		std::cout << "Could not open the file in path: '" << filePath.string() << "'" << std::endl;
	} else {
		outFile << std::setw(2) << jsonFile << std::endl;
		outFile.close();
	}

}
*/

void NetState::saveNetworkState(const NeuralNet &net, const std::string &filename) {

	double learningRate = 0.0;
	double momentum = 0.0;

	ordered_json layerState;
	std::vector<Layer> layers = net.getLayers();
	for(size_t numLayer = 0; numLayer < layers.size(); numLayer++) {

		ordered_json neuronState;
		for(const Neuron& neuron : layers[numLayer]) {

			unsigned index = neuron.getIndex();
			neuronState[std::to_string(index)]["output"] = neuron.getOutputVal();
			neuronState[std::to_string(index)]["gradient"] = neuron.getGradient();

			ordered_json connectionState;
			std::vector<Connection> connections = neuron.getOutputConnections();
			for(size_t numConnection = 0; numConnection < connections.size(); numConnection++) {
				connectionState[std::to_string(numConnection)]["weight"] = connections[numConnection].weight;
				connectionState[std::to_string(numConnection)]["deltaWeight"] = connections[numConnection].deltaWeight;
			}
			neuronState[std::to_string(index)]["connections"] = connectionState;

		}
		layerState[std::to_string(numLayer)] = neuronState;

	}

	ordered_json netState;
	netState["name"] = "test";
	netState["learningRate"] = net.getLearningRate();
	netState["momentum"] = net.getMomentum();
	netState["layers"] = layerState;

	// Combine directory and file path
	fs::path filePath = putputFolder / filename;
	std::ofstream outFile(filePath);
	if(!outFile.is_open()) {
		std::cout << "Could not open the file in path: '" << filePath.string() << "'" << std::endl;
	} else {
		outFile << std::setw(2) << netState << std::endl;
		outFile.close();
	}

}

NeuralNet NetState::loadNetworkState(const std::string &filename) {


	// Combine directory and file path
	fs::path filePath = putputFolder / filename;

	if(!fs::exists(filePath)) {
		std::cout << "Could not find the file: '" << filePath.string() << "'" << std::endl;
		std::abort();
	}

	std::ifstream inFile(filePath);
	json netState;
	inFile >> netState;

	std::string name = netState.at("name").get<std::string>();

	return netState.get<NeuralNet>();
}

/*
NeuralNet NetState::loadNetworkState(const std::string &filename) {


	// Combine directory and file path
	fs::path filePath = putputFolder / filename;

	if(!fs::exists(filePath)) {
		std::cout << "Could not find the file: '" << filePath.string() << "'" << std::endl;
		std::abort();
	}

	std::ifstream inFile(filePath);
	json netState;
	inFile >> netState;

	std::string name = netState["name"].get<std::string>();

	json layerState = netState["layers"];
	std::vector<Layer> layerVect(layerState.size());
	for(json::iterator layersIt = layerState.begin(); layersIt != layerState.end(); ++layersIt) {

		int layerKey = std::stoi(layersIt.key());

		json neuronState = layerState[layersIt.key()];
		Layer layer(neuronState.size());

		for(json::iterator neuronsIt = neuronState.begin(); neuronsIt != neuronState.end(); ++neuronsIt) {

			int index = std::stoi(neuronsIt.key());
			double outputVal = neuronsIt.value()["output"].get<double>();
			double gradient = neuronsIt.value()["gradient"].get<double>();

			json connectionState = neuronState[neuronsIt.key()]["connections"];
			std::vector<Connection> connectionVect(connectionState.size());
			for(json::iterator connectionsIt = connectionState.begin(); connectionsIt != connectionState.end(); ++connectionsIt) {
				int connKey = std::stoi(connectionsIt.key());
				Connection conn;
				conn.weight = connectionsIt.value()["weight"].get<double>();
				conn.deltaWeight = connectionsIt.value()["deltaWeight"].get<double>();
				connectionVect[connKey] = conn;
			}

			//std::vector<Connection> connections;
			//for(auto& connectionElement : connectionState) {
			//	Connection conn;
			//	conn.weight = connectionElement["weight"].get<double>();
			//	conn.deltaWeight = connectionElement["deltaWeight"].get<double>();
			//	connections.push_back(conn);
			//}

			Neuron neuron;
			neuron.setIndex(index);
			neuron.setOutputVal(outputVal);
			neuron.setGradient(gradient);
			neuron.setOutputConnections(connectionVect);

			layer[index] = neuron;

		}
		layerVect[layerKey] = layer;

	}

	NeuralNet net;
	net.setLayers(layerVect);
	net.setLearningRate(netState["learningRate"].get<double>());
	net.setMomentum(netState["momentum"].get<double>());

	return net;
}
*/

NetState::~NetState() {
}
