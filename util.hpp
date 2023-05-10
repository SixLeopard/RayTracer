#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

inline float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    return min + (max-min)*random_float();
}

const double infinity = std::numeric_limits<double>::infinity();

inline float clamp(float x, float min, float max){
    if (x < min) 
        return min;
    if (x > max)
        return max;
    return x;
}

typedef struct Colour {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    Colour& operator+=(const Colour &c){
        r += c.r;
        g += c.g;
        b += c.b;
        a += c.a;
        return *this;
    }
};

#endif