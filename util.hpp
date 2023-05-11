#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

inline float random_float() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
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

struct Colour {
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

inline float degrees_to_radians(float degrees) {
    return degrees * PI / 180.0;
}

#endif