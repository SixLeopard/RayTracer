#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

class Vector3 {
    public:
        public:
            Vector3() : x(0), y(0), z(0) {}
            Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
            float x;
            float y;
            float z;

            Vector3 operator-() const { return Vector3(-x, -y, -z); }

            Vector3& operator+=(const Vector3 &v) {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            Vector3& operator*=(const double t) {
                x *= t;
                y *= t;
                z *= t;
                return *this;
            }

            Vector3& operator/=(const double t) {
                return *this *= 1/t;
            }

            double length_squared() const {
                return x*x + y*y + z*z;
            }

            double length() const {
                return sqrt(length_squared());
            }
};

#endif