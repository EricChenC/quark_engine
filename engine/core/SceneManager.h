/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// SceneManager class for manager scene.
/// SceneManager for convenient manager scene.

#pragma once

#include "CoreObject.h"
#include "Scene.h"

namespace qe {
    namespace core {
        class SceneManager : public CoreObject {
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
            void Load(Scene scene, Scene main_scene);

            /// <summary>
            ///  Unload a scene from main scene.
            /// </summary>
            /// <param name="scene"> is will be unloaded scene from main scene.</param>
            /// <param name="main_scene">The main scene.</param>
            void Unload(Scene scene, Scene main_scene);

        };
    }
}