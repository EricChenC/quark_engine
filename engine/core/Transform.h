/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Transform class saved all transform data.
/// include rotate, scale, translation.

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>

namespace qe {
    namespace core {
        class DLL_EXPORT Transform : public Component {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Transform"/> class.
            /// </summary>
            Transform();

            /// <summary>
            /// Finalizes an instance of the <see cref="Transform"/> class.
            /// </summary>
            ~Transform();

        // properties
        public:

            /// <summary>
            /// Gets the local rotate.
            /// </summary>
            /// <returns></returns>
            inline auto get_local_rotate()const -> const glm::vec3& { return local_rotate_; }

            /// <summary>
            /// Sets the local rotate.
            /// </summary>
            /// <param name="local_roate">The local roate.</param>
            inline void set_local_rotate(const glm::vec3& local_roate) {
                local_rotate_ = local_roate;
                local_matrix_ *= glm::orientate4(local_rotate_);
            }

            /// <summary>
            /// Gets the world rotate.
            /// </summary>
            /// <returns></returns>
            inline auto get_world_rotate()const -> const glm::vec3& { return world_rotate_; }

            /// <summary>
            /// Sets the world rotate.
            /// </summary>
            /// <param name="world_roate">The world roate.</param>
            inline void set_world_rotate(const glm::vec3& world_roate) {
                world_rotate_ = world_roate;
                world_matrix_ *= glm::orientate4(world_rotate_);
            }

            /// <summary>
            /// Gets the local scale.
            /// </summary>
            /// <returns></returns>
            inline auto get_local_scale()const -> const glm::vec3& { return local_scale_; }

            /// <summary>
            /// Sets the local scale.
            /// </summary>
            /// <param name="local_scale">The local scale.</param>
            inline void set_local_scale(const glm::vec3& local_scale) {
                local_scale_ = local_scale;
                local_matrix_ *= glm::scale(glm::mat4(1.0f), local_scale_);
            }

            /// <summary>
            /// Gets the world scale.
            /// </summary>
            /// <returns></returns>
            inline auto get_world_scale()const -> const glm::vec3& { return world_scale_; }

            /// <summary>
            /// Sets the world scale.
            /// </summary>
            /// <param name="world_scale">The world scale.</param>
            inline void set_world_scale(const glm::vec3& world_scale) {
                world_scale_ = world_scale;
                world_matrix_ *= glm::scale(glm::mat4(1.0f), world_scale_);
            }

            /// <summary>
            /// Gets the local translation.
            /// </summary>
            /// <returns></returns>
            inline auto get_local_translation()const -> const glm::vec3& { return local_translation_; }

            /// <summary>
            /// Sets the local translation.
            /// </summary>
            /// <param name="local_translation">The local translation.</param>
            inline void set_local_translation(const glm::vec3& local_translation) {
                local_translation_ = local_translation;
                local_matrix_ *= glm::translate(glm::mat4(1.0f), local_translation_);
            }

            /// <summary>
            /// Gets the world translation.
            /// </summary>
            /// <returns></returns>
            inline auto get_world_translation()const -> const glm::vec3& { return world_translation_; }

            /// <summary>
            /// Sets the world translation.
            /// </summary>
            /// <param name="world_translation">The world translation.</param>
            inline void set_world_translation(const glm::vec3& world_translation) {
                world_translation_ = world_translation;
                world_matrix_ *= glm::translate(glm::mat4(1.0f), world_translation_);
            }

            /// <summary>
            /// Gets the local matrix.
            /// </summary>
            /// <returns></returns>
            inline auto get_local_matrix()const -> const glm::mat4x4& { return local_matrix_; }

            /// <summary>
            /// Sets the local matrix.
            /// </summary>
            /// <param name="local_matrix">The local matrix.</param>
            inline void set_local_matrix(const glm::mat4x4& local_matrix) {

                local_matrix_ = local_matrix;

                glm::quat rot;
                glm::decompose(local_matrix_, local_scale_, rot, local_translation_, local_skew_, local_perspective_);

                local_rotate_ = glm::eulerAngles(rot);
            }

            /// <summary>
            /// Gets the world matrix.
            /// </summary>
            /// <returns></returns>
            inline auto get_world_matrix()const -> const glm::mat4x4& { return world_matrix_; }

            /// <summary>
            /// Sets the world matrix.
            /// </summary>
            /// <param name="world_matrix">The world matrix.</param>
            inline void set_world_matrix(const glm::mat4x4& world_matrix) {
                world_matrix_ = world_matrix;

                glm::quat rot;
                glm::decompose(world_matrix_, world_scale_, rot, world_translation_, world_skew_, world_perspective_);

                world_rotate_ = glm::eulerAngles(rot);
            }

        private:
            /// <summary>
            /// The local rotate
            /// </summary>
            glm::vec3 local_rotate_;
            
            /// <summary>
            /// The world rotate
            /// </summary>
            glm::vec3 world_rotate_;

            /// <summary>
            /// The local scale
            /// </summary>
            glm::vec3 local_scale_;

            /// <summary>
            /// The world scale
            /// </summary>
            glm::vec3 world_scale_;

            /// <summary>
            /// The local translation
            /// </summary>
            glm::vec3 local_translation_;

            /// <summary>
            /// The world translation
            /// </summary>
            glm::vec3 world_translation_;

            /// <summary>
            /// The local skew
            /// </summary>
            glm::vec3 local_skew_;

            /// <summary>
            /// The world skew
            /// </summary>
            glm::vec3 world_skew_;

            /// <summary>
            /// The local perspective
            /// </summary>
            glm::vec4 local_perspective_;

            /// <summary>
            /// The world perspective
            /// </summary>
            glm::vec4 world_perspective_;

            /// <summary>
            /// The local matrix
            /// </summary>
            glm::mat4x4 local_matrix_;

            /// <summary>
            /// The world matrix
            /// </summary>
            glm::mat4x4 world_matrix_;


        };
    }
}