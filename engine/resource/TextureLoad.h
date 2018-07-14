/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "ResourceObject.h"

namespace qe {
    namespace core {
        class Texture;
    }

    namespace resource {
        class DLL_EXPORT TextureLoad : public ResourceObject {
        public:
            explicit TextureLoad();
            ~TextureLoad();

            std::shared_ptr<qe::core::Texture> Load(const std::string & path);

        };
    }

}