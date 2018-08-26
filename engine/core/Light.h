/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "Behaviour.h"

namespace qe {
    namespace core {

        struct Color;

        class DLL_EXPORT Light : public Behaviour {
        public:
            enum class LightType
            {
                SPOT,
                DIRECTIONAL,
                POINT,
                AREA
            };

            enum class LightShadows
            {
                NONE,
                HARD,
                SOFT
            };

        public:
            explicit Light();
            ~Light();

        // properties
        public:
            inline auto get_area_size() const -> const glm::vec2& { return area_size_; }

            inline void set_area_size(const glm::vec2& size) { area_size_ = size; }

            inline auto get_baking_output() const -> const LightBakingOutput& { return baking_output_; }

            inline void set_baking_output(const LightBakingOutput& output) { baking_output_ = output; }

            inline auto get_color() const -> const std::shared_ptr<Color>& { return color_; }

            inline void set_color(const std::shared_ptr<Color>& color){ color_ = color; }






        private:
            glm::vec2 area_size_;

            LightBakingOutput baking_output_;

            std::shared_ptr<Color> color_;

        };
    }

}