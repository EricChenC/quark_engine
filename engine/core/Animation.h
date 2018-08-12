/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Animation can play,pause,stop.

#pragma once

#include "Component.h"

namespace qe {
    namespace core {
        class DLL_EXPORT Animation : public Component {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Animation"/> class.
            /// </summary>
            explicit Animation();

            /// <summary>
            /// Finalizes an instance of the <see cref="Animation"/> class.
            /// </summary>
            ~Animation();

        // methods
        public:

            /// <summary>
            /// Play animation, if no animation will no effect.
            /// </summary>
            void Play();

            /// <summary>
            /// Pause animation. if no animation will no effect.
            /// </summary>
            void Pause();

            /// <summary>
            /// Stop animation. if no animation will no effect.
            /// </summary>
            void Stop();

        };
    }

}