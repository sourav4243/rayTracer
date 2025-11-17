#ifndef HITTABLE_H
#define HITTABLE_H

class material;

class hit_record {
    public:
        point3 p;   // hit point in 3D place
        vec3 normal;  // surface normal at hit point
        shared_ptr<material>mat;
        double t;   // ray eqn: p(t) = origin + t*direction 
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal){
            // Sets the hit record normal vector.
            // Note: the parameter 'outward_normal' is assumed to have unit length.

            // dot product of ray direction and normal tells weather they are in same direction or not
            // Ensure normal always opposes ray direction. 
            // If ray is outside -> keep outward_normal.
            // If ray is inside  -> flip it. Also mark front_face.


            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};


class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif