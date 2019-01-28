#include "pch.h"
#include "TrainingData.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

/*
#ifdef _WIN32
	#include <Windows.h>
#elif __linux__
	#include <unistd.h>
#endif
*/

using namespace std::placeholders;
enum Training { XOR, Mult9 };
Training trainingType = Training::XOR;

TrainingData::TrainingData(const std::string filename, const std::string directory) {

	fs::path filepath = fs::absolute(directory);
	fs::create_directories(filepath);
	filepath.append(filename);

	this->trainingFilePath = filepath;
	switch(trainingType) {
	case Mult9:
		training = std::bind(&TrainingData::mult9Training, this, _1);
		break;
	case XOR:
	default:
		training = std::bind(&TrainingData::xorTraining, this, _1);
		break;
	}

}

TrainingData::~TrainingData() {
	trainingDataFile.close();
}

bool TrainingData::isEof() {
	return trainingDataFile.eof();
}

size_t TrainingData::getTopology(std::vector<unsigned> &topology, std::string labelName) {

	if(!fs::exists(trainingFilePath)) {
		std::cout << "Missing training sets file in path: '" << trainingFilePath.string() << "'" << std::endl;
		std::abort();
	}

	if(!trainingDataFile.is_open()) {
		trainingDataFile.open(trainingFilePath);
		if(!trainingDataFile.is_open()) {
			std::cout << "Could not open the file in path: '" << trainingFilePath.string() << "'" << std::endl;
			std::abort();
		}
	}

	topology.clear();

	std::string line;
	std::getline(trainingDataFile, line);
	std::stringstream strm(line);

	std::string label;
	strm >> label;

	if(this->isEof() || label.compare(labelName) != 0) {
		std::abort();
	}

	while(!strm.eof()) {
		unsigned neuron;
		strm >> neuron;
		topology.push_back(neuron);
	}

	return topology.size();
}

size_t TrainingData::getNeuronValues(std::vector<double>& values, const std::string labelName) {

	if(!fs::exists(trainingFilePath)) {
		std::cout << "Missing training sets file in path: '" << trainingFilePath.string() << "'" << std::endl;
		std::abort();
	}

	if(!trainingDataFile.is_open()) {
		trainingDataFile.open(trainingFilePath);
		if(!trainingDataFile.is_open()) {
			std::cout << "Could not open the file in path: '" << trainingFilePath.string() << "'" << std::endl;
			std::abort();
		}
	}

	values.clear();

	std::string line;
	getline(trainingDataFile, line);
	std::stringstream strm(line);

	std::string label;
	strm >> label;
	if(label.compare(labelName) == 0) {
		double oneValue;
		while(strm >> oneValue) {
			values.push_back(oneValue);
		}
	}

	return values.size();
}

void TrainingData::createRandomData(int trainingSets) {
	training(trainingSets);
}

void TrainingData::xorTraining(int trainingSets) {

	// Random training sets for XOR
	// Two inputs and one output

	std::ofstream file(trainingFilePath);
	if(file.is_open()) {

		int numInputs = 2;
		int numOutputs = 1;

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<> dis(0, numInputs - 1);

		file << "topology: " << numInputs << " 4 " << numOutputs << std::endl;
		for(int i = trainingSets; i > 0; --i) {

			int n1 = dis(rng);
			int n2 = dis(rng);
			int t = n1 ^ n2; // Should be 0 or 1

			file << "in:";
			for(int i = 0; i < numInputs; i++) {
				file << " " << (n1 == i || n2 == i);
			}
			file << std::endl;

			file << "out:";
			for(int i = 0; i < numOutputs; i++) {
				file << " " << (t == i);
			}
			file << std::endl;

		}

		file.close();

	} else {
		std::cout << "Unable to open file";
	}

}

void TrainingData::mult9Training(int trainingSets) {

	std::ofstream file(trainingFilePath);
	if(file.is_open()) {

		int numInputs = 11;
		int numOutputs = 82;

		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<> dis(0, numInputs - 1);

		file << "topology: " << numInputs << " 100 50 " << numOutputs << std::endl;
		for(int i = trainingSets; i > 0; --i) {
			int n1 = dis(rng);
			int n2 = dis(rng);
			int t = (n1 * n2);

			file << "in:";
			for(int i = 0; i < numInputs; i++) {
				file << " " << (n1 == i || n2 == i);
			}
			file << std::endl;

			file << "out:";
			for(int i = 0; i < numOutputs; i++) {
				file << " " << (t == i);
			}
			file << std::endl;

		}

		file.close();

	} else {
		std::cout << "Unable to open file";
	}

}

//std::string TrainingData::getExePath() {
//	/*
//	// Current working directory
//	char path[FILENAME_MAX];
//	GetCurrentDir(path, sizeof(path));
//	return std::string(path);
//	*/
//	/*
//#ifdef _WIN32
//	char path[MAX_PATH];
//	size_t len = sizeof(path);
//	
//	int bytes = GetModuleFileName(NULL, path, len);
//	//return (bytes == 0) ? -1 : bytes;
//#elif __linux__
//	char path[PATH_MAX];
//	size_t len = sizeof(path);
//
//	char szTmp[32];
//	sprintf(szTmp, "/proc/%d/exe", getpid());
//
//	int bytes = MIN(readlink(szTmp, path, len), len - 1);
//	//if(bytes >= 0) {
//	//	path[bytes] = '\0';
//	//}
//	//return bytes;
//#endif
//	//std::string directory = path;
//	//size_t lastSeparator = directory.rfind(separator());
//	//if(std::string::npos != lastSeparator) {
//	//	directory = filename.substr(0, lastSeparator);
//	//}
//	*/
//	fs::path directory = fs::current_path();
//	if(!fs::is_directory(directory)) {
//		directory = directory.parent_path();
//	}
//
//	return directory.string();
//}