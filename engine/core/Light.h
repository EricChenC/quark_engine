/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace qe {
    namespace core {

        class Color;

        class DLL_EXPORT Light : public Component {
        public:
            explicit Light();
            ~Light();

        // properties
        public:
            inline auto get_color() const -> const std::shared_ptr<Color>& { return color_; }

            inline void set_color(const std::shared_ptr<Color>& color){ color_ = color; }

        private:
            std::shared_ptr<Color> color_;

        };
    }

}