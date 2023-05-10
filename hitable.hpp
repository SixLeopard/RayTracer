#ifndef HITABLE_H
#define HITABLE_H

#include "Vector3.hpp"

struct hit_record {
    Vec3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(Ray* ray, const Vec3& outward_normal) {
        front_face = dot(ray->direction, outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(Ray* ray, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif