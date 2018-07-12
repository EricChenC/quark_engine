/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace qe {
    namespace core {
        class Light : public Component {
        public:
            explicit Light();
            ~Light();

            glm::vec3 get_color();

        };
    }

}