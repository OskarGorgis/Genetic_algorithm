#pragma once
#include "COptymalizationProblem.h"
#include <iostream>
#include <vector>
#include "CIndividual.h"
class CGeneticAlgorithm
{
public:

	CGeneticAlgorithm();
	CGeneticAlgorithm(int mutationRate, int crossingRate, int populationSize, int maxGenerations, COptymalizationProblem* problemType);
	~CGeneticAlgorithm();
	void vRunSymulation();
	void vShowPopulation();
	void vShowBestIndividual();
	CIndividual* cGetBestSolution();

private:

	void vCreateFirstPopulation();
	void vBreedCurrentPopulation();
	void vChooseBestIndividual();
	void vSwitchPopulations();
	CIndividual* pBetterCandidate();

	const int DEF_VALUE = 1;

	std::vector<CIndividual*>* veCurrentPopulation;
	std::vector<CIndividual*>* veNextPopulation;
	CIndividual* cBestSolution;
	COptymalizationProblem* cProblemType;
	RandomNumberGenerator* RNG01;
	RandomNumberGenerator* RNG100;
	int iMutationRate;
	int iCrossingRate;
	int iPopulationSize;
	int iMaxGenerations;

};

