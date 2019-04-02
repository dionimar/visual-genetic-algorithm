#include <iostream>
#include <assert.h>

#include "point.h"

Point::Point(const Point & P){
    this->x = P.x;
    this->y = P.y;
}

Point & Point::operator =(const Point & P){
    this->x = P.x;
    this->y = P.y;
    return *this;
}

std::ostream & operator <<(std::ostream & os, const Point & P){
    os << "(" << P.x;
    os << ", ";
    os << P.y << ")";
    return os;
}
