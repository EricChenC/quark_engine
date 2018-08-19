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

            // static methods
        public:
            static std::shared_ptr<Color> Black() {
                return std::make_shared<Color>(0, 0, 0, 1);
            }

            static std::shared_ptr<Color> Blue() {
                return std::make_shared<Color>(0, 0, 1, 1);
            }

            static std::shared_ptr<Color> Clear() {
                return std::make_shared<Color>(0, 0, 0, 0);
            }

            static std::shared_ptr<Color> Cyan() {
                return std::make_shared<Color>(0, 1, 1, 1);
            }

            static std::shared_ptr<Color> Gray() {
                return std::make_shared<Color>(0.5, 0.5, 0.5, 1);
            }

            static std::shared_ptr<Color> Green() {
                return std::make_shared<Color>(0, 1, 0, 1);
            }

            static std::shared_ptr<Color> Magenta() {
                return std::make_shared<Color>(1, 0, 1, 1);
            }

            static std::shared_ptr<Color> Red() {
                return std::make_shared<Color>(1, 0, 0, 1);
            }

            static std::shared_ptr<Color> White() {
                return std::make_shared<Color>(1, 1, 1, 1);
            }

            static std::shared_ptr<Color> Yellow() {
                return std::make_shared<Color>(1, 0.92, 0.016, 1);
            }

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
            glm::vec4 get_glm_color(const Color& color);

        private:
            float r_;
            float g_;
            float b_;
            float a_;

        };
    }
}

