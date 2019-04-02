#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>

struct Point{
public:
    float x, y;
    
    Point(): x(0), y(0){}
    Point(float _x, float _y): x(_x), y(_y){}
    
    ~Point() = default;
    
    Point(const Point & P);
    Point & operator=(const Point & P);

    inline bool operator == (const Point & P) const{
	return (x == P.x && y == P.y);
    }

    inline bool operator != (const Point & P) const{
	return !(*this == P);
    }

};

std::ostream & operator <<(std::ostream & os, const Point & P);

inline float dist(const Point & a, const Point & b){
    return sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2));
}

#endif
