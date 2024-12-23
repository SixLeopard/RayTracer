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
#include "rectangle.hpp"
#include "hitable_list.hpp"
#include "cube.hpp"
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
int sampels_per_pixels = 50;
Texture noiseimagedata; //remove later
Texture raytracedimagedata; //remove later
Texture whitness;

void UpdateDrawFrame(Camera2D* camera);     // Update and Draw one frame
Image GenImageFastNoiseLite(int width, int height, float frequency);
Image RayTracedImage(int width, int height);

Vec3 ray_at(float p, Ray* ray){
    return ray->position + ray->direction * p;
}

Vec3 ray_colour(Ray *ray, const hitable& scene, int depth){
    hit_record rec;

    if (depth >= max_depth)
        return Vec3(0,0,0);

    if (scene.hit(ray, 0.001f, infinity, rec)){
        Ray scattered;
        Vec3 attenuation;
        Vec3 emission;
        if (rec.mat->scatter(ray, rec, attenuation, &scattered)) {
            return attenuation * ray_colour(&scattered, scene, depth+1);
        }
        if (rec.mat->emitted(emission)){
            return emission;
        }
        return Vec3(0,0,0);
    }
    float t = 0.5*(ray->direction.y + 1.0);
    //return ((1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0))/10;
    return Vec3(0,0,0);
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
    auto diffuse_mat = make_shared<diffuse>(Vec3(1.0, 1.0, 1.0));
    auto light   = make_shared<emissive>(Vec3(1, 1, 1), 1000000);
    auto light2   = make_shared<emissive>(Vec3(0.8, 0.1, 1), 1);
    auto light3   = make_shared<emissive>(Vec3(1, 0.1, 0.1), 5);
    auto metal  = make_shared<metallic>(Vec3(0.2, 0.1, 0.8), 0.5f);
    auto metal2  = make_shared<metallic>(Vec3(0.1, 0.1, 0.6), 0.2f);
    auto specular_mat = make_shared<specular>(Vec3(0.2, 0.1, 0.8));

    scene.add(make_shared<sphere>(Vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<sphere>(Vec3( 0.0, 0.0, -3.0),   0.5, diffuse_mat));
    //scene.add(make_shared<sphere>(Vec3(-1.0, 10.0, -3.0),   7, light));
    scene.add(make_shared<sphere>(Vec3( 2.0, 0.0, -2.25),   0.5, light2));
    scene.add(make_shared<sphere>(Vec3( 0.0, 0.75, -4.0),   0.5, light3));
    scene.add(make_shared<sphere>(Vec3( -1.0, 0.0, -3.0),   0.5, light));
    scene.add(make_shared<sphere>(Vec3( 1.0, 0.0, -3.0),   0.5, metal));
    scene.add(make_shared<cube>(Vec3(0.0, 0.0, -4.0),   Vec3(0.75, 0.75, -3.25), metal2));
    scene.add(make_shared<cube>(Vec3(-1.0, 0.0, -4.0),   Vec3(-0.25, 0.75, -3.25), diffuse_mat));
    scene.add(make_shared<sphere>(Vec3( -0.5, 0.0, -2.0),   0.5, metal));
    scene.add(make_shared<sphere>(Vec3( 2.0, 0.0, -3.0),   0.5, specular_mat));
    scene.add(make_shared<sphere>(Vec3( -2.0, 0.0, -3.0),   0.5, diffuse_mat));


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
                Vec3 colour = vec3_clamp(ray_colour(&ray, scene, 0), Vec3(0,0,0), Vec3(1,1,1));
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