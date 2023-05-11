#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.hpp"
#include "ray.hpp"

class rt_camera {
    public:
        rt_camera() {
            origin = Vec3(-3.5,2,1);
            image_width = 1920;
            image_height = 1080;
            focal_distance = image_width;
            rotation = Vec3(-40,-20,0);
        }

        Ray get_ray(int x, int y) const {
            Vec3 direction = Vec3((((float)x)-(image_width/2)),(-(float)y+(image_height/2)),-image_width);
            Vec3 x_axis = Vec3(1,0,0);
            Vec3 y_axis = Vec3(0,1,0);
            Vec3 z_axis = Vec3(0,0,1);
            direction.rotate(y_axis, rotation.x);
            x_axis.rotate(y_axis, rotation.x);
            direction.rotate(x_axis, rotation.y);
            z_axis.rotate(y_axis, rotation.x);
            z_axis.rotate(x_axis, rotation.y);
            direction.rotate(z_axis, rotation.z);
            return {origin, unit_vector(direction)};
        }

    private:
        Vec3 origin;
        int image_width;
        int image_height;
        float focal_distance;
        Vec3 rotation;
};


#endif