/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "ResourceObject.h"

#include <string>
#include <memory>

namespace qe {
    namespace core {
        class Scene;
    }

    namespace resource {
        class FBXLoad : public ResourceObject {
        public:
            explicit FBXLoad() {}
            ~FBXLoad() {}

            std::shared_ptr<qe::core::Scene> Load(const std::string & path);

        private:
            bool gVerbose = true;

        };
    }
}






