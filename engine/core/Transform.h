/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Transform class saved all transform data.
/// include rotate, scale, translation.

#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

#include <vector>

namespace qe {
    namespace core {
        class Transform : public Component {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Transform"/> class.
            /// </summary>
            Transform();

            /// <summary>
            /// Finalizes an instance of the <see cref="Transform"/> class.
            /// </summary>
            ~Transform();

            glm::vec3 get_local_rotate();

            glm::vec3 get_world_rotate();
     
            glm::vec3 get_local_scale();

            glm::vec3 get_world_scale();

            glm::vec3 get_local_translation();

            glm::vec3 get_world_translation();

            glm::mat4x4 get_local_matrix();

            glm::mat4x4 get_world_matrix();

            void set_local_rotate(const glm::vec3& local_roate);

            void set_world_rotate(const glm::vec3& world_roate);

            void set_local_scale(const glm::vec3& local_scale);

            void set_world_scale(const glm::vec3& world_scale);

            void set_local_translation(const glm::vec3& local_translation);

            void set_world_translation(const glm::vec3& world_translation);

            void set_local_matrix(const glm::mat4x4& local_matrix);

            void set_world_matrix(const glm::mat4x4& world_matrix);

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

            glm::vec3 local_skew_;

            glm::vec3 world_skew_;

            glm::vec4 local_perspective_;

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