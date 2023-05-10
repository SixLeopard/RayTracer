#ifndef RAY_H
#define RAY_H

#include "Vector3.hpp"

struct Ray {
    Vec3 position;
    Vec3 direction;

    Vec3 at(float t){
        return position + direction * t;
    };
};

#endif