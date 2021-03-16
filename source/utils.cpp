#include "utils.hpp"
#include "object.hpp"
#include <stdlib.h>
#include <iostream>
#include <glm/glm.hpp>
#include <random>

float getCol()
{
    return (float)(rand() % 256) / 256.0f;
}

Object createDecagonalPrism()
{
    int nv = 20;
    int sdt = 108;
    // the draw table array
    unsigned int *dt = (unsigned int *)malloc(sdt * sizeof(unsigned int));
    for (int a = 0; a < 8; a++) // triangles to make uppar decagon face
    {
        dt[3 * a] = 0;
        dt[3 * a + 1] = a + 1;
        dt[3 * a + 2] = a + 2;
    }
    for (int a = 0; a < 8; a++) // triangle to make lower decagon face
    {
        dt[24 + 3 * a] = 10;
        dt[24 + 3 * a + 1] = 10 + a + 1;
        dt[24 + 3 * a + 2] = 10 + a + 2;
    }
    for (int a = 0; a < 10; a++) // triangles to make side faces
    {
        dt[48 + a * 6] = a;
        dt[48 + a * 6 + 1] = a + 1;
        dt[48 + a * 6 + 2] = a + 10;
        dt[48 + a * 6 + 3] = a + 1;
        dt[48 + a * 6 + 4] = a + 10;
        dt[48 + a * 6 + 5] = a + 11;
    }
    dt[103] = dt[105] = 0;
    dt[107] = 10;
    float verts[6 * nv];
    for (int a = 0; a < 10; a++) // calculate upper face vertices
    {
        verts[6 * a] = (float)(glm::sin(glm::radians((float)(a * 36))));
        verts[6 * a + 1] = (float)(glm::cos(glm::radians((float)(a * 36))));
        verts[6 * a + 2] = 0.5f;
        for (int b = 3; b < 6; b++)
            verts[6 * a + b] = getCol();
    }
    for (int a = 0; a < 10; a++) // calculate lower face vertices
    {
        verts[60 + 6 * a] = (float)(glm::sin(glm::radians((float)(a * 36))));
        verts[60 + 6 * a + 1] = (float)(glm::cos(glm::radians((float)(a * 36))));
        verts[60 + 6 * a + 2] = -0.5f;
        for (int b = 3; b < 6; b++)
            verts[6 * a + b] = getCol();
    }
    float vertices[6 * sdt];
    for (int a = 0; a < sdt; a++) // copy into a vertex array
    {
        for (int b = 0; b < 3; b++)
            vertices[6 * a + b] = verts[dt[a] * 6 + b];
        for (int b = 3; b < 6; b++)
            vertices[6 * a + b] = getCol();
    }
    // make color of different triangles of same face have the same color
    for (int a = 2; a < 21; a += 3)
        for (int b = 3; b < 6; b++)
            vertices[a * 6 + b] = vertices[(a + 2) * 6 + b];
    for (int a = 0; a < 24; a += 3)
        for (int b = 3; b < 6; b++)
            vertices[a * 6 + b] = vertices[b];
    for (int a = 26; a < 45; a += 3)
        for (int b = 3; b < 6; b++)
            vertices[a * 6 + b] = vertices[(a + 2) * 6 + b];
    for (int a = 24; a < 48; a += 3)
        for (int b = 3; b < 6; b++)
            vertices[a * 6 + b] = vertices[24 * 6 + b];
    for (int a = 49; a < 108; a += 6)
    {
        for (int b = 3; b < 6; b++)
            vertices[a * 6 + b] = vertices[(a + 2) * 6 + b];
        for (int b = 3; b < 6; b++)
            vertices[(a + 1) * 6 + b] = vertices[(a + 3) * 6 + b];
    }
    return Object(6 * sdt, vertices, 20);
}

Object createSqPyramid()
{
    float vertices[] = {
        // vertices
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,    //top thing
        0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,   //bottom thing
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,    // upper top right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,   // upper top left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // upper bottom left,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,   // upper bottom right,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,   // lower top right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // lower top left
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // lower bottom left,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f   // lower bottom right,
    };
    unsigned int dt[] = {         // draw table
                         0, 2, 3, // upper trig 1
                         0, 3, 4, // upper trig 2
                         0, 4, 5, // upper trig 3
                         0, 5, 2, // upper trig 4
                         1, 6, 7, // lower trig 1
                         1, 7, 8, // lower trig 2
                         1, 8, 9, // lower trig 3
                         1, 9, 6, // lower trig 4
                         2, 3, 6, // side face 1
                         3, 6, 7,
                         3, 4, 7, // side face 2
                         4, 7, 8,
                         4, 5, 8, // side face 3
                         5, 8, 9,
                         5, 2, 9, // side face 4
                         2, 9, 6};
    float av[48 * 6];
    // copy into vertex array
    for (int a = 0; a < 48; a++)
    {
        for (int b = 0; b < 3; b++)
            av[6 * a + b] = vertices[6 * dt[a] + b];
        for (int b = 3; b < 6; b++)
            av[6 * a + b] = getCol();
    }
    // make color of different triangles of same face have the same color
    for (int a = 24; a < 48; a += 6)
    {
        for (int b = 3; b < 6; b++)
            av[(a + 1) * 6 + b] = av[(a + 3) * 6 + b];
        for (int b = 3; b < 6; b++)
            av[(a + 2) * 6 + b] = av[(a + 4) * 6 + b];
    }
    return Object(48 * 6, av, 10);
}

Object createHexDiPyramid()
{
    float sq3 = glm::sqrt(3.0f) / 2.0f;
    float vertices[] = {                    // vertices
                        0.0f, 1.0f, 0.0f,   // hexagona vertex 1
                        -sq3, 0.5f, 0.0f,   // hexagona vertex 2
                        -sq3, -0.5f, 0.0f,  // hexagona vertex 3
                        0.0f, -1.0f, 0.0f,  // hexagona vertex 4
                        sq3, -0.5f, 0.0f,   // hexagona vertex 5
                        sq3, 0.5f, 0.0f,    // hexagona vertex 6
                        0.0f, 0.0f, 1.0f,   // upper vertex 1
                        0.0f, 0.0f, -1.0f}; // upper vertex 2
    unsigned int dt[] = {
        6, 0, 1,  // upper face 1
        6, 1, 2,  // upper face 2
        6, 2, 3,  // upper face 3
        6, 3, 4,  // upper face 4
        6, 4, 5,  // upper face 5
        6, 5, 0,  // upper face 6
        7, 0, 1,  // lower face 1
        7, 1, 2,  // lower face 2
        7, 2, 3,  // lower face 3
        7, 3, 4,  // lower face 4
        7, 4, 5,  // lower face 5
        7, 5, 0}; // lower face 6
    float verts[36 * 6];
    // copy into vertex array
    for (int a = 0; a < 36; a++)
    {
        for (int b = 0; b < 3; b++)
            verts[6 * a + b] = vertices[3 * dt[a] + b];
        for (int b = 3; b < 6; b++)
            verts[6 * a + b] = getCol();
    }
    return Object(36 * 6, verts, 8);
}