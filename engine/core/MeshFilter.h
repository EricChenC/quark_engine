/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#include "Component.h"

namespace qe {
    namespace core {
        class Mesh;

        class MeshFilter : public Component 
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


            /// <summary>
            /// Gets the render mesh.
            /// </summary>
            /// <returns>the render mesh</returns>
            auto get_mesh()->std::shared_ptr<Mesh>;

            /// <summary>
            /// Sets the render mesh.
            /// </summary>
            /// <param name="mesh">The mesh.</param>
            void set_mesh(std::shared_ptr<Mesh> mesh);


        private:
            /// <summary>
            /// The mesh for render
            /// </summary>
            std::shared_ptr<Mesh> mesh_;

        };
    }
}