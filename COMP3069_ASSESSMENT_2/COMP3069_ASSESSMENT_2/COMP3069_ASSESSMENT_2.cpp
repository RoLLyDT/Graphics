//Maksim KOZLOV 20219332
#define _USE_MATH_DEFINES 
#include <iostream>
#include <SDL.h>
#include <Windows.h>
#undef main

#include "DoNotModify.h"

int n_tris;


float vertices[] =
{
    // pos 1
    -.75f,  .5f,    0.f,  
    .75f,   .5f,    0.f,         
    .0f,    .0f,    0.f,         

    // pos 2					
    .5f,    -.5f,   0.f,        
    -.25f,  -.25f,  0.f,   
    .0f,    .0f,    0.f,       

    // pos 3
    -.5f,   -.5f,   0.f,
    .5f,    -.5f,   0.f,
    0.f,    -1.f,   0.f
};


void ClearColourBuffer(int r, int g, int b)
{
    for (int i = 0; i < PIXEL_W; ++i)
    {
        for (int j = 0; j < PIXEL_H; ++j)
        {
            colour_buffer[i][j].x = static_cast<float>(r);
            colour_buffer[i][j].y = static_cast<float>(g);
            colour_buffer[i][j].z = static_cast<float>(b);
        }
    }
}

triangle* AssembleTriangles(float* verts, int n_verts, int* n_tris)
{
    /* Check for correct amount of vertices
    if (n_verts < 3 || n_verts % 3 != 0)
    {
        *n_tris = 0;
        return nullptr;
    }
    */
    *n_tris = n_verts / 3;

    //memory allocation
    triangle* triangles = new triangle[*n_tris];

    for (int i = 0; i < *n_tris; i++)
    {
        triangles[i].v1.pos.x = verts[i * 9];
        triangles[i].v1.pos.y = verts[i * 9 + 1];
        triangles[i].v1.pos.z = verts[i * 9 + 2];

        triangles[i].v2.pos.x = verts[i * 9 + 3];
        triangles[i].v2.pos.y = verts[i * 9 + 4];
        triangles[i].v2.pos.z = verts[i * 9 + 5];

        triangles[i].v3.pos.x = verts[i * 9 + 6];
        triangles[i].v3.pos.y = verts[i * 9 + 7];
        triangles[i].v3.pos.z = verts[i * 9 + 8];
    }

    return triangles;
}

void TransformToViewport(int width, int height, triangle* tri)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    for (int i = 0; i < n_tris; i++) 
    {
        tri[i].v1.pos.x = (tri[i].v1.pos.x + 1) * halfWidth;
        tri[i].v1.pos.y = (tri[i].v1.pos.y + 1) * halfHeight;

        tri[i].v2.pos.x = (tri[i].v2.pos.x + 1) * halfWidth;
        tri[i].v2.pos.y = (tri[i].v2.pos.y + 1) * halfHeight;

        tri[i].v3.pos.x = (tri[i].v3.pos.x + 1) * halfWidth;
        tri[i].v3.pos.y = (tri[i].v3.pos.y + 1) * halfHeight;
    }
}

void ComputeBarycentricCoordinates(float x, float y, triangle t, float& alpha, float& beta, float& gamma)
{
    float x1 = t.v1.pos.x, y1 = t.v1.pos.y;
    float x2 = t.v2.pos.x, y2 = t.v2.pos.y;
    float x3 = t.v3.pos.x, y3 = t.v3.pos.y;

    float BCP = (y3 - y2) * x + (x2 - x3) * y + x3 * y2 - x2 * y3;
    float BCA = (y3 - y2) * x1 + (x2 - x3) * y1 + x3 * y2 - x2 * y3;

    float ACP = (y3 - y1) * x + (x1 - x3) * y + x3 * y1 - x1 * y3;
    float ACB = (y3 - y1) * x2 + (x1 - x3) * y2 + x3 * y1 - x1 * y3;

    float ABP = (y2 - y1) * x + (x1 - x2) * y + x2 * y1 - x1 * y2;
    float ABC = (y2 - y1) * x3 + (x1 - x2) * y3 + x2 * y1 - x1 * y2;

    alpha = BCP / BCA;
    beta = ACP / ACB;
    gamma = ABP / ABC;
}

void ShadeFragment(float alpha, float beta, float gamma, triangle t, int& r, int& g, int& b)
{
    r = 64; g = 224; b = 208;
}



int main()
{
    float alpha, beta, gamma;

    COMP3069StartSDL();

    ClearColourBuffer(128, 0, 255);

    triangle* tris = AssembleTriangles(vertices, sizeof(vertices) / (sizeof(float) * 3), &n_tris);

    TransformToViewport(PIXEL_W, PIXEL_H, tris);

    for (int x = 0; x < PIXEL_W; x++) 
    {
        for (int y = 0; y < PIXEL_H; y++) 
        {
            for (int t = 0; t < n_tris; t++) 
            {
                ComputeBarycentricCoordinates((float)x, (float)y, tris[t], alpha, beta, gamma);
                if (alpha > 0 && beta > 0 && gamma > 0) 
                {
                    int r, g, b;
                    ShadeFragment(alpha, beta, gamma, tris[t], r, g, b);
                    colour_buffer[x][PIXEL_H - y - 1].x = static_cast<float>(r);
                    colour_buffer[x][PIXEL_H - y - 1].y = static_cast<float>(g);
                    colour_buffer[x][PIXEL_H - y - 1].z = static_cast<float>(b);
                }
            }
        }
    }


    while (1)
    {
        if (COMP3069PressedEscape())
            break;

        COMP3069DisplayColourBuffer();
    }

    COMP3069StopSDL();

    delete[] tris;

    return EXIT_SUCCESS;
}

