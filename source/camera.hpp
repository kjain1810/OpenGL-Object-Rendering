#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    glm::vec3 cameraPos;   // position location vector of camera
    glm::vec3 cameraFront; // front location vector of camera
    glm::vec3 cameraUp;    // up direction vector of camera
    glm::mat4 view;        // view matrix
    Camera();              // constructor
    void makeView();       //sets view matrix of camera
    void moveXn();         // move camera along negative X
    void moveXp();         // move camera along positive X
    void moveYn();         // move camera along negative Y
    void moveYp();         // move camera along positive Y
    void moveZn();         // move camera along negative Z
    void moveZp();         // move camera along positive Z
};