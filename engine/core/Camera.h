/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace qe {
    namespace core {
        class Camera : public Component {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Camera"/> class.
            /// </summary>
            explicit Camera();

            /// <summary>
            /// Finalizes an instance of the <see cref="Camera"/> class.
            /// </summary>
            ~Camera();

            glm::vec3 get_look_at();

            /// <summary>
            /// Gets the near plane.
            /// </summary>
            /// <returns> Gets the near plane. </returns>
            int get_near();

            /// <summary>
            /// Gets the far.
            /// </summary>
            /// <returns> Gets the far plane. </returns>
            int get_far();

        };
    }
}