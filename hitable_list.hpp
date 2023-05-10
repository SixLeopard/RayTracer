#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hitable.hpp"
#include "ray.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hitable_list : public hitable {
    public:
        hitable_list() {}
        hitable_list(shared_ptr<hitable> object) {add(object);}
        std::vector<shared_ptr<hitable>> objects;

        void clear() {
            objects.clear();
        }

        void add(shared_ptr<hitable> object) {
            objects.push_back(object);
        }

        virtual bool hit (
            Ray* ray,
            float t_min,
            float t_max,
            hit_record& rec
        ) const override;
};

bool hitable_list::hit(Ray* ray, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    float closet_so_far = t_max;

    for (const auto& object: objects){
        if (object->hit(ray, t_min, closet_so_far, temp_rec)){
            hit_anything = true;
            closet_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif