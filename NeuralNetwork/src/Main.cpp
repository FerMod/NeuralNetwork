// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <vector>
#include <string>
#include <cassert>
#include <thread>
#include <mutex> 
#include <future>
#include <condition_variable>
#include <chrono>
#include <filesystem>

#include "NeuralNet.h"
#include "TrainingData.h"
#include "NetState.h"
#include "Utils.h"
#include "LayerAlias.h"
#include "Neuron.h"

using namespace NeuralNetwork;

const std::string TRAINING_FILENAME = "trainingData.txt";
const std::string STATE_FILENAME = "NeuralNetworkStateTest.json";
const std::string DATA_FOLDER = "data";

const int TRAINING_SETS = 100;

std::mutex mutex;

//#define CREATE_FILE
#define TRAIN
#define RUN

void showVectorVals(const std::string label, const std::vector<double> &vect) {
	std::lock_guard<std::mutex> guard(mutex);
	std::ostringstream os;
	os << label << std::endl;
	for(size_t i = 0; i < vect.size(); i++) {
		os << "    [" << i << "] " << vect[i] << std::endl;
	}
	std::cout << os.str();
}

int main() {

	NetState state(DATA_FOLDER);
	NeuralNet net;

#if defined(CREATE_FILE) || defined(TRAIN)
	TrainingData trainingData(TRAINING_FILENAME, DATA_FOLDER);
#endif

#if defined(CREATE_FILE)
	std::cout << "Creating random training data..." << std::endl;
	trainingData.createRandomData(TRAINING_SETS);
	std::cout << "Finished creating training data" << std::endl;
#endif

#if defined(TRAIN)

	std::vector<unsigned> topology;
	trainingData.getTopology(topology, "topology:");
	net = NeuralNet(topology);

	std::vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;
	size_t numInputVals = 0;

	auto start = std::chrono::high_resolution_clock::now();

	while(!trainingData.isEof()) {

		numInputVals = trainingData.getNeuronValues(inputVals, "in:");
		if(numInputVals != topology[0]) {
			break;
		}

		++trainingPass;
		std::cout << std::endl << "Pass " << trainingPass << ": " << std::endl;

		showVectorVals("  Inputs:", inputVals);
		net.feedForward(inputVals);

		// Collect the results
		resultVals = net.getResults();
		showVectorVals("  Outputs:", resultVals);

		// Train the net
		trainingData.getNeuronValues(targetVals, "out:");
		showVectorVals("  Targets:", targetVals);
		assert(targetVals.size() == topology.back());

		std::future<size_t> maxValIndexResult = std::async(std::launch::async, Utils::getMaxValueIndex<double>, resultVals);

		net.backProp(targetVals);

		// Report the training results
		size_t maxValIndex = maxValIndexResult.get();
		std::cout << "  Chosen value: [" << maxValIndex << "] " << resultVals[maxValIndex] << std::endl;

		// Average error measurement
		std::cout << "  Net recent average error: " << net.getRecentAverageError() << std::endl;

	}
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
	std::cout << std::endl << "Elapsed time: " << milliseconds << " ms" << std::endl;

	state.saveNetworkState(net, STATE_FILENAME);

#endif

#if defined(RUN)

#if !defined(TRAIN)
	net = state.loadNetworkState(STATE_FILENAME);
#endif
	std::vector<double> input(net.getLayers()[0].size() - 1);
	std::vector<double> result;

	std::cout << std::endl << "===================================\n" << std::endl;

	int a = 0;
	int b = 0;
	while(a != -1 || b != -1) {

		std::cout << "Input values [0, 9]. Input -1 to exit." << std::endl;
		std::cout << "a: ";
		std::cin >> a;
		if(a == -1 || b == -1) {
			break;
		} else if(a < 0 || a >= 10) {
			std::cout << std::endl << "Value must be between [0, 9]." << std::endl << std::endl;
			continue;
		} else {
			input[0] = a;
			//input[a] = 1;
		}

		std::cout << "b: ";
		std::cin >> b;
		if(b == -1) {
			break;
		} else if(b < 0 || b >= 10) {
			std::cout << std::endl << "Value must be between [0, 9]." << std::endl << std::endl;
			continue;
		} else {
			input[1] = b;
			//input[b] = 1;
		}

		std::cout << std::endl;
		// Input values
		showVectorVals("  Inputs:", input);
		net.feedForward(input);

		// Collect the results
		result = net.getResults();
		showVectorVals("  Outputs:", result);
		std::cout << std::endl << std::endl;

		size_t index = Utils::getMaxValueIndex(result);
		std::cout << "  Chosen value: [" << index << "] " << result[index] << std::endl;

		//input[a] = 0;
		//input[b] = 0;

	}

	/*
	while(a != -1 || b != -1) {

		std::cout << "Input -1 to exit." << std::endl;
		std::cout << "a: ";
		std::cin >> a;
		if(a == -1) {
			break;
		}
		input[0] = a;

		std::cout << "b: " ;
		std::cin >> b;
		if(b == -1) {
			break;
		}
		input[1] = b;

		std::cout << std::endl;
		// Input values
		showVectorVals("  Inputs:", input);
		network.feedForward(input);

		// Collect the results
		result = network.getResults();
		showVectorVals("  Outputs:", result);
		std::cout << std::endl << std::endl;

		size_t index = getMaxValIndex(result);
		std::cout << "  Chosen value: [" << index << "] " << result[index] << std::endl;

	}
	*/

#endif

	std::cout << std::endl << "Done" << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
