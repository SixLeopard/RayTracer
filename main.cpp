#include "FastNoiseLite.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <omp.h>

#include "Vector3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "util.hpp"
#include "camera.hpp"
#include "material.hpp"
#include <chrono>

int screenWidth = GetScreenWidth();
int screenHeight = GetScreenHeight();
int imageWidth = 1920;
int imageHeight = 1080;
int progress = 0;
int max_depth = 5;
int sampels_per_pixels = 10;
Texture noiseimagedata; //remove later
Texture raytracedimagedata; //remove later
Texture whitness;

void UpdateDrawFrame(Camera2D* camera);     // Update and Draw one frame
Image GenImageFastNoiseLite(int width, int height, float frequency);
Image RayTracedImage(int width, int height);

Vec3 ray_at(float p, Ray* ray){
    return ray->position + ray->direction * p;
}

float hit_sphere(Vec3 center, float radius, Ray *ray) {
    Vec3 oc = ray->position - center;
    float a =ray->direction.length_squared();
    float half_b = dot(oc, ray->direction);
    float c = oc.length_squared() - radius*radius;
    float discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    }
    else{
        return (-half_b - sqrt(discriminant)) / a;
    }
}

Vec3 ray_colour(Ray *ray, const hitable& scene, int depth){
    hit_record rec;

    if (depth >= max_depth)
        return Vec3(0,0,0);

    if (scene.hit(ray, 0.001f, infinity, rec)){
        Ray scattered;
        Vec3 attenuation;
        if (rec.mat->scatter(ray, rec, attenuation, &scattered)) {
            return attenuation * ray_colour(&scattered, scene, depth+1);
        }
        return Vec3(0,0,0);
    }
    float t = 0.5*(ray->direction.y + 1.0);
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main()
{
    //--------------------------------------------------------------------------------------
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "RayTracer");
    SetTargetFPS(144);

    Image noisedata = GenImageFastNoiseLite(1920, 1080, 0.1);
    noiseimagedata = LoadTextureFromImage(noisedata);
    Image whiteimage = GenImageColor(1920,1080,WHITE);
    whitness = LoadTextureFromImage(whiteimage);

    UnloadImage(noisedata);

    //--------------------------------------------------------------------------------------

    Camera2D camera = { 0 };
    camera.target = (Vector2){0.0f,0.0f};
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    //Shader raytracer = LoadShader(0, "resources/RayTracer.fs");

    hitable_list scene;
    
    auto material_ground = make_shared<diffuse>(Vec3(0.0, 0.1, 0.8));
    auto material_center = make_shared<diffuse>(Vec3(1.0, 1.0, 1.0));
    auto material_left   = make_shared<specular>(Vec3(0.5, 0.5, 0.8));
    auto material_right  = make_shared<specular>(Vec3(0.2, 0.1, 0.8));

    scene.add(make_shared<sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<sphere>(Vec3( 0.0,    0.0, -3.0),   0.5, material_center));
    scene.add(make_shared<sphere>(Vec3(-1.0,    0.0, -3.0),   0.5, material_left));
    scene.add(make_shared<sphere>(Vec3( 1.0,    0.0, -3.0),   0.5, material_right));

    rt_camera rtcamera = rt_camera();

    //----------------Ray-Trace----------------//
    Color *pixels = (Color *)RL_MALLOC(imageWidth*imageHeight*sizeof(Color));
    const auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for 
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            Vec3 pixel_colour(0,0,0);
            for (int s = 0; s < sampels_per_pixels; s++){
                float u = (x + random_float(-1,1));
                float v = (y + random_float(-1,1));
                Ray ray = rtcamera.get_ray(u,v);
                Vec3 colour = ray_colour(&ray, scene, 0);
                colour = Vec3(sqrt(colour.x),sqrt(colour.y),sqrt(colour.z));
                colour = colour * 255;
                pixel_colour += colour;
            }
            pixel_colour = pixel_colour / sampels_per_pixels;
            pixels[y*imageWidth + x] = (Color){ pixel_colour.x, pixel_colour.y, pixel_colour.z, 255 };
        }
        if ((y+1)%100 == 0 || y == imageHeight -1)
            std::cout << "line " << y+1 << " out of " << imageHeight << "\n";
        progress = y;
    }
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration<double>(end-start).count() << "\n";

    Image final_image = {
        .data = pixels,
        .width = imageWidth,
        .height = imageHeight,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    raytracedimagedata = LoadTextureFromImage(final_image);



    //----------------Display----------------//

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(&camera);
    }

    CloseWindow();
    return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(Camera2D* camera)
{
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(WHITE);

        BeginMode2D(*camera);
            //Rectangle rec = {(float)0,(float)0,(float)GetScreenWidth(),(float)GetScreenHeight()};
            //Vector2 pos = {(float)0,(float)0};
            //DrawTextureRec(whitness, rec, pos, WHITE);
            //rec = {(float)0,(float)0,(float)GetScreenWidth()/2,(float)GetScreenHeight()/2};
            //DrawTextureRec(whitness, rec, pos, BLUE);
            //DrawRectangle(0,-100,10,10,BLUE);
            //DrawPixel(-200,-100,BLACK);
            DrawTexture(raytracedimagedata, 0, 0, WHITE);
        EndMode2D();

        DrawFPS(20,20);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

Image GenImageFastNoiseLite(int width, int height, float frequency)
{
    Color *pixels = (Color *)RL_MALLOC(width*height*sizeof(Color));
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(frequency);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float p = noise.GetNoise((float)x,(float)y);
            p = p * -1;

            int intensity = (int)(p*255.0f);
            pixels[y*width + x] = (Color){ intensity, intensity, intensity, 255 };
        }
    }

    Image image = {
        .data = pixels,
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    return image;
}