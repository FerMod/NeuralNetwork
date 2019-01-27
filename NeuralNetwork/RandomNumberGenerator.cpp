#include "pch.h"
#include "RandomNumberGenerator.hpp"

#include <random>
#include <string>

//RandomNumberGenerator::RandomNumberGenerator(NumberType numType, double min, double max): min(min), max(max) {
//	
//	// Only used once to initialise (seed) engine
//	std::random_device rd;
//	setSeed(rd());
//
//	switch(numType)	{
//	case Integer:
//		std::uniform_int_distribution<> dis(min, max);
//		break;
//	case Real:
//	default:
//		std::uniform_real_distribution<> dis(min, max);
//		break;
//	}
//
//}

RandomNumberGenerator::RandomNumberGenerator(double min, double max) {

	// Only used once to initialise (seed) engine
	std::random_device rd;
	setSeed(rd());

	// Guaranteed unbiased
	dis = std::uniform_real_distribution<>(min, max);

}

double RandomNumberGenerator::generateNumber() {
	return dis(rng);
}

void RandomNumberGenerator::setSeed(std::string seed) {
	std::seed_seq seedSeq(seed.begin(), seed.end());
	rng.seed(seedSeq);
}

void RandomNumberGenerator::setSeed(std::seed_seq seedSeq) {
	rng.seed(seedSeq);
}

void RandomNumberGenerator::setSeed(unsigned seed) {
	rng.seed(seed);
}

RandomNumberGenerator::~RandomNumberGenerator() {
}
