/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 8/7/2018 11:18:58 PM
/// author: eric
/// class description ....

#pragma once

#include "CoreObject.h"

#include <glm/glm.hpp>

namespace qe {
    namespace core
    {
        class Color : public CoreObject
        {
        public:
            explicit Color();

            Color(const float&r, const float&g, const float&b, const float&a);

            ~Color();

            void set_r(const float& r);

            void set_g(const float& g);

            void set_b(const float& b);

            void set_a(const float& a);

            const float& get_r();

            const float& get_g();

            const float& get_b();

            const float& get_a();

            Color Black();

            Color Blue();

            Color Clear();

            Color Cyan();

            Color Gray();

            Color Green();

            Color Magenta();

            Color Red();

            Color White();

            Color Yellow();

            glm::vec4 get_glm_color(const Color& color);

        private:
            float r_;
            float g_;
            float b_;
            float a_;

        };
    }
}

