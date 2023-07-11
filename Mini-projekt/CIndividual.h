#pragma once
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include "RandomNumberGenerator.h"
#include "COptymalizationProblem.h"
#include "CKnapsackProblem.h"

class CIndividual
{
public:

	CIndividual(int size, RandomNumberGenerator* RNG01, RandomNumberGenerator* RNG100);
	CIndividual(std::vector<int> Genotype);
	~CIndividual();
	std::vector<int>* getGenotype();
	CIndividual* copy();
	int getFitness(const COptymalizationProblem* countingMethod);
	void mutate(int mutationRate, RandomNumberGenerator* RNG100);
	std::pair<CIndividual*, CIndividual*> cross(const CIndividual* other) const;
	void showIndividual();

private:

	const int DEF_VAL = -1;

	std::vector<int> genotype;
	int fitness;

	RandomNumberGenerator* RNG100;
	std::string showGenotype();
	void generateGenotype(RandomNumberGenerator* RNG01);
};

