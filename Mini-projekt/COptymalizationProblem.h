#pragma once
#include <vector>

class COptymalizationProblem
{
public:
	virtual int calculateQualityOfSolution(const std::vector<int>* solution)const = 0;
	virtual int lengthOfGenotype() = 0;
	virtual bool isCorrect() = 0;
};