#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "util.hpp"
#include "hitable.hpp"
#include "ray.hpp"

//struct hit_record;

class material {
    public:
        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const = 0;
};

class diffuse : public material {
    public:
        diffuse(const Vec3& Albedo) : albedo(Albedo) {}
        Vec3 albedo;

        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const override {
            Vec3 scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()){
                scatter_direction = rec.normal;
            }

            *ray_out = {rec.p, scatter_direction};
            attenuation = albedo;
            return true;
        }
};

class specular : public material {
    public:
        specular(const Vec3& Albedo) : albedo(Albedo) {}
        Vec3 albedo;

        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const override {
            Vec3 reflected = reflect(unit_vector(ray_in->direction), rec.normal);
            *ray_out = {rec.p, reflected};
            attenuation = albedo;
            return (dot(ray_out->direction, rec.normal) > 0);;
        }
};

#endif
