#pragma once
#include <random>
#include <string>

class RandomNumberGenerator {

public:

	//enum NumberType { Integer, Real };

	//RandomNumberGenerator(NumberType numType, double min, double max);
	RandomNumberGenerator(double min, double max);
	~RandomNumberGenerator();


	//void (*uniformDistributionFunc)(std::mt19937 rng);


	double generateNumber();
	void setSeed(std::string seed);
	void setSeed(std::seed_seq seedSeq);
	void setSeed(unsigned seed);

private:
	std::mt19937 rng;
	std::uniform_real_distribution<> dis;

	double min;
	double max;

};
