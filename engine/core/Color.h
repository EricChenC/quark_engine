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
        class DLL_EXPORT Color : public CoreObject
        {
        public:
            explicit Color();

            Color(const float&r, const float&g, const float&b, const float&a);

            ~Color();

        // properties
        public:
            inline auto get_r()const -> const float& { return r_; }

            inline void set_r(const float& r){ r_ = r; }

            inline auto get_g()const -> const float& { return g_; }

            inline void set_g(const float& g){ g_ = g; }

            inline auto get_b()const -> const float& { return b_; }

            inline void set_b(const float& b){ b_ = b; }

            inline auto get_a()const -> const float& { return a_; }

            inline void set_a(const float& a){ a_ = a; }


        // methods
        public:
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

