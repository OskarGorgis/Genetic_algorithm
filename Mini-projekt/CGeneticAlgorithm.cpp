#include "CGeneticAlgorithm.h"

CGeneticAlgorithm::CGeneticAlgorithm()
{
	iMutationRate = DEF_VALUE;
	iCrossingRate = DEF_VALUE;
	iPopulationSize = DEF_VALUE;
	iMaxGenerations = DEF_VALUE;
	cProblemType = NULL;
	RNG01 = new RandomNumberGenerator(0, 1);
	RNG100 = new RandomNumberGenerator(0, 100);
	cBestSolution = NULL;
	veCurrentPopulation = new std::vector<CIndividual*>;
	veNextPopulation = new std::vector<CIndividual*>;
	veCurrentPopulation->reserve(iPopulationSize);
	veNextPopulation->reserve(iPopulationSize);
	
}

CGeneticAlgorithm::CGeneticAlgorithm(int mutationRate, int crossingRate, int populationSize, int maxGenerations, COptymalizationProblem* problemType)
{
	iMutationRate = mutationRate;
	iCrossingRate = crossingRate;
	iPopulationSize = populationSize;
	iMaxGenerations = maxGenerations;
	cProblemType = problemType;
	RNG01 = new RandomNumberGenerator(0, 1);
	RNG100 = new RandomNumberGenerator(0, 100);
	cBestSolution = NULL;
	veCurrentPopulation = new std::vector<CIndividual*>;
	veNextPopulation = new std::vector<CIndividual*>;
	veCurrentPopulation->reserve(iPopulationSize);
	veNextPopulation->reserve(iPopulationSize);
}

CGeneticAlgorithm::~CGeneticAlgorithm()
{
	for (int ii = 0; ii < veCurrentPopulation->size(); ii++)
		delete  veCurrentPopulation->at(ii);
	delete veCurrentPopulation;

	for (int ii = 0; ii < veNextPopulation->size(); ii++)
		delete  veNextPopulation->at(ii);
	delete veNextPopulation;
	delete RNG01;
	delete RNG100;
}

void CGeneticAlgorithm::vRunSymulation()
{
	vCreateFirstPopulation();
	for (int i = 0; i < iMaxGenerations; i++)
	{
		vBreedCurrentPopulation();
		vSwitchPopulations();
		std::cout << "================================= NEW GENERATION NR "; std::cout << i; std::cout << " =========================== \n";
		vChooseBestIndividual();
		//vShowBestIndividual();
		//vShowPopulation();
	}
}

void CGeneticAlgorithm::vShowPopulation()
{
	std::cout << "======================================= Aktualna populacja ================================\n";
	for (int i = 0; i < veCurrentPopulation->size(); i++)
	{
		veCurrentPopulation->at(i)->showIndividual();
	}
}

void CGeneticAlgorithm::vShowBestIndividual()
{
	std::cout << "Najlepszy osobnik: \n";
	cBestSolution->showIndividual();
}

CIndividual* CGeneticAlgorithm::cGetBestSolution()
{
	if (cBestSolution != NULL)
		return cBestSolution;
	else
	{
		vChooseBestIndividual();
		return cBestSolution;
	}
}

void CGeneticAlgorithm::vCreateFirstPopulation()
{
	for (int i = 0; i < iPopulationSize; i++)
	{
		veCurrentPopulation->push_back(new CIndividual(cProblemType->lengthOfGenotype(), RNG01, RNG100));
	}
}

void CGeneticAlgorithm::vBreedCurrentPopulation()
{
	CIndividual* chosen1;
	CIndividual* chosen2;
	std::pair<CIndividual*, CIndividual*> newPair;
	for (int i = 0; i < iPopulationSize; i+=2)
	{
		if (i == 0)
		{
			chosen1 = cGetBestSolution();
			chosen2 = pBetterCandidate();

			newPair = std::make_pair(chosen1->copy(), chosen2->copy());
		}
		else
		{
			chosen1 = pBetterCandidate();
			chosen2 = pBetterCandidate();

			if (iCrossingRate >= RNG100->operator()())
			{
				newPair = chosen1->cross(chosen2);
			}
			else
			{
				newPair = std::make_pair(chosen1->copy(), chosen2->copy());
			}

			newPair.first->mutate(iMutationRate, RNG100);
			newPair.second->mutate(iMutationRate, RNG100);

		}

		newPair.first->getFitness(cProblemType);
		newPair.second->getFitness(cProblemType);

		veNextPopulation->push_back(newPair.first);
		veNextPopulation->push_back(newPair.second);
	}
}

void CGeneticAlgorithm::vChooseBestIndividual()
{
	int fitness = 0;
	int position = 0;
	for (int i = 0; i < iPopulationSize; i++)
	{
		if (veCurrentPopulation->at(i)->getFitness(cProblemType) > fitness)
		{
			fitness = veCurrentPopulation->at(i)->getFitness(cProblemType);
			position = i;
		}
	}
	cBestSolution = veCurrentPopulation->at(position);
}

void CGeneticAlgorithm::vSwitchPopulations()
{
	for (int i = 0; i < iPopulationSize; i++)
		delete veCurrentPopulation->at(i);
	veCurrentPopulation->clear();

	std::vector<CIndividual*>* temp = veCurrentPopulation;
	veCurrentPopulation = veNextPopulation;
	veNextPopulation = temp;
	vChooseBestIndividual();

}

CIndividual* CGeneticAlgorithm::pBetterCandidate()
{
	RandomNumberGenerator random(0, iPopulationSize - 1);
	CIndividual* chosen1;
	CIndividual* chosen2;
	chosen1 = veCurrentPopulation->at(random.operator()());
	chosen2 = veCurrentPopulation->at(random.operator()());
	for (int i = 0; i <= iPopulationSize / 10; i++)
	{
		chosen1 = veCurrentPopulation->at(random.operator()());
		chosen2 = veCurrentPopulation->at(random.operator()());
		if ((chosen1->getFitness(cProblemType) > 0 || chosen2->getFitness(cProblemType)) && chosen1->getFitness(cProblemType) > chosen2->getFitness(cProblemType))
			return chosen1;
		else
			return chosen2;

	}
	return chosen1;
}
	
