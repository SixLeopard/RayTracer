#ifndef Vec3_H
#define Vec3_H

#include <cmath>
#include <iostream>

#include "util.hpp"

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

            inline static Vec3 random() {
                return Vec3(random_float(), random_float(), random_float());
            }

            inline static Vec3 random(float min, float max){
                return Vec3(random_float(min, max), random_float(min, max), random_float(min, max));
            }

            bool near_zero() const {
                const auto s = 1e-8;
                return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
            }
            void rotate(Vec3 axis, float angle)
            {
                angle = degrees_to_radians(angle);
                // Using Euler-Rodrigues Formula
                // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula
                Vec3 v = Vec3(x,y,z);

                Vec3 result = v;

                // Vector3Normalize(axis);
                float length = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
                if (length == 0.0f) length = 1.0f;
                float ilength = 1.0f / length;
                axis.x *= ilength;
                axis.y *= ilength;
                axis.z *= ilength;

                angle /= 2.0f;
                float a = sinf(angle);
                float b = axis.x * a;
                float c = axis.y * a;
                float d = axis.z * a;
                a = cosf(angle);
                Vec3 w = { b, c, d };

                // Vector3CrossProduct(w, v)
                Vec3 wv = { w.y * v.z - w.z * v.y, w.z * v.x - w.x * v.z, w.x * v.y - w.y * v.x };

                // Vector3CrossProduct(w, wv)
                Vec3 wwv = { w.y * wv.z - w.z * wv.y, w.z * wv.x - w.x * wv.z, w.x * wv.y - w.y * wv.x };

                // Vector3Scale(wv, 2 * a)
                a *= 2;
                wv.x *= a;
                wv.y *= a;
                wv.z *= a;

                // Vector3Scale(wwv, 2)
                wwv.x *= 2;
                wwv.y *= 2;
                wwv.z *= 2;

                result.x += wv.x;
                result.y += wv.y;
                result.z += wv.z;

                result.x += wwv.x;
                result.y += wwv.y;
                result.z += wwv.z;

                x = result.x;
                y = result.y;
                z = result.z;
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

Vec3 random_in_unit_sphere() {
    while (true){
        Vec3 p = Vec3::random(-1,1);
        if (p.length_squared() >= 1){
            continue;
        }
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
    return v - 2*dot(v,n)*n;
}

Vec3 vec3_clamp(const Vec3& value, const Vec3& min, const Vec3& max){
    return Vec3(clamp(value.x, min.x, max.x),clamp(value.y, min.y, max.y),clamp(value.z, min.z, max.y));
}

Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_float(-1,1), random_float(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif