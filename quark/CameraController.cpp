#include "CameraController.h"

#include <glm/gtc/matrix_transform.hpp>

qe::edit::CameraController::CameraController()
{
    mouse_speed_ = 0.005f;
    horizontal_angle_ = 0.0f;
    vertical_angle_ = 0.0f;
    move_pace_ = 0.5f;

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

    // init camera rotate position 
    RotateCamera(glm::vec2(0, 1));

}

qe::edit::CameraController::~CameraController()
{
}

void qe::edit::CameraController::RotateCamera(const glm::vec2& pos)
{
    horizontal_angle_ += mouse_speed_ * pos.x;
    vertical_angle_ += mouse_speed_ * pos.y;

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
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveForward()
{
    glm::vec3 direc = view_center_ - view_position_;

    view_position_ += direc * move_pace_;
    view_center_ += direc * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveBack()
{
    glm::vec3 direc = view_center_ - view_position_;

    view_position_ -= direc * move_pace_;
    view_center_ -= direc * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveLeft()
{
    glm::vec3 direc = view_center_ - view_position_;
    glm::vec3 right = glm::cross(direc, view_up_);

    view_position_ -= right * move_pace_;
    view_center_ -= right * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveRight()
{
    glm::vec3 direc = view_center_ - view_position_;
    glm::vec3 right = glm::cross(direc, view_up_);

    view_position_ += right * move_pace_;
    view_center_ += right * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveUp()
{
    view_position_ += glm::normalize(view_up_) * move_pace_;
    view_center_ += glm::normalize(view_up_) * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::MoveDown()
{
    view_position_ -= view_up_ * move_pace_;
    view_center_ -= view_up_ * move_pace_;
    UpdateViewMatrix();
}

void qe::edit::CameraController::UpdateProjectionRatio(const float & ratio)
{
    projection_ratio_ = ratio;
    UpdateProjectionMatrix();
}

const glm::mat4& qe::edit::CameraController::get_m() const
{
    return Model_;
}

const glm::mat4& qe::edit::CameraController::get_v() const
{
    return View_;
}

const glm::mat4& qe::edit::CameraController::get_p() const
{
    return Projection_;
}

const glm::mat4& qe::edit::CameraController::get_mv() const
{
    return View_ * Model_;
}

const glm::mat4 & qe::edit::CameraController::get_vp() const
{
    return Projection_ * View_;
}

const glm::mat4& qe::edit::CameraController::get_mvp() const
{
    return Projection_ * View_ * Model_;
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


