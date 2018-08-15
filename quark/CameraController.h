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

            enum class CameraType
            {
                LOOKAT,
                FIRSTPERSON,
                THIRDPERSON
            };

        // properties
        public:
            inline auto get_type() const -> const CameraType& { return type_; }

            inline void set_type(const CameraType& type) { type_ = type; }

        // methods
        public:
            inline auto M() const -> const glm::mat4& { return Model_; }

            inline auto V() const -> const glm::mat4& { return View_; }

            inline auto P() const -> const glm::mat4& { return Projection_; }

            inline auto MV() const -> const glm::mat4& { return View_ * Model_; }

            inline auto VP() const -> const glm::mat4&{ return Projection_ * View_; }

            inline auto MVP() const -> const glm::mat4&{ return Projection_ * View_ * Model_; }

            void RotateCamera(const glm::vec2& pos);

            void MoveCamera(const glm::vec2& pos);

            void MoveForward(const float& delta_time);

            void MoveBack(const float& delta_time);

            void MoveLeft(const float& delta_time);

            void MoveRight(const float& delta_time);

            void MoveUp(const float& delta_time);

            void MoveDown(const float& delta_time);

            void UpdateProjectionRatio(const float& ratio);

            void Update();

        private:
            void UpdateModelMatrix();
            void UpdateViewMatrix();
            void UpdateProjectionMatrix();

            void UpdateDirection();

        private:
            glm::mat4 clip;

            float rotation_speed_;
            float movement_speed_;

            glm::mat4 Model_;
            glm::mat4 View_;
            glm::mat4 Projection_;

            glm::vec3 view_direction_;
            glm::vec3 view_position_;

            float projection_fov_;
            float projection_ratio_;
            float projection_near_;
            float projection_far_;

            glm::vec3 rotation_;

            CameraType type_;

        };
    }
}





