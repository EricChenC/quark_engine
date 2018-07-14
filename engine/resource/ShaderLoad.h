/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/9/2018 3:58:04 PM
/// author: eric
/// class description ....

#pragma once

#include "ResourceObject.h"

namespace qe {
    namespace core {
        class Shader;
    }

    namespace resource
    {
        class DLL_EXPORT ShaderLoad
        {
        public:
            explicit ShaderLoad();
            ~ShaderLoad();

            std::shared_ptr<core::Shader> Load(const std::string& path);



        };
    }
}

