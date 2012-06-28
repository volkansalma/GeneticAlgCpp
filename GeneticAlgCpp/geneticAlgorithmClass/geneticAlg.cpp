#include "geneticAlg.h"

bool inline fitness_sort(ga_struct x, ga_struct y) 
{ 
	return (x.fitness < y.fitness); 
}

geneticAlg::geneticAlg(void)
{
	srand(unsigned(time(NULL)));
	init_population(pop_alpha, pop_beta);
	population = &pop_alpha;
	buffer = &pop_beta;
}

geneticAlg::~geneticAlg(void)
{
}

void geneticAlg::init_population(ga_vector &population,ga_vector &buffer ) 
{
	int tsize = GA_TARGET.size();

	for (int i=0; i<GA_POPSIZE; i++) {
		ga_struct citizen;

		citizen.fitness = 0;
		citizen.str.erase();

		for (int j=0; j<tsize; j++)
			citizen.str += (rand() % 90) + 32;

		population.push_back(citizen);
	}

	buffer.resize(GA_POPSIZE);
}

/*
void geneticAlg::calc_fitness(ga_vector &population)
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
*/

ga_vector* geneticAlg::getPopulationVector()
{
	return population;
}

void geneticAlg::setPopulationVector(ga_vector *_population)
{
	population = _population;
}


inline void geneticAlg::sort_by_fitness(ga_vector &population)
{
	sort(population.begin(), population.end(), fitness_sort); 
}

void geneticAlg::elitism(ga_vector &population, ga_vector &buffer, int esize )
{
	for (int i=0; i<esize; i++) {
		buffer[i].str = population[i].str;
		buffer[i].fitness = population[i].fitness;
	}
}

void geneticAlg::mutate(ga_struct &member)
{
	int tsize = GA_TARGET.size();
	int ipos = rand() % tsize;
	int delta = (rand() % 90) + 32; 

	member.str[ipos] = ((member.str[ipos] + delta) % 122);
}

void geneticAlg::mate(ga_vector &population, ga_vector &buffer)
{
	int esize = GA_POPSIZE * GA_ELITRATE;
	int tsize = GA_TARGET.size(), spos, i1, i2;

	elitism(population, buffer, esize);

	// Mate the rest
	for (int i=esize; i<GA_POPSIZE; i++) {
		i1 = rand() % (GA_POPSIZE / 2);
		i2 = rand() % (GA_POPSIZE / 2);
		spos = rand() % tsize;

		buffer[i].str = population[i1].str.substr(0, spos) + 
			population[i2].str.substr(spos, esize - spos);

		if (rand() < GA_MUTATION) mutate(buffer[i]);
	}
}

inline void geneticAlg::print_best(ga_vector &gav)
{ cout << "Best: " << gav[0].str << " (" << gav[0].fitness << ")" << endl; }

inline void geneticAlg::swap(ga_vector *&population,
				 ga_vector *&buffer)
{ ga_vector *temp = population; population = buffer; buffer = temp; }

void geneticAlg::iterate()
{

	
		//calc_fitness(*population);		// calculate fitness
		
		sort_by_fitness(*population);	// sort them
		print_best(*population);		// print the best one

		if ((*population)[0].fitness == 0) return;

		mate(*population, *buffer);		// mate the population together
		swap(population, buffer);		// swap buffers
}