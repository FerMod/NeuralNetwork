#include "pch.h"
#include "Connection.h"
#include "../lib/nlohmann/ordered_json.hpp"

using namespace NeuralNetwork;
using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

Connection::Connection(): Connection(0.0, 0.0) {
}

Connection::Connection(double weight, double deltaWeight): weight(weight), deltaWeight(deltaWeight) {
}

void NeuralNetwork::to_json(json& j, const Connection& c) {
	j = ordered_json {{"weight", c.weight}, {"deltaWeight", c.deltaWeight}};
}

void NeuralNetwork::from_json(const json& j, Connection& c) {
	j.at("weight").get_to(c.weight);
	j.at("deltaWeight").get_to(c.deltaWeight);
}
