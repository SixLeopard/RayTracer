#ifndef CUBE_H
#define CUBE_H

#include "rectangle.hpp"
#include "hitable_list.hpp"

using std::shared_ptr;
using std::make_shared;

class cube : public hitable  {
    public:
        cube() {}
        cube(const Vec3& corner_1, const Vec3& corener_2, shared_ptr<material> ptr);

        virtual bool hit(Ray* ray, float t_min, float t_max, hit_record& rec) const override;

    public:
        Vec3 box_min;
        Vec3 box_max;
        hitable_list sides;
};


cube::cube(const Vec3& corner_1, const Vec3& corener_2, shared_ptr<material> ptr) {
    box_min = corner_1;
    box_max = corener_2;

    sides.add(make_shared<xy_rect>(corner_1.x, corener_2.x, corner_1.y, corener_2.y, corener_2.z, ptr));
    sides.add(make_shared<xy_rect>(corner_1.x, corener_2.x, corner_1.y, corener_2.y, corner_1.z, ptr));

    sides.add(make_shared<xz_rect>(corner_1.x, corener_2.x, corner_1.z, corener_2.z, corener_2.y, ptr));
    sides.add(make_shared<xz_rect>(corner_1.x, corener_2.x, corner_1.z, corener_2.z, corner_1.y, ptr));

    sides.add(make_shared<yz_rect>(corner_1.y, corener_2.y, corner_1.z, corener_2.z, corener_2.x, ptr));
    sides.add(make_shared<yz_rect>(corner_1.y, corener_2.y, corner_1.z, corener_2.z, corner_1.x, ptr));
}

bool cube::hit(Ray* ray, float t_min, float t_max, hit_record& rec) const {
    return sides.hit(ray, t_min, t_max, rec);
}

#endif