// The ray class
// P(t)  = A + tb ,  P is 3D point, A is ray origin, 
// t is random number to change and move along 3D line, 
// and b is ray direction

#ifndef RAY_H
#define RAY_H

#include "math/vec3.h"

class ray{
    private:
        point3 orig;
        vec3 dir;
    public: 
        ray(){}

        ray(const point3& origin, const vec3& direction): orig(origin), dir(direction){}

        const point3& origin() const { return orig; }
        const vec3& direction() const { return dir; }

        point3 at(double t) const {
            return orig+t*dir;
        } 
};

#endif