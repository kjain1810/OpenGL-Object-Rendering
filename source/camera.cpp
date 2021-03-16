#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"
#include "object.hpp"

Camera::Camera()
{
    cameraPos = glm::vec3(1.0f, 1.0f, -4.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(cameraPos, cameraFront, cameraUp);
}

void Camera::makeView()
{
    view = glm::lookAt(cameraPos, cameraFront, cameraUp);
}

void Camera::moveXn()
{
    glm::vec3 toadd = glm::vec3(-0.01f, 0.0f, 0.0f);
    cameraPos += toadd;
    cameraFront += toadd;
    makeView();
}

void Camera::moveXp()
{
    glm::vec3 toadd = glm::vec3(0.01f, 0.0f, 0.0f);
    cameraPos += toadd;
    cameraFront += toadd;
    makeView();
}
void Camera::moveYn()
{
    cameraPos += 0.01f * cameraFront;
    makeView();
}

void Camera::moveYp()
{
    cameraPos += -0.01f * cameraFront;
    makeView();
}
void Camera::moveZn()
{
    glm::vec3 toadd = glm::vec3(0.0f, -0.01f, 0.0f);
    cameraPos += toadd;
    cameraFront += toadd;
    makeView();
}

void Camera::moveZp()
{
    glm::vec3 toadd = glm::vec3(0.0f, 0.01f, 0.0f);
    cameraPos += toadd;
    cameraFront += toadd;
    makeView();
}
