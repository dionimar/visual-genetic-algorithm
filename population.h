#ifndef POPULATION_H
#define POPULATION_H

#include <iostream>
#include <vector>
#include <iterator>

#include "point.h"
#include "path.h"
#include "adn.h"

extern const int POPULATION_SIZE;
extern const int POOL_SIZE;
extern const bool ELITISM;
extern const int NUM_ELLIT;

class Population{
    
private:
    
    std::vector<ADN> members;
    std::vector<ADN> pool;
    
public:
    
    int generation_number;
    float entropy;

    Population();
    Population(int num, const std::vector<Point> & initial_points);

    Population(const Population & pop) = default;
    Population & operator =(const Population & pop) = default;

    ~Population() = default;

    void sort();

    void next_generation();

    inline ADN get_best(){
	return members[0];
    }

    inline ADN get_worst(){
	return members.back();
    }

    friend std::ostream & operator <<(std::ostream & os, const Population & pop);
};

#endif
