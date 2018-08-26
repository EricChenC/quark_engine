/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "CoreObject.h"

namespace qe {
    namespace core {
        class Shader;

        class DLL_EXPORT Material : public CoreObject {
        public:
            explicit Material();

            explicit Material(std::shared_ptr<Shader> shader);

            ~Material();
            
        // properties
        public:
            inline auto get_shader() const -> const std::shared_ptr<Shader>& { return shader_; };

            inline auto set_shader(const std::shared_ptr<Shader>& shader){ shader_ = shader; }

        private:
            std::shared_ptr<Shader> shader_;

        };
    }
}