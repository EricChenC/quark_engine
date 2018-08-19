/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include <glm/matrix.hpp>

#include "ScriptBehaviour.h"


namespace qe {
    namespace core {
        class Camera;
        class Transform;

        class CameraController : public ScriptBehaviour
        {
        public:
            explicit CameraController();
            ~CameraController();

        // methods
        public:
            inline auto M() const -> const glm::mat4& { return Model_; }

            inline auto V() const -> const glm::mat4& { return View_; }

            inline auto P() const -> const glm::mat4& { return Projection_; }

            inline auto MV() const -> const glm::mat4& { return View_ * Model_; }

            inline auto VP() const -> const glm::mat4&{ return Projection_ * View_; }

            inline auto MVP() const -> const glm::mat4&{ return Projection_ * View_ * Model_; }

            inline auto get_camera() const -> const std::shared_ptr<Camera>&{ return camera_; }

            /// <summary>
            /// Rotates the camera in screen space.(mouse right key)
            /// </summary>
            /// <param name="pos">The screen position.</param>
            void RotateCamera(const glm::vec2& pos);

            /// <summary>
            /// Smoothes zoom the camera.(Alt + mouse right key)
            /// almost 1 / 5 step.
            /// </summary>
            /// <param name="delta_time">The delta time.</param>
            void SmoothZoom(const float& delta_time);

            /// <summary>
            /// Drags the camera in screen space. (mouse middle key)
            /// </summary>
            /// <param name="pos">The screen position.</param>
            void DragCamera(const glm::vec2& pos);

            /// <summary>
            /// Zooms the camera in specified delta time.(mouse middle key)
            /// almost 1 / 2 step.
            /// </summary>
            /// <param name="delta_time">The delta time.</param>
            void Zoom(const float& delta_time);

            /// <summary>
            /// Rotate camera around lookat point. (Alt + mouse left key)
            /// </summary>
            /// <param name="pos">The screen position.</param>
            void LookAtRotate(const glm::vec2& pos);

            /// <summary>
            /// Shrinks move the camera by specified delta time.(W(S) + mouse right key)
            /// </summary>
            /// <param name="delta_time">The delta time.</param>
            void ShrinkMove(const float& delta_time);

            /// <summary>
            /// Horizontals move the camera.(A(D) + mouse right key)
            /// </summary>
            /// <param name="delta_time">The delta time.</param>
            void HorizontalMove(const float& delta_time);
            
            /// <summary>
            /// Verticals move the camera.(E(Q) + mouse right key)
            /// </summary>
            /// <param name="delta_time">The delta time.</param>
            void VerticalMove(const float& delta_time);

            /// <summary>
            /// Looks at object.(F)
            /// </summary>
            void LookAtObject();

            void Awake();

            void Update();

        private:
            void UpdateModelMatrix();
            void UpdateViewMatrix();
            void UpdateProjectionMatrix();

            void UpdateDirection();

        private:
            std::shared_ptr<Camera> camera_;
            std::shared_ptr<Transform> transform_;

            glm::mat4 clip_;

            float rotation_speed_;
            float movement_speed_;

            glm::mat4 Model_;
            glm::mat4 View_;
            glm::mat4 Projection_;

            glm::vec3 view_direction_;
            glm::vec3 lookat_point_;

            bool is_lookat_rotate_;

        };
    }
}





