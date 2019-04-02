#include <iostream>
#include <vector>
#include <random>

#include "path.h"
#include "point.h"

std::random_device r_device;
std::mt19937 gen(r_device());

int random_in(int a, int b){
    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}

Path::Path(const Path & path){
    rep = std::move(path.rep);
}

Path & Path::operator =(const Path & path){
    if(path != *this){
	this->rep = path.rep;
	return *this;
    }
}

void Path::random_path(){
    std::random_shuffle(rep.begin(), rep.end());
}

float Path::comp_fitness() const{
    float result = 0;
    
    for(auto it = rep.begin()+1; it != rep.end(); ++it){
	result += dist(*it, *(it-1));
    }
    result += dist(rep.front(), rep.back()); // Distance to close the path
    return result;
}

Path Path::crossover(const Path & other) const{
    if(*this == other){
	return *this;
    }
    
    else{
	int pos_begin = random_in(0, rep.size()-2); // Random in [0...N-1)
	int pos_end = random_in(pos_begin, rep.size()-1); // Random in [pos_begin...N)
	pos_end = (pos_begin<pos_end) ? pos_end : pos_end+1;    

	// Construct a copy of rep without selected elements
	// Ready for append to the new child in order
	std::vector<Point> new_rep_to_construct = other.rep;

	for(auto it = rep.begin() + pos_begin; it != rep.begin()+pos_end; ++it){
	    auto it_del = std::find(new_rep_to_construct.begin(), new_rep_to_construct.end(), *it);
	    if(it_del != new_rep_to_construct.end()){
		new_rep_to_construct.erase(it_del);
	    }
	}

	// Insert in random position
	int pos_insert_rand = random_in(0, rep.size() - (pos_end - pos_begin));
	new_rep_to_construct.insert(new_rep_to_construct.begin()+pos_insert_rand, rep.begin()+pos_begin, rep.begin()+pos_end);
	return Path(new_rep_to_construct);
    }
}

std::ostream & operator <<(std::ostream & os, const Path & L){
    for(const auto& elem : L.rep){
	os << elem << " ,";
    }
    return os;
}
