#include <stdlib.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <random>

#include "object.hpp"
#include "camera.hpp"

Object::Object(int sv, float *av, int verts)
{
    size_allVertices = sv;
    allVertices = (float *)std::malloc(sv * sizeof(float));
    for (int a = 0; a < sv; a++)
        allVertices[a] = av[a];
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    vertices = verts;
}

void Object::bindBuffer(unsigned int VAO, unsigned int VBO)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size_allVertices * 6 * sizeof(float), allVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Object::draw(unsigned int VAO)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, size_allVertices / 6);
}

void Object::applyMVP(unsigned int shaderProgram, Camera cam, glm::mat4 projection)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &cam.view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
}

void Object::moveXn()
{
    model = glm::translate(model, glm::vec3(-0.01f, 0.0f, 0.0f));
}

void Object::moveXp()
{
    model = glm::translate(model, glm::vec3(0.01f, 0.0f, 0.0f));
}
void Object::moveYn()
{
    model = glm::translate(model, glm::vec3(0.0f, -0.01f, 0.0f));
}

void Object::moveYp()
{
    model = glm::translate(model, glm::vec3(0.0f, 0.01f, 0.0f));
}
void Object::moveZn()
{
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.01f));
}

void Object::moveZp()
{
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.01f));
}

void Object::rotate()
{
    model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Object::recenter()
{
    model = glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Object::rotateCamera(Camera &cam)
{
    recenter();
    glm::mat4 here = glm::rotate(glm::mat4(1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.1f));
    glm::vec4 lmao = here * glm::vec4(cam.cameraPos, 0.0f);
    cam.cameraPos.x = lmao.x;
    cam.cameraPos.y = lmao.y;
    cam.makeView();
}

void Object::predef(int i, Camera &cam)
{
    if (i <= 0 || i >= 4)
        return;
    if (i == 1)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.3f, 0.3f, 0.3f));
        cam.cameraPos = glm::vec3(0.0f, 1.0f, -6.0f);
        cam.cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
        cam.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.makeView();
    }
    else if (i == 2)
    {
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 1.0f));
        cam.cameraPos = glm::vec3(1.0f, 1.0f, -4.0f);
        cam.cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
        cam.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.makeView();
    }
    else if (i == 3)
    {
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        cam.cameraPos = glm::vec3(1.0f, 1.0f, -4.0f);
        cam.cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
        cam.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
        cam.makeView();
    }
}