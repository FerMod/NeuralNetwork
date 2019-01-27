#pragma once
#include "json.hpp"

namespace NeuralNetwork {

	class Connection {
	public:

		Connection();
		Connection(double weight, double deltaWeight);

		friend void to_json(nlohmann::json& j, const Connection& c);
		friend void from_json(const nlohmann::json& j, Connection& c);

		double weight;
		double deltaWeight;

	};

}
