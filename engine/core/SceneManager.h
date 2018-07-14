/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// SceneManager class for manager scene.
/// SceneManager for convenient manager scene.

#pragma once

#include "CoreObject.h"

namespace qe {
    namespace core {
        class Scene;

        class DLL_EXPORT SceneManager : public CoreObject {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="SceneManager"/> class.
            /// </summary>
            explicit SceneManager();

            /// <summary>
            /// Finalizes an instance of the <see cref="SceneManager"/> class.
            /// </summary>
            ~SceneManager();

            /// <summary>
            /// Load a scene to main scene, generate a new main scene.
            /// </summary>
            /// <param name="scene"> for be loaded to main scene.</param>
            /// <param name="main_scene"> main scene.</param>
            void Load(std::shared_ptr<Scene> scene, std::shared_ptr<Scene> main_scene);

            /// <summary>
            ///  Unload a scene from main scene.
            /// </summary>
            /// <param name="scene"> is will be unloaded scene from main scene.</param>
            /// <param name="main_scene">The main scene.</param>
            void Unload(std::shared_ptr<Scene> scene, std::shared_ptr<Scene> main_scene);

        };
    }
}