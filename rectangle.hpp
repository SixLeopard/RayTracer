#ifndef REC_H
#define REC_H


#include "hitable.hpp"
#include "Vector3.hpp"
#include "ray.hpp"

using std::shared_ptr;
using std::make_shared;

class xy_rect : public hitable {
    public:
        xy_rect() {}

        xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, 
            shared_ptr<material> mat)
            : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};

        virtual bool hit(Ray* ray, float t_min, float t_max, hit_record& rec) const override;

    public:
        shared_ptr<material> mp;
        float x0, x1, y0, y1, k;
};

class xz_rect : public hitable {
    public:
        xz_rect() {}

        xz_rect(float _x0, float _x1, float _z0, float _z1, float _k,
            shared_ptr<material> mat)
            : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

        virtual bool hit(Ray* ray, float t_min, float t_max, hit_record& rec) const override;

    public:
        shared_ptr<material> mp;
        float x0, x1, z0, z1, k;
};

class yz_rect : public hitable {
    public:
        yz_rect() {}

        yz_rect(float _y0, float _y1, float _z0, float _z1, float _k,
            shared_ptr<material> mat)
            : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

        virtual bool hit(Ray* ray, float t_min, float t_max, hit_record& rec) const override;

    public:
        shared_ptr<material> mp;
        float y0, y1, z0, z1, k;
};

bool xy_rect::hit(Ray* ray, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-ray->position.z) / ray->direction.z;
    if (t < t_min || t > t_max)
        return false;
    auto x = ray->position.x + t*ray->direction.x;
    auto y = ray->position.y + t*ray->direction.y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.t = t;
    auto outward_normal = Vec3(0, 0, 1);
    rec.set_face_normal(ray, outward_normal);
    rec.mat = mp;
    rec.p = ray->at(t);
    return true;
}

bool xz_rect::hit(Ray* ray, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-ray->position.y) / ray->direction.y;
    if (t < t_min || t > t_max)
        return false;
    auto x = ray->position.x + t*ray->direction.x;
    auto z = ray->position.z + t*ray->direction.z;
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.t = t;
    auto outward_normal = Vec3(0, 1, 0);
    rec.set_face_normal(ray, outward_normal);
    rec.mat = mp;
    rec.p = ray->at(t);
    return true;
}

bool yz_rect::hit(Ray* ray, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-ray->position.x) / ray->direction.x;
    if (t < t_min || t > t_max)
        return false;
    auto y = ray->position.y + t*ray->direction.y;
    auto z = ray->position.z + t*ray->direction.z;
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.t = t;
    auto outward_normal = Vec3(1, 0, 0);
    rec.set_face_normal(ray, outward_normal);
    rec.mat = mp;
    rec.p = ray->at(t);
    return true;
}

#endif