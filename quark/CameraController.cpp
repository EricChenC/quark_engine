#include "CameraController.h"

#include <glm/gtc/matrix_transform.hpp>


qe::edit::CameraController::CameraController()
{
    rotation_speed_ = 0.005f;
    movement_speed_ = 2000.0f;

    horizontal_angle_ = 0.0f;
    vertical_angle_ = 0.0f;

    view_position_ = glm::vec3(0.0f, 1.0f, -6.0f);
    view_center_ = glm::vec3(0.0f, 0.0f, 0.0f);
    view_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

    projection_angle_ = 45.0f;
    projection_ratio_ = 4.0f / 3.0f;
    projection_near_ = 0.1f;
    projection_far_ = 1000.0f;

    Model_ = glm::mat4(1.0);
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

qe::edit::CameraController::~CameraController()
{
}

void qe::edit::CameraController::RotateCamera(const glm::vec2& pos)
{
    horizontal_angle_ += rotation_speed_ * pos.x;
    vertical_angle_ += rotation_speed_ * pos.y;

    view_direction_ = glm::vec3(
        cos(vertical_angle_) * sin(horizontal_angle_),
        sin(vertical_angle_),
        cos(vertical_angle_) * cos(horizontal_angle_)
    );

    view_right_ = glm::vec3(
        sin(horizontal_angle_ - 3.14f / 2.0f),
        0,
        cos(horizontal_angle_ - 3.14f / 2.0f)
    );

    view_center_ = view_position_ + view_direction_;
    view_up_ = glm::cross(view_right_, view_direction_);
}

void qe::edit::CameraController::MoveForward(const float& delta_time)
{
    glm::vec3 direc = view_center_ - view_position_;

    view_position_ += direc * movement_speed_ * delta_time;
    view_center_ += direc * movement_speed_ * delta_time;
}

void qe::edit::CameraController::MoveBack(const float& delta_time)
{
    glm::vec3 direc = view_center_ - view_position_;

    view_position_ -= direc * movement_speed_ * delta_time;
    view_center_ -= direc * movement_speed_ * delta_time;
}

void qe::edit::CameraController::MoveLeft(const float& delta_time)
{
    glm::vec3 direc = view_center_ - view_position_;
    glm::vec3 right = glm::cross(direc, view_up_);

    view_position_ -= right * movement_speed_ * delta_time;
    view_center_ -= right * movement_speed_ * delta_time;
}

void qe::edit::CameraController::MoveRight(const float& delta_time)
{
    glm::vec3 direc = view_center_ - view_position_;
    glm::vec3 right = glm::cross(direc, view_up_);

    view_position_ += right * movement_speed_ * delta_time;
    view_center_ += right * movement_speed_ * delta_time;
}

void qe::edit::CameraController::MoveUp(const float& delta_time)
{
    view_position_ += glm::normalize(view_up_) * movement_speed_ * delta_time;
    view_center_ += glm::normalize(view_up_) * movement_speed_ * delta_time;
}

void qe::edit::CameraController::MoveDown(const float& delta_time)
{
    view_position_ -= view_up_ * movement_speed_* delta_time;
    view_center_ -= view_up_ * movement_speed_ * delta_time;
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
    View_ = glm::mat4(1.0);
    View_ = glm::lookAt(view_position_, view_center_, view_up_);
}

void qe::edit::CameraController::UpdateProjectionMatrix()
{
    Projection_ = glm::mat4(1.0);
    Projection_ = clip * glm::perspective(projection_angle_, projection_ratio_, projection_near_, projection_far_);
}




