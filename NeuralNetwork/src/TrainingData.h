#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

class TrainingData {
public:
	TrainingData(const std::string filename, const std::string directory);

	~TrainingData();

	bool isEof();
	size_t getTopology(std::vector<unsigned> &topology, const std::string labelName);

	// Returns the number of input values stored in the file
	size_t getNeuronValues(std::vector<double> &values, const std::string labelName);

	void createRandomData(int trainingSets);

	//std::string getExePath();

private:

	std::function<void(int)> training;
	void xorTraining(int trainingSets);
	void mult9Training(int trainingSets);

	fs::path outputDirPath;
	fs::path trainingFilePath;
	std::ifstream trainingDataFile;

};

