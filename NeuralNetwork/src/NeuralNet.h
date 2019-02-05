#pragma once
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "ActivationFunction.h"
#include "LayerAlias.h"

namespace NeuralNetwork {

	enum TrainingType { Epoch, MinErr };

	class NeuralNet {
	public:
		NeuralNet();
		NeuralNet(const std::vector<unsigned> &topology);

		void feedForward(const std::vector<double> &inputVals);
		void backProp(const std::vector<double> &targetVals);
		std::vector<double> getResults() const;
		void calcHiddenLayerGradients();
		void updateConnectionWeights();

		void calcOutputLayerGradients(const std::vector<double> &targetVals);
		std::vector<Layer> getLayers() const;
		void setLayers(const std::vector<Layer> &layers);

		void setLearningRate(double learningRate);
		double getLearningRate() const;

		void setMomentum(double momentum);
		double getMomentum() const;

		void calculateOverallNetError(const std::vector<double> &targetVals);
		double getError() const;
		void setError(double error);

		void calculateRecentAverageError(double smoothingFactor, double error);
		double getRecentAverageError() const;
		void setRecentAverageError(double recentAverageError);

		double getRecentAverageSmoothingFactor() const;
		void setRecentAverageSmoothingFactor(double recentAverageSmoothingFactor);

		friend void to_json(nlohmann::json& j, const NeuralNet& nn);
		friend void from_json(const nlohmann::json& j, NeuralNet& nn);

	private:

		// Activation or also called transfer function
		std::unique_ptr<ActivationFunction> activationFunction;

		// 0 = Input Layer
		// n-1 = Hidden Layer
		// n = Output Layer
		std::vector<Layer> layers;

		/*
		Overall net training rate. [0.0 ... 1.0]

		e.g:
		0.0 -> Slow learner
		0.2 -> Medium learner
		1.0 -> Fast learner
		*/
		double learningRate;

		/*
		Inertia, multiplier of last weight change. [0.0 ... 1.0]

		e.g:
		0.0 -> No momentum
		0.5 -> Moderate momentum
		*/
		double momentum;

		double error;
		double recentAverageError;
		double recentAverageSmoothingFactor;
		TrainingType trainingType;

	};

}
