#pragma once

#include <glm/glm.hpp>

#include "camera.hpp"

class Object
{
private:
public:
    float *allVertices;
    int size_allVertices;
    int vertices;
    glm::mat4 model;
    Object(int, float *, int);
    void printAll();
    void bindBuffer(unsigned int VAO, unsigned int VBO);
    void bindIndexArray(unsigned int IBO);
    void draw(unsigned int VAO);
    void applyMVP(unsigned int shaderProgram, Camera, glm::mat4);
    void moveXn();
    void moveXp();
    void moveYn();
    void moveYp();
    void moveZn();
    void moveZp();
    void rotate();
};