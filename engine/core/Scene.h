/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Scene for manage quark object.
/// a scene saved all quark object, like a space include objects.
/// a scene for convenient manage quark object.

#pragma once

#include "CoreObject.h"

#include <vector>

namespace qe {
    namespace core {
        class QuarkObject;

        class DLL_EXPORT Scene : public CoreObject {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Scene"/> class.
            /// </summary>
            explicit Scene();

            /// <summary>
            /// Finalizes an instance of the <see cref="Scene"/> class.
            /// </summary>
            ~Scene();

            /// <summary>
            /// Get this scene all root quark objects pointers.
            /// </summary>
            /// <returns>all root quark objects pointers.</returns>
            std::vector<std::shared_ptr<qe::core::QuarkObject>> get_roots();
           
            /// <summary>
            /// Adds the root to scene.
            /// </summary>
            /// <returns>return a root quark object</returns>
            auto add_root()->std::shared_ptr<qe::core::QuarkObject>;

        private:
            /// Saved this scene all quark object roots pointer.
            std::vector<std::shared_ptr<qe::core::QuarkObject>> roots_;

        };
    }

}