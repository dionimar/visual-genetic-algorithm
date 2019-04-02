#ifndef ADN_H
#define ADN_H

#include <iostream>
#include <vector>

#include "point.h"
#include "path.h"

extern const float MUTATION_RATE;

class ADN{
    
private:
    
    Path rep;
    
public:
    
    float fitness;

    ADN(): rep(Path()), fitness(0){}
    ADN(int size): rep(Path(size)), fitness(0){}
    ADN(std::vector<Point> _rep): rep(Path(_rep)), fitness(0){}
    ADN(Path & _path): rep(_path), fitness(0){}

    ~ADN() = default;

    ADN(const ADN & adn);
    ADN & operator =(const ADN & adn);

    inline int size() const{
	return rep.size();
    }

    inline Path get_rep() const{
	return rep;
    }
    
    // Random permutation of Path points
    void init_random();

    // Compute path length (fitness)
    void comp_fitness();

    // Swap two random vertex of path
    void mutate();

    ADN crossover(ADN & other);

    // Order from fitness function to sort population
    inline bool operator <(const ADN & other) const{
      return fitness < other.fitness;
    }
    
    bool operator ==(const ADN & other) const;

    friend std::ostream & operator <<(std::ostream & os, const ADN & adn);
};

#endif
