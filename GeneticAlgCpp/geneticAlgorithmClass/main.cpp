#include "geneticAlg.h"
#include "iostream"

using namespace std;


void calc_fitness(ga_vector &population)
{
string target = GA_TARGET;
int tsize = target.size();
unsigned int fitness;

for (int i=0; i<GA_POPSIZE; i++) {
	fitness = 0;
	
	for (int j=0; j<tsize; j++) {
		fitness += abs(int(population[i].str[j] - target[j]));
	}

	population[i].fitness = fitness;
	}
}


int main()
{
	geneticAlg geneticObj;
	ga_vector *solutions = 0;


	for (int i = 0; i < GA_MAXITER; i++)
	{
		solutions = geneticObj.getPopulationVector();
		calc_fitness(*solutions);
		geneticObj.iterate();
	}
	
	return 0;
}