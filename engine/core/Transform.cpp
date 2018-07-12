#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>


qe::core::Transform::Transform()
{
    local_rotate_ = glm::vec3(0.0, 0.0, 0.0);

    world_rotate_ = glm::vec3(0.0, 0.0, 0.0);

    local_scale_ = glm::vec3(1.0, 1.0, 1.0);

    world_scale_ = glm::vec3(1.0, 1.0, 1.0);

    local_translation_ = glm::vec3(0.0, 0.0, 0.0);

    world_translation_ = glm::vec3(0.0, 0.0, 0.0);
}

qe::core::Transform::~Transform()
{
}

glm::vec3 qe::core::Transform::get_local_rotate()
{
    return local_rotate_;
}

glm::vec3 qe::core::Transform::get_world_rotate()
{
    return world_rotate_;
}

glm::vec3 qe::core::Transform::get_local_scale()
{
    return local_scale_;
}

glm::vec3 qe::core::Transform::get_world_scale()
{
    return world_scale_;
}

glm::vec3 qe::core::Transform::get_local_translation()
{
    return local_translation_;
}

glm::vec3 qe::core::Transform::get_world_translation()
{
    return world_translation_;
}

glm::mat4x4 qe::core::Transform::get_local_matrix()
{
    return local_matrix_;
}

glm::mat4x4 qe::core::Transform::get_world_matrix()
{
    return world_matrix_;
}

void qe::core::Transform::set_local_rotate(const glm::vec3 & local_roate)
{
    local_rotate_ = local_roate;
    local_matrix_ *= glm::orientate4(local_rotate_);
}

void qe::core::Transform::set_world_rotate(const glm::vec3 & world_roate)
{
    world_rotate_ = world_roate;
    world_matrix_ *= glm::orientate4(world_rotate_);
}

void qe::core::Transform::set_local_scale(const glm::vec3 & local_scale)
{
    local_scale_ = local_scale;
    local_matrix_ *= glm::scale(glm::mat4(1.0f), local_scale_);
}

void qe::core::Transform::set_world_scale(const glm::vec3 & world_scale)
{
    world_scale_ = world_scale;
    world_matrix_ *= glm::scale(glm::mat4(1.0f), world_scale_);
}

void qe::core::Transform::set_local_translation(const glm::vec3 & local_translation)
{
    local_translation_ = local_translation;
    local_matrix_ *= glm::translate(glm::mat4(1.0f), local_translation_);
}

void qe::core::Transform::set_world_translation(const glm::vec3 & world_translation)
{
    world_translation_ = world_translation;
    world_matrix_ *= glm::translate(glm::mat4(1.0f), world_translation_);
}

void qe::core::Transform::set_world_matrix(const glm::mat4x4& world_matrix)
{
    world_matrix_ = world_matrix;

    glm::quat rot;
    glm::decompose(world_matrix_, world_scale_, rot, world_translation_, world_skew_, world_perspective_);

    world_rotate_ = glm::eulerAngles(rot);
}

void qe::core::Transform::set_local_matrix(const glm::mat4x4& local_matrix)
{
    local_matrix_ = local_matrix;

    glm::quat rot;
    glm::decompose(local_matrix_, local_scale_, rot, local_translation_, local_skew_, local_perspective_);

    local_rotate_ = glm::eulerAngles(rot);
}


