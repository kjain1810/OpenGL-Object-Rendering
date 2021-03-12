#pragma once

#include <glm/glm.hpp>

class Object
{
private:
public:
    float *allVertices;
    int size_allVertices;
    glm::mat4 model;
    Object(int, float *);
    void printAll();
    void bindBuffer(unsigned int VAO, unsigned int VBO);
    void bindIndexArray(unsigned int IBO);
    void draw(unsigned int VAO);
    void applyMVP(unsigned int shaderProgram, glm::mat4, glm::mat4);
    void moveXn();
    void moveXp();
    void moveYn();
    void moveYp();
    void moveZn();
    void moveZp();
    void rotate();
};