#include <iostream>
#include <vector>
#include <random>

#include "point.h"
#include "path.h"
#include "adn.h"

std::default_random_engine generator;
std::bernoulli_distribution distribution(MUTATION_RATE);

ADN::ADN(const ADN & adn){
    this->rep = adn.rep;
    this-> fitness = adn.fitness;
}

ADN & ADN::operator =(const ADN & adn){
    this->rep = adn.rep;
    this->fitness = adn.fitness;
    return *this;
}

// Random permutation of Path points
void ADN::init_random(){
    rep.random_path();
}

// Compute path length (fitness)
void ADN::comp_fitness(){
    fitness = rep.comp_fitness();
}

// Swap two random vertex of path
void ADN::mutate(){
    if(distribution(generator)){
        int x1 = rand() % rep.size();
        int x2 = x1 + (rand() % (rep.size() - x1));
	rep.swap(x1, x2);
    }
}

// Crates new ADN from parents preserving the order
ADN ADN::crossover(ADN & other){
	Path new_path = rep.crossover(other.rep);
	return ADN(new_path);
}

bool ADN::operator ==(const ADN & other) const{
    return rep == other.rep;
}

std::ostream & operator <<(std::ostream & os, const ADN & adn){
    os << adn.rep;
    return os;
}
