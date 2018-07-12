#include "Camera.h"

qe::core::Camera::Camera()
{
}

qe::core::Camera::~Camera()
{
}

glm::vec3 qe::core::Camera::get_look_at()
{
    return glm::vec3();
}

int qe::core::Camera::get_near()
{
    return 0;
}

int qe::core::Camera::get_far()
{
    return 0;
}
