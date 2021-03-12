#pragma once

#include <glm/glm.hpp>

class Object
{
private:
public:
    float *allVertices;
    int size_allVertices;
    Object(int, float *);
    void printAll();
    void bindBuffer(unsigned int VAO, unsigned int VBO);
    void bindIndexArray(unsigned int IBO);
    void draw(unsigned int VAO);
    void applyMVP(unsigned int shaderProgram, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};