#include "CameraController.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


qe::edit::CameraController::CameraController()
    : clip{
    1.0, 0.0, 0.0, 0.0,
    0.0, -1.0, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.0, 0.0, 0.5, 1.0 }
    , rotation_speed_(0.05f)
    , movement_speed_(1.0f)
    , view_position_(0.0f, 0.0f, 0.0f)
    , projection_fov_(45.0f)
    , projection_ratio_(4.0f / 3.0f)
    , projection_near_(0.1f)
    , projection_far_(1000.0f)
    , Model_(1.0f)
    , type_(CameraType::FIRSTPERSON)
{
    
}

qe::edit::CameraController::~CameraController()
{
}

void qe::edit::CameraController::RotateCamera(const glm::vec2& pos)
{
    glm::vec3 delta(-pos.y * rotation_speed_, -pos.x * rotation_speed_, 0.0f);

    rotation_ += delta;
}

void qe::edit::CameraController::MoveCamera(const glm::vec2 & pos)
{

}

void qe::edit::CameraController::MoveForward(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ += view_direction_ * movement_speed_ * delta_time;
    }
    else {
        view_position_ += view_direction_ * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::MoveBack(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ -= view_direction_ * movement_speed_ * delta_time;
    }
    else {
        view_position_ -= view_direction_ * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::MoveLeft(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ -= glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * delta_time;
    }
    else {
        view_position_ -= glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::MoveRight(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ += glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * delta_time;
    }
    else {
        view_position_ += glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::MoveUp(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ -= glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * delta_time;
    }
    else {
        view_position_ += glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::MoveDown(const float& delta_time)
{
    UpdateDirection();

    if (type_ == CameraType::FIRSTPERSON)
    {
        view_position_ += glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * delta_time;
    }
    else {
        view_position_ -= glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * delta_time;
    }
}

void qe::edit::CameraController::UpdateProjectionRatio(const float & ratio)
{
    projection_ratio_ = ratio;
}

void qe::edit::CameraController::Update()
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void qe::edit::CameraController::UpdateModelMatrix()
{

}

void qe::edit::CameraController::UpdateViewMatrix()
{

    glm::mat4 rotM = glm::mat4(1.0f);
    glm::mat4 transM;

    rotM = glm::rotate(rotM, glm::radians(rotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotM = glm::rotate(rotM, glm::radians(rotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotM = glm::rotate(rotM, glm::radians(rotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));

    transM = glm::translate(glm::mat4(1.0f), view_position_);

    if (type_ == CameraType::FIRSTPERSON)
    {
        View_ = rotM * transM;
    }
    else
    {
        View_ = transM * rotM;
    }

}

void qe::edit::CameraController::UpdateProjectionMatrix()
{
    Projection_ = glm::mat4(1.0);
    Projection_ = clip * glm::perspective(projection_fov_, projection_ratio_, projection_near_, projection_far_);
}

void qe::edit::CameraController::UpdateDirection()
{
    view_direction_.x = -cos(glm::radians(rotation_.x)) * sin(glm::radians(rotation_.y));
    view_direction_.y = sin(glm::radians(rotation_.x));
    view_direction_.z = cos(glm::radians(rotation_.x)) * cos(glm::radians(rotation_.y));
    view_direction_ = glm::normalize(view_direction_);
}




