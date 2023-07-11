#include "CKnapsackProblem.h"
#define CKNAP_UNABLE_TO_OPEN -1;
#define CKNAP_INVALID_ARGUMENT_ERROR -2;

CKnapsackProblem::CKnapsackProblem(int knapsackSize)
{
	if (knapsackSize <= 0)
	{
		bIsQuantityCorrect = false;
		iKnapsackSize = DEF_AMOUNT;
	}
	else 
	{
		bIsQuantityCorrect = true;
		iKnapsackSize = knapsackSize;
	}

	bIsTablesCorrect = false;
	tValues = NULL;
	tSizes = NULL;
	std::cout << "Wielkosc plecaka: " << iKnapsackSize << std::endl;
}

CKnapsackProblem::CKnapsackProblem(int knapsackSize, std::vector<int>* values, std::vector<int>* sizes)
{
	if (knapsackSize <= 0)
	{
		bIsQuantityCorrect = false;
		iKnapsackSize = DEF_AMOUNT;
	}
	else
	{
		bIsQuantityCorrect = true;
		iKnapsackSize = knapsackSize;
	}

	iKnapsackSize = knapsackSize;
	tValues = values;
	tSizes = sizes;
	bIsTablesCorrect = bCheckCorrectness();
	std::cout << "Wielkosc plecaka: " << iKnapsackSize << std::endl;
}

CKnapsackProblem::CKnapsackProblem(std::string fileName)
{
	iLoadFromFile(fileName);
	if (iKnapsackSize < 0) bIsQuantityCorrect = false;
	else bIsQuantityCorrect = true;
	bIsTablesCorrect = bCheckCorrectness();
	std::cout << "Wielkosc plecaka: " << iKnapsackSize << std::endl;
}


CKnapsackProblem::~CKnapsackProblem()
{

}

std::vector<int>* CKnapsackProblem::getValues()
{
	return tValues;
}

std::vector<int>* CKnapsackProblem::getSizes()
{
	return tSizes;
}

bool CKnapsackProblem::isCorrect()
{
	if (bIsQuantityCorrect == true && bIsTablesCorrect == true)
		return true;
	else
		return false;
}

bool CKnapsackProblem::bCheckCorrectness()
{
	if (bIsTablesCorrect == true) return true;

	for (int i = 0; i < tValues->size() ; i++)
	{
		if (tValues->at(i) < 0 || tSizes->at(i) < 0)
			return false;
	}
	return true;
}

int CKnapsackProblem::iLoadFromFile(std::string fileName)
{
	std::fstream file(fileName, std::ios_base::in);
	if (!file.is_open()) return CKNAP_UNABLE_TO_OPEN;


	int newKnapsackSize;
	int lenght;

	file >> lenght;

	tValues = new std::vector<int>;
	tSizes = new std::vector<int>;

	file >> newKnapsackSize;
	if (newKnapsackSize < 0) {
		return CKNAP_INVALID_ARGUMENT_ERROR;
	}
	iKnapsackSize = newKnapsackSize;

	int a, b;
	int ii = 0;
	while (file >> a >> b && ii < lenght)
	{
		tValues->push_back(a);
		tSizes->push_back(b);
		//std::cout << a << " " << b << std::endl;
		ii += 1;

	}
	file.close();

	return 0;
}

int CKnapsackProblem::calculateQualityOfSolution(const std::vector<int>* genotype) const
{
	int genotypeSize = 0;
	int genotypeQuality = 0;
	for (int i = 0; i < tValues->size(); i++)
	{
		if (genotype->at(i) == 1)
		{
			genotypeSize += tSizes->at(i);
			genotypeQuality += tValues->at(i);
		}
	}
	if (genotypeSize > iKnapsackSize) return 0;
	return genotypeQuality;

}

int CKnapsackProblem::lengthOfGenotype()
{
	return tValues->size();
}
