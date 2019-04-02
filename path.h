#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "point.h"


class Path{

private:

    std::vector<Point> rep;
    
public:
    
    Path(): rep(std::vector<Point>()){}
    Path(int dim): rep(std::vector<Point>(dim)){}
    Path(std::vector<Point> other): rep(other){}
    
    ~Path() = default;
    
    Path(const Path & path);
    Path & operator =(const Path & path);

    inline int size() const{
	return rep.size();
    }

    inline std::vector<Point> get_rep() const{
	return rep;
    }

    void random_path();

    // Compute fitness function
    float comp_fitness() const;

    // Ordered Crossover
    Path crossover(const Path & other) const;

    // For mutation, we use swap to assert still being a path
    inline void swap(int x1, int x2){
	std::swap(rep[x1], rep[x2]);
    }

    inline bool operator ==(const Path & other) const{
      return rep == other.rep;
    }
    
    inline bool operator !=(const Path & other) const{
	return !(*this == other);
    }

    friend std::ostream & operator <<(std::ostream & os, const Path & L);
};

#endif
