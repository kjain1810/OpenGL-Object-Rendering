#pragma once

#include <glm/glm.hpp>

#include "camera.hpp"

class Object
{
private:
public:
    float *allVertices;                                  // coordinates and colours of all vertices
    int size_allVertices;                                // size of allVertices array
    int vertices;                                        // actual number of vertices
    glm::mat4 model;                                     // model matrix of the object
    Object(int, float *, int);                           // constructor
    void printAll();                                     // for debugging
    void bindBuffer(unsigned int VAO, unsigned int VBO); // binds vertex array and vertex buffer objects
    void draw(unsigned int VAO);                         // draws the vertex array
    void applyMVP(unsigned int, Camera, glm::mat4);      // resets the model view projection matrices
    void moveXn();                                       // move object along negative X
    void moveXp();                                       // move object along positive X
    void moveYn();                                       // move object along negative Y
    void moveYp();                                       // move object along positive Y
    void moveZn();                                       // move object along negative Z
    void moveZp();                                       // move object along positive Z
    void rotate();                                       // rotate object
    void recenter();                                     // recenter object
    void rotateCamera(Camera &);                         // rotate camera
    void predef(int, Camera &);                          // move and camera and object to predefined locations
};