#ifndef RT_MATERIAL_H
#define RT_MATERIAL_H

#include "util.hpp"
#include "hitable.hpp"
#include "ray.hpp"

//struct hit_record;

class material {
    public:
        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const = 0;
        
        virtual bool emitted(Vec3& colour_out) const {
            return false;
        }
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

class metallic : public material {
    public:
        metallic(const Vec3& Albedo, float Roughness) : albedo(Albedo), roughness(Roughness <= 1.0f ? Roughness : 1.0f) {}
        Vec3 albedo;
        float roughness;

        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const override {
            Vec3 reflected = reflect(unit_vector(ray_in->direction), rec.normal);
            *ray_out = {rec.p, reflected + roughness*random_in_unit_sphere()};
            attenuation = albedo;
            return (dot(ray_out->direction, rec.normal) > 0);;
        }
};

class emissive : public material {
    public:
        emissive(const Vec3& Albedo, float Intensity) : albedo(Albedo), intensity(Intensity) {}
        Vec3 albedo;
        float intensity;

        virtual bool scatter(Ray *ray_in, const hit_record& rec, Vec3& attenuation, Ray *ray_out) const override {
            return false;
        }

        virtual bool emitted(Vec3& colour_out) const override {
            colour_out = albedo * intensity;
            return true;
        }
};

#endif
