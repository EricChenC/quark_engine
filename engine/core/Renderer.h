/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "Component.h"

#include <vector>

namespace qe {
    namespace core {
        class Material;

        class Renderer : public Component {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Renderer"/> class.
            /// </summary>
            explicit Renderer();

            /// <summary>
            /// Finalizes an instance of the <see cref="Renderer"/> class.
            /// </summary>
            ~Renderer();

            /// <summary>
            /// Gets the first material in renderer.
            ///if no material return nullptr.
            /// </summary>
            /// <returns>first material or nullptr</returns>
            auto get_material()->std::shared_ptr<Material>;

            /// <summary>
            /// Gets the all materials of object.
            /// </summary>
            /// <returns>all materials</returns>
            auto get_materials()->std::vector<std::shared_ptr<Material>>;

            /// <summary>
            /// Adds the material to object.
            /// </summary>
            /// <param name="material">The material.</param>
            void add_material(std::shared_ptr<Material> material);

            /// <summary>
            /// Gets whether the object enable in camera.
            /// </summary>
            /// <returns> whether enable in camera </returns>
            bool get_enable();


            /// <summary>
            /// Sets the object enable in camera.
            /// </summary>
            /// <param name="enable">if set to <c>true</c> [enable] in camera.</param>
            void set_enable(bool enable);


        private:
            /// <summary>
            /// The object materials
            /// </summary>
            std::vector<std::shared_ptr<Material>> materials_;

            /// <summary>
            /// whether enable object in camera
            /// </summary>
            bool enable_;
            
        };
    }
}


