/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 8/7/2018 11:14:31 PM
/// author: eric
/// class description ....

#pragma once

#include "Texture.h"

namespace qe {
    namespace core
    {
        class RenderTexture : public Texture
        {
        public:
            explicit RenderTexture();
            ~RenderTexture();
        };
    }
}

