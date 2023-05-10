#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.hpp"
#include "ray.hpp"

class rt_camera {
    public:
        rt_camera() {
            origin = Vec3(0,0,0);
            image_width = 1920;
            image_height = 1080;
            focal_distance = image_width;
        }

        Ray get_ray(int x, int y) const {
            Vec3 direction = Vec3((((float)x)-(image_width/2)),(-(float)y+(image_height/2)),-1920);
            return {Vec3(0,0,0), unit_vector(direction)};
        }

    private:
        Vec3 origin;
        int image_width;
        int image_height;
        float focal_distance;
};


#endif