#include <stdlib.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>

#include "object.hpp"

Object::Object(int nv, float v[], unsigned int *dt, int sdt)
{
    size_drawTable = sdt;
    num_vertices = nv;
    vertices = (float *)std::malloc(6 * nv * sizeof(float));
    for (int a = 0; a < 6 * num_vertices; a++)
        vertices[a] = v[a];
    drawTable = (unsigned int *)malloc(sdt * sizeof(unsigned int));
    for (int a = 0; a < sdt; a++)
        drawTable[a] = dt[a];
    allVertices = (float *)std::malloc(6 * sdt * sizeof(float));
    for (int a = 0; a < sdt; a++)
    {
        for (int b = 0; b < 3; b++)
            allVertices[6 * a + b] = vertices[drawTable[a] * 6 + b];
        for (int b = 3; b < 6; b++)
            allVertices[6 * a + b] = (float)(rand() % 256) / 256.0;
    }
}

Object::Object(int sv, float *av)
{
    size_allVertices = sv;
    allVertices = (float *)std::malloc(sv * sizeof(float));
    for (int a = 0; a < sv; a++)
        allVertices[a] = av[a];
}

void Object::bindBuffer(unsigned int VAO, unsigned int VBO)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_allVertices * 6 * sizeof(float), allVertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Object::bindIndexArray(unsigned int IBO)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_drawTable * sizeof(unsigned int), drawTable, GL_STATIC_DRAW);
}

void Object::draw(unsigned int VAO)
{
    glBindVertexArray(VAO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawArrays(GL_TRIANGLES, 0, size_allVertices / 6);
}

void Object::applyMVP(unsigned int shaderProgram, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
}

void Object::printAll()
{
    for (int a = 0; a < num_vertices; a++)
    {
        std::cout << vertices[6 * a] << " " << vertices[6 * a + 1] << " " << vertices[6 * a + 2] << " ";
        std::cout << vertices[6 * a + 3] << " " << vertices[6 * a + 4] << " " << vertices[6 * a + 5] << "\n";
    }
    for (int a = 0; a < size_drawTable / 3; a++)
        std::cout << drawTable[3 * a] << " " << drawTable[3 * a + 1] << " " << drawTable[3 * a + 2] << "\n";
}