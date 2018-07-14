/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "CoreObject.h"
#include "Shader.h"


namespace qe {
    namespace core {
        class DLL_EXPORT Material : public CoreObject {
        public:
            explicit Material();

            explicit Material(std::shared_ptr<Shader> shader);

            ~Material();

            std::shared_ptr<Shader> get_shader();

            void set_shader(std::shared_ptr<Shader> shader);

        private:
            std::shared_ptr<Shader> shader_;

        };
    }
}