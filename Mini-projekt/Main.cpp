#include <iostream>
#include <string>
#include "CIndividual.h"
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"
#include "COptymalizationProblem.h"
#include "RandomNumberGenerator.h"
using namespace std;

// PARAMETRY SYMULACJI
const int mutation_rate = 10;
const int crossing_rate = 70;
const int population_size = 50;
const int max_generations = 300;

const int knapsack_size = 30;

int main()
{
	vector<int> Values = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> Sizes = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };

	COptymalizationProblem* Problem = new CKnapsackProblem("plik20genow.txt");
	
	if (Problem->isCorrect())
	{
		CGeneticAlgorithm genetic_algorythm(mutation_rate, crossing_rate, population_size, max_generations, Problem);

		genetic_algorythm.vRunSymulation();
		genetic_algorythm.vShowPopulation();
		genetic_algorythm.vShowBestIndividual();

	}
	else
	{
		cout << "B³êdne dane wejœciowe problemu" << endl;
	}
	
	delete  Problem;

	return 0;
}
