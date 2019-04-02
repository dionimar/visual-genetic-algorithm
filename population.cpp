#include <iostream>
#include <vector>
#include <assert.h>
#include <list>
#include <random>
#include <algorithm>
#include <cmath>

#include "point.h"
#include "path.h"
#include "adn.h"
#include "population.h"

Population::Population(): generation_number(0), members(std::vector<ADN>()), pool(std::vector<ADN>()), entropy(0){}
Population::Population(int num, const std::vector<Point> & initial_points): generation_number(0), entropy(0){
	members = std::vector<ADN>(num, ADN(initial_points));
	if(POOL_SIZE <= num){
	    pool = std::vector<ADN>(POOL_SIZE);
	}
	else{
	    pool = std::vector<ADN>(num);
	}
	
	for(auto&&elem : members){
	    elem.init_random();
	    elem.comp_fitness();
	}
	sort();
}

// Sort population by the order given by the class ADN
void Population::sort(){
    std::stable_sort(members.begin(), members.end());
}

void Population::next_generation(){
    bool update_entropy = generation_number % 100 == 0;

    // Normalize fitness to percentaje
    float total_fitness = 0;
    for(auto it = members.begin(); it != members.end(); ++it){
	total_fitness += it->fitness;
    }

    // Construct the pool with n-times elements (probability)
    auto it_pool = pool.begin();
    for(auto it = members.begin(); it != members.end() && it_pool != pool.end(); ++it){
	
	int times = static_cast<int>(it->fitness/total_fitness*(pool.size())-1);
	times = (times >= 1) ? times : 1; // In first generation, fitness can be float in (0,1)
	
	while(times > 0){
	    *it_pool = *it;
	    ++it_pool;
	    times--;
	}
    }

    int i = (ELITISM) ? NUM_ELLIT : 0;
    while(i < members.size()){
	int rand_pos_pool1 = rand() % pool.size();
	int rand_pos_pool2 = rand() % pool.size();
	// DIFERENT random numbers
	while(rand_pos_pool2 == rand_pos_pool1){
	    rand_pos_pool2 = rand() % pool.size();
	}

	if(i != rand_pos_pool1 && i != rand_pos_pool2){
	    members[i] = pool[rand_pos_pool1].crossover(pool[rand_pos_pool2]);
	    members[i].mutate();
	    members[i].comp_fitness();
	}
	i++;
    }
    generation_number++;
    sort();
}
    
std::ostream & operator <<(std::ostream & os, const Population & pop){
    for(const auto& elem : pop.members){
	os << elem;
	os << "    fitness: " << elem.fitness;
	os <<std::endl;
    }
    return os;
}
