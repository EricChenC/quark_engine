/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 8/21/2018 11:51:42 PM
/// author: eric
/// class description ....

#pragma once

#include "CoreObject.h"

namespace qe {
    namespace core
    {
        class Input : public CoreObject
        {
        public:
            explicit Input();
            ~Input();

        // static properties
        public:
            inline static auto get_mouse_position() -> const glm::vec3& { return mouse_position_; }

            inline static auto set_mouse_position(const glm::vec3& position) { mouse_position_ = position; }

            inline static auto get_mouse_scroll_delta() -> const glm::vec2& { return mouse_scroll_delta_; }

            inline static auto set_mouse_scroll_delta(const glm::vec2& delta) { mouse_scroll_delta_ = delta; }


        // static methods
        public:
            inline static void GetAccelerationEvent(){}

            inline static void GetAxis(){}

            inline static void GetAxisRaw(){}

            inline static bool GetButton(){}

            inline static bool GetButtonDown(){}

            inline static bool GetButtonUp(){}

            inline static void GetJoystickNames(){}

            inline static bool GetKey(const KeyCode& key ){}

            inline static bool GetKeyDown(const KeyCode& key){}

            inline static bool GetKeyUp(const KeyCode& key){}

            inline static bool GetMouseButton(const KeyCode& key){}

            inline static bool GetMouseButtonDown(const KeyCode& key){}

            inline static bool GetMouseButtonUp(const KeyCode& key){}

            inline static void GetTouch(){}

            inline static void IsJoystickPreconfigured(){}

            inline static void ResetInputAxes(){}

        private:
            static glm::vec3 mouse_position_;

            static glm::vec2 mouse_scroll_delta_;

        };
    }
}

