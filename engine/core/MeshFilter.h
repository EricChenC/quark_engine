/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#include "Component.h"

namespace qe {
    namespace core {
        class Mesh;

        class DLL_EXPORT MeshFilter : public Component
        {
        public:
            /// <summary>
            /// Prevents a default instance of the <see cref="MeshFilter"/> class from being created.
            /// </summary>
            explicit MeshFilter();

            /// <summary>
            /// Finalizes an instance of the <see cref="MeshFilter"/> class.
            /// </summary>
            ~MeshFilter();


        // properties
        public:
            /// <summary>
            /// Gets the render mesh.
            /// </summary>
            /// <returns>the render mesh</returns>
            inline auto get_mesh() const->const std::shared_ptr<Mesh>&{ return mesh_; }

            /// <summary>
            /// Sets the render mesh.
            /// </summary>
            /// <param name="mesh">The mesh.</param>
            inline auto set_mesh(const std::shared_ptr<Mesh>& mesh){ mesh_ = mesh; }


        private:
            /// <summary>
            /// The mesh for render
            /// </summary>
            std::shared_ptr<Mesh> mesh_;

        };
    }
}