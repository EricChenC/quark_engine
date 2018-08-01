/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include <glm/matrix.hpp>

#include "EditObject.h"

namespace qe {
    namespace edit {
        class CameraController : public EditObject
        {
        public:
            explicit CameraController();
            ~CameraController();

            void RotateCamera(const glm::vec2& pos);
            void MoveForward(const float& elapsed = 1.0);
            void MoveBack(const float& elapsed = 1.0);
            void MoveLeft(const float& elapsed = 1.0);
            void MoveRight(const float& elapsed = 1.0);
            void MoveUp(const float& elapsed = 1.0);
            void MoveDown(const float& elapsed = 1.0);
            void UpdateProjectionRatio(const float& ratio);
            void Update();

            const glm::mat4& get_m() const;
            const glm::mat4& get_v() const;
            const glm::mat4& get_p() const;
            const glm::mat4& get_mv() const;
            const glm::mat4& get_vp() const;
            const glm::mat4& get_mvp() const;

        private:
            void UpdateModelMatrix();
            void UpdateViewMatrix();
            void UpdateProjectionMatrix();

            float SmoothMove(const float& elapsed);

        private:
            glm::mat4 clip = glm::mat4{
                1.0, 0.0, 0.0, 0.0,
                0.0, -1.0, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                0.0, 0.0, 0.5, 1.0 };


            float mouse_speed_;
            float horizontal_angle_;
            float vertical_angle_;
            float move_pace_;

            glm::mat4 Model_;
            glm::mat4 View_;
            glm::mat4 Projection_;

            glm::vec3 view_direction_;
            glm::vec3 view_right_;

            glm::vec3 view_position_;
            glm::vec3 view_center_;
            glm::vec3 view_up_;

            float projection_angle_;
            float projection_ratio_;
            float projection_near_;
            float projection_far_;

            

        };
    }
}





