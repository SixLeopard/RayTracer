#ifndef Vec3_H
#define Vec3_H

#include <cmath>
#include <iostream>

class Vec3 {
    public:
        public:
            Vec3() : x(0), y(0), z(0) {}
            Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
            float x;
            float y;
            float z;

            Vec3 operator-() const { return Vec3(-x, -y, -z); }

            Vec3& operator+=(const Vec3 &v) {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            Vec3& operator*=(const float t) {
                x *= t;
                y *= t;
                z *= t;
                return *this;
            }

            Vec3& operator/=(const float t) {
                return *this *= 1/t;
            }

            float length_squared() const {
                return x*x + y*y + z*z;
            }

            float length() const {
                return sqrt(length_squared());
            }
};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator*(float t, const Vec3 &v) {
    return Vec3(t*v.x, t*v.y, t*v.z);
}

inline Vec3 operator*(const Vec3 &v, float t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, float t) {
    return (1/t) * v;
}

inline float dot(const Vec3 &u, const Vec3 &v) {
    return u.x * v.x
         + u.y * v.y
         + u.z * v.z;
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

inline Vec3 add_scalar(const Vec3 &v, const float t) {
                return Vec3(v.x+t, v.y+t, v.z+t);
            }

#endif