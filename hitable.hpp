#ifndef HITABLE_H
#define HITABLE_H

#include "Vector3.hpp"
//#include "material.hpp"

using std::shared_ptr;
using std::make_shared;

class material;

struct hit_record {
    Vec3 p;
    Vec3 normal;
    shared_ptr<material> mat;
    double t;
    bool front_face;

    inline void set_face_normal(Ray* ray, const Vec3& outward_normal) {
        front_face = dot(ray->direction, outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hitable {
    public:
        virtual bool hit(Ray* ray, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif