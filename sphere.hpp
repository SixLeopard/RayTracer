#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.hpp"
#include "Vector3.hpp"

class sphere: public hittable {
    public:
        sphere() : center(Vec3(0,0,0)), radius(0) {}
        sphere(Vec3 Center, float Radius) : center(Center), radius(Radius) {} 

        Vec3 center;
        float radius;

        virtual bool hit(Ray* ray, double t_min, double t_max, hit_record& rec) const;
};

bool sphere::hit(Ray* ray, double t_min, double t_max, hit_record& rec) const {
    Vec3 oc = ray->position - center;
    float a =ray->direction.length_squared();
    float half_b = dot(oc, ray->direction);
    float c = oc.length_squared() - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    float sqrtd = sqrt(discriminant);

    float root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd)/ a;
        if (root < t_min  || t_max < root) return false;
    }

    rec.t = root;
    rec.p = ray->at(rec.t);
    rec.normal = (rec.p - center) / radius; 
}


#endif