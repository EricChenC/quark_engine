/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Resource is a quark engine resource class.
/// Quark engine KResource class is used assimp library load model.

#pragma once

#include "CoreObject.h"

namespace qe {

    namespace resource {
        class FBXLoad;
        class TextureLoad;
        class ShaderLoad;
    }

    namespace core {

        class DLL_EXPORT Resource : public CoreObject {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Resource"/> class.
            /// </summary>
            explicit Resource();

            /// <summary>
            /// Finalizes an instance of the <see cref="Resource"/> class.
            /// </summary>
            ~Resource();

            /// <summary>
            /// load model from model path, if no model return nullptr.
            /// if model path is invalid or have error, return nullptr.
            /// </summary>
            /// <param name="path"> is load model path.</param>
            /// <returns> a scene has loaded model from model path,</returns>
            std::shared_ptr<CoreObject> Load(const std::string& path);

        private:
            std::shared_ptr<resource::FBXLoad> fbx_load_;

            std::shared_ptr<resource::TextureLoad> texture_load_;

            std::shared_ptr<resource::ShaderLoad> shader_load_;

        };
    }
}