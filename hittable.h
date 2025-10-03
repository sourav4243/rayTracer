#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
    public:
        point3 p;   // hit point in 3D place
        vec3 normal;  // surface normal at hit point
        double t;   // ray eqn: p(t) = origin + t*direction 
};


class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif