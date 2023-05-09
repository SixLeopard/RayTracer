#include "FastNoiseLite.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <iostream>

int screenWidth = GetScreenWidth();
int screenHeight = GetScreenHeight();
int imageWidth = 1920;
int imageHeight = 1080;
Texture noiseimagedata; //remove later
Texture raytracedimagedata; //remove later
Texture whitness;

void UpdateDrawFrame(Camera2D* camera);     // Update and Draw one frame
Image GenImageFastNoiseLite(int width, int height, float frequency);
Image RayTracedImage(int width, int height);

Vector3 get_ray_colour(Ray *ray){
    //std::cout << ray->direction.y;
    float r = ((ray->direction.x + 1) / 2) * 255;
    float g = ((ray->direction.y + 1) / 2) * 255;
    float b = ((ray->direction.z + 1) / 2) * 255;
    return (Vector3){r,g,b};
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

    //----------------Ray-Trace----------------//
    Color *pixels = (Color *)RL_MALLOC(imageWidth*imageHeight*sizeof(Color));
    for (int y = 0; y < imageHeight; y++)
    {
        for (int x = 0; x < imageWidth; x++)
        {
            Ray ray = {(Vector3){x,y}, (Vector3){(((float)x)-(imageWidth/2))/imageWidth,((float)y-(imageHeight/2))/imageHeight,0}};
            Vector3 colour = get_ray_colour(&ray);
            pixels[y*imageWidth + x] = (Color){ colour.x, colour.y, colour.z, 255 };
        }
    }

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