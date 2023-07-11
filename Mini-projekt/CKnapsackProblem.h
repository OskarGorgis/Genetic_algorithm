#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "COptymalizationProblem.h"

class CKnapsackProblem: public COptymalizationProblem
{
public:

	CKnapsackProblem(int knapsackSize);
	CKnapsackProblem(int knapsackSize, std::vector<int>* values, std::vector<int>* sizes);
	CKnapsackProblem(std::string fileName);
	~CKnapsackProblem();
	std::vector<int>* getValues();
	std::vector<int>* getSizes();
	bool isCorrect();
	bool bCheckCorrectness();
	int iLoadFromFile(std::string fileName);
	int calculateQualityOfSolution(const std::vector<int>* genotype) const;
	int lengthOfGenotype();

private:

	const int DEF_AMOUNT = 1;

	int iKnapsackSize;
	bool bIsQuantityCorrect;
	bool bIsTablesCorrect;
	std::vector<int>* tValues;
	std::vector<int>* tSizes;
 
};

