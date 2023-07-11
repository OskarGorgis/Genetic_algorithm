#include "CIndividual.h"
using namespace std;

CIndividual::CIndividual(int size, RandomNumberGenerator* RNG01, RandomNumberGenerator* rng100)
{
	genotype.resize(size);
	fitness = DEF_VAL;
	generateGenotype(RNG01);
	RNG100 = rng100;
}

CIndividual::CIndividual(vector<int> Genotype)
{
	genotype = Genotype;
	fitness = DEF_VAL;
}

CIndividual::~CIndividual()
{

}

int CIndividual::getFitness(const COptymalizationProblem* countingMethod)
{
	if (fitness != -1) return fitness;
	else
	{
		fitness = countingMethod->calculateQualityOfSolution(&genotype);
		return fitness;
	}
}

void CIndividual::mutate(int mutationRate, RandomNumberGenerator* RNG100)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		if (RNG100->operator()() <= mutationRate)
		{
			if (genotype[i] == 0) genotype[i] = 1;
			else genotype[i] = 0;
			fitness = -1;
		}
	}
	
}

std::pair<CIndividual*, CIndividual*> CIndividual::cross(const CIndividual* other) const
{
	vector<int> child1_genotype;
	vector<int> child2_genotype;
	child1_genotype.resize(genotype.size());
	child2_genotype.resize(genotype.size());
	RandomNumberGenerator rnd(0, genotype.size() - 2);
	int cut_place = rnd.operator()();

	for (int i = 0; i < genotype.size()-1; i++)
	{
		if (i <= cut_place)
		{
			child1_genotype[i] = other->genotype[i];
			child2_genotype[i] = genotype[i];
		}
		else
		{
			child1_genotype[i] = genotype[i];
			child2_genotype[i] = other->genotype[i];
		}
	}

	CIndividual* child1 = new CIndividual(child1_genotype);
	CIndividual* child2 = new CIndividual(child2_genotype);

	return std::make_pair(child1, child2);
}

string CIndividual::showGenotype()
{
	string gens = "";
	for (int i = 0; i < genotype.size(); i++)
	{
		gens += " " + to_string(genotype[i]);
	}
	return gens;
}

void CIndividual::showIndividual()
{
	cout << "---Osobnik---\nGenotyp: " << showGenotype() << "\nJakosc rozwiazania: " << fitness << "\n-------------\n\n\n";
}

void CIndividual::generateGenotype(RandomNumberGenerator* RNG)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		genotype[i] = RNG->operator()();
	}
}

std::vector<int>* CIndividual::getGenotype()
{
	return &genotype;
}

CIndividual* CIndividual::copy()
{
	CIndividual* copy = new CIndividual(*this);
	return copy;
}
