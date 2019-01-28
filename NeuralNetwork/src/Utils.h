#pragma once
#include <string>
#include <sstream>
#include <vector>

namespace NeuralNetwork::Utils {

	template<typename T>
	std::string vectorToString(const std::vector<T> &vect, std::string start, std::string separator, std::string end) {
		std::ostringstream os;
		size_t size = vect.size();
		if(size > 0) {
			os << start;
			for(size_t i = 0; i < size; ++i) {
				os << std::to_string(vect[i]) << ((i + 1 != size) ? separator : end);
			}
		}
		return os.str();
	}

	template<typename T>
	size_t getMaxValueIndex(const std::vector<T> &vect) {
		size_t maxValIndex = 0;
		for(size_t i = 0; i < vect.size(); i++) {
			if(vect[maxValIndex] < vect[i]) {
				maxValIndex = i;
			}
		}
		return maxValIndex;
	}

}
