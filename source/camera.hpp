#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::mat4 view;
    Camera();
    void makeView();
    void moveXn();
    void moveXp();
    void moveYn();
    void moveYp();
    void moveZn();
    void moveZp();
};