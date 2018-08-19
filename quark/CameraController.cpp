#include "CameraController.h"
#include "Camera.h"
#include "Transform.h"
#include "QuarkObject.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


qe::core::CameraController::CameraController()
    : clip_{
    1.0, 0.0, 0.0, 0.0,
    0.0, -1.0, 0.0, 0.0,
    0.0, 0.0, 0.5, 0.0,
    0.0, 0.0, 0.5, 1.0 }
    , rotation_speed_(0.05f)
    , movement_speed_(1.0f)
    , lookat_point_(0.0f)
    , Model_(1.0f)
    , camera_(nullptr)
    , transform_(nullptr)
{
    
}

qe::core::CameraController::~CameraController()
{

}

void qe::core::CameraController::RotateCamera(const glm::vec2& pos)
{
    glm::vec3 delta(-pos.y * rotation_speed_, -pos.x * rotation_speed_, 0.0f);

    if (is_lookat_rotate_) {
        lookat_rotate_ += delta;

        transform_->set_world_rotate(lookat_rotate_);
    }
    else {
        world_rotate_ += delta;

        transform_->set_world_rotate(world_rotate_);
    }

    is_lookat_rotate_ = false;
}

void qe::core::CameraController::SmoothZoom(const float & delta_time)
{
    ShrinkMove(delta_time / 100.0f);
}

void qe::core::CameraController::DragCamera(const glm::vec2 & pos)
{
    transform_->set_world_translation(transform_->get_world_translation() - (glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * pos.x));
    transform_->set_world_translation(transform_->get_world_translation() - (glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * pos.y));
}

void qe::core::CameraController::Zoom(const float & delta_time)
{
    ShrinkMove(delta_time / 2.0f);
}

void qe::core::CameraController::LookAtRotate(const glm::vec2 & pos)
{
    RotateCamera(pos);
    is_lookat_rotate_ = true;
}

void qe::core::CameraController::ShrinkMove(const float & delta_time)
{
    transform_->set_world_translation(transform_->get_world_translation() + (view_direction_ * movement_speed_ * delta_time));
}

void qe::core::CameraController::HorizontalMove(const float & delta_time)
{
    transform_->set_world_translation(transform_->get_world_translation() + (glm::normalize(glm::cross(view_direction_, glm::vec3(0.0, 1.0, 0.0))) * movement_speed_ * delta_time));
}

void qe::core::CameraController::VerticalMove(const float & delta_time)
{
    transform_->set_world_translation(transform_->get_world_translation() + (glm::vec3(0.0, 1.0, 0.0) * movement_speed_ * delta_time));
}

void qe::core::CameraController::LookAtObject()
{

}

void qe::core::CameraController::Awake()
{
   camera_ = get_quark_object()->GetComponent<qe::core::Camera>();
   transform_ = get_quark_object()->GetComponent<qe::core::Transform>();
}

void qe::core::CameraController::Update()
{
    UpdateDirection();
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void qe::core::CameraController::UpdateModelMatrix()
{

}

void qe::core::CameraController::UpdateViewMatrix()
{

    auto lookat_rotate = glm::mat4(1.0f);
    auto world_rotate = glm::mat4(1.0f);

    glm::mat4 transM;

    lookat_rotate = glm::rotate(lookat_rotate, glm::radians(lookat_rotate_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    lookat_rotate = glm::rotate(lookat_rotate, glm::radians(lookat_rotate_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    lookat_rotate = glm::rotate(lookat_rotate, glm::radians(lookat_rotate_.z), glm::vec3(0.0f, 0.0f, 1.0f));


    world_rotate = glm::rotate(world_rotate, glm::radians(world_rotate_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    world_rotate = glm::rotate(world_rotate, glm::radians(world_rotate_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    world_rotate = glm::rotate(world_rotate, glm::radians(world_rotate_.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // adjust camera coordination
    transM = glm::translate(glm::mat4(1.0f), -transform_->get_world_translation());

    if (is_lookat_rotate_) {
        auto camera_point_mat = glm::translate(glm::mat4(1.0f), lookat_point_);

        View_ = world_rotate * transM * lookat_rotate * camera_point_mat;
    }
    else {
        View_ = world_rotate * transM * lookat_rotate;
    }

}

void qe::core::CameraController::UpdateProjectionMatrix()
{
    Projection_ = glm::mat4(1.0);
    Projection_ = clip_ * glm::perspective(
        camera_->get_field_of_view(), 
        camera_->get_aspect(),
        camera_->get_near_clip_plane(),
        camera_->get_far_clip_plane());
}

void qe::core::CameraController::UpdateDirection()
{
    view_direction_.x = -cos(glm::radians(world_rotate_.x)) * sin(glm::radians(world_rotate_.y));
    view_direction_.y = sin(glm::radians(world_rotate_.x));
    view_direction_.z = cos(glm::radians(world_rotate_.x)) * cos(glm::radians(world_rotate_.y));
    view_direction_ = glm::normalize(view_direction_);
}




