#pragma once
#include <vector>					// for vector class
#include <string>					// for string class
#include <algorithm>				// for sort algorithm
#include <time.h>					// for random seed
#include <math.h>					// for abs()
#include <iostream>

using namespace std;

struct ga_struct 
{
	string str;						// çözüm
	unsigned int fitness;			// its fitness
};



#define GA_POPSIZE		200	// ga population size
#define GA_MAXITER		16384		// maximum iterations
#define GA_ELITRATE		0.10f		// elitism rate
#define GA_MUTATIONRATE	0.80f		// mutation rate
#define GA_MUTATION		RAND_MAX * GA_MUTATIONRATE
#define GA_TARGET		std::string("Hello world!")

typedef vector<ga_struct> ga_vector;// for brevity

class geneticAlg
{
public:
	geneticAlg(void);
	~geneticAlg(void);
	void iterate();
	ga_vector* getPopulationVector();
	void setPopulationVector(ga_vector *population);


private:
	void init_population(ga_vector &population,ga_vector &buffer);
	void calc_fitness(ga_vector &population);
	
	inline void sort_by_fitness(ga_vector &population);
	void elitism(ga_vector &population, ga_vector &buffer, int esize);
	void mutate(ga_struct &member);
	void mate(ga_vector &population, ga_vector &buffer);
	inline void print_best(ga_vector &gav);
	inline void swap(ga_vector *&population,ga_vector *&buffer);

	ga_vector pop_alpha, pop_beta;
	ga_vector *population, *buffer;
	

};
