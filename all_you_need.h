#ifndef ALL_YOU_NEED_H
#define ALL_YOU_NEED_H

#include<iostream>
#include<cmath>
#include<limits>
#include<memory>

// C++ std using
using std:: make_shared;
using std:: shared_ptr;

// Constants 
const double infinity = std:: numeric_limits<double> :: infinity();
const double pi = 3.1415926535897932385;

// Utility function
inline double degrees_to_radians(double degrees){
    return degrees * pi / 180;
}

// Common headers
#include "color.h"
#include "vec3.h"
#include "ray.h"

#endif 