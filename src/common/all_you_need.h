#ifndef ALL_YOU_NEED_H
#define ALL_YOU_NEED_H

#include<iostream>
#include<cmath>
#include<limits>
#include<memory>
#include<random>
#include<thread>

// C++ std using
using std:: make_shared;
using std:: shared_ptr;

// Constants 
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility function
inline double degrees_to_radians(double degrees){
    return degrees * pi / 180;
}

inline double random_double(){
    // Returns a random real in [0, 1)
    static thread_local std::mt19937 generator(
        []{
            uint64_t x = std::hash<std::thread::id>{}(std::this_thread::get_id());
            x ^= x >> 30;
            x *= 0xbf58476d1ce4e5b9ULL;
            x ^= x >> 27;
            x *= 0x94d049bb133111ebULL;
            x ^= x >> 31;
            return (uint32_t)x;
        }()
    );

    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(double min, double max){
    // Returns a random real in [min, max)
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min, max]
    return int(random_double(min, max+1));
}

// Common headers
#include "core/color.h"
#include "math/interval.h"
#include "math/vec3.h"
#include "core/ray.h"

#endif 