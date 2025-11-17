#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter (
            const ray& ray_in,
            const hit_record& rec,
            color& attenuation,
            ray& scattered
        ) const {
            return false;
        }
};

#endif