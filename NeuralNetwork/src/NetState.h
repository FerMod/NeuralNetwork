#pragma once
#include <filesystem>
#include <string>
#include "NeuralNet.h"

namespace NeuralNetwork {

	namespace fs = std::filesystem;

	class NetState {
	public:
		NetState(const std::string &putputFolder);
		~NetState();

		void saveNetworkState(const NeuralNet &net, const std::string &filename);
		NeuralNet loadNetworkState(const std::string &filename);

	private:
		fs::path putputFolder;
	};

}
