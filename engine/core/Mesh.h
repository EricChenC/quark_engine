/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// Mesh class save polygon data vertex, normal, uv, index.

/// Mesh have POINTS, LINES, TRIANGLES, POLYGON, mesh type.
/// POLYGON mesh type is a special mesh type in fbx or other file format.
/// Mesh saved all mesh data for draw.

#pragma once

#include "CoreObject.h"

#include <vector>
#include <map>
#include <glm/glm.hpp>


namespace qe {
    namespace core {
        class DLL_EXPORT Mesh : public CoreObject {
        public:
            
            /// <summary>
            /// MeshType have four mesh type.
            ///
            /// POINTS is point mesh type.
            /// LINES is lines mesh type.
            /// TRIANGLES is triangles mesh type.
            /// POLYGON is polygon mesh type (uncommon mesh type).
            ///
            /// </summary>
            enum class MeshType {
                POINTS,
                LINES,
                TRIANGLES,
                POLYGON
            };

        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Mesh"/> class.
            /// </summary>
            explicit Mesh();

            /// <summary>
            /// Finalizes an instance of the <see cref="Mesh"/> class.
            /// </summary>
            ~Mesh();

            /// <summary>
            /// Set vertex data to mesh.
            /// </summary>
            /// <param name="vertexs">The mesh vertex data.</param>
            void set_vertexs(std::shared_ptr<std::vector<glm::vec3>> vertexs) { vertexs_ = vertexs; };

            /// <summary>
            /// Set normal data to mesh.
            /// </summary>
            /// <param name="normals">The mesh normal data.</param>
            void set_normals(std::shared_ptr<std::vector<glm::vec3>> normals) { normals_ = normals; };

            /// <summary>
            /// Set uv data to mesh.
            /// </summary>
            /// <param name="uvs">The mesh uv data.</param>
            void set_uvs(std::shared_ptr<std::vector<glm::vec2>> uvs) { uvs_ = uvs; };

            /// <summary>
            /// Set index data to mesh.
            /// </summary>
            /// <param name="indexs">The mesh index data.</param>
            void set_indexs(std::shared_ptr<std::vector<unsigned int>> indexs) { indexs_ = indexs; };

            /// <summary>
            /// Set vertex count.
            /// </summary>
            /// <param name="vertexs_count">The mesh vertex count.</param>
            void set_vertexs_count(const int& vertexs_count) { vertex_count_ = vertexs_count; };

            /// <summary>
            /// Sets the normals count.
            /// </summary>
            /// <param name="normals_count">The normals count.</param>
            void set_normals_count(const int& normals_count) { normal_count_ = normals_count; };

            /// <summary>
            /// Sets the uvs count.
            /// </summary>
            /// <param name="uvs_count">The uvs count.</param>
            void set_uvs_count(const int& uvs_count) { uv_count_ = uvs_count; };

            /// <summary>
            /// Sets the indexs count.
            /// </summary>
            /// <param name="indexs_count">The indexs count.</param>
            void set_indexs_count(const int& indexs_count) { index_count_ = indexs_count; };

            /// <summary>
            /// Gets the vertexs.
            /// </summary>
            /// <returns> mesh vertexs data pointer. </returns>
            std::shared_ptr<std::vector<glm::vec3>> get_vertexs() { return vertexs_; };

            /// <summary>
            /// Gets the normals.
            /// </summary>
            /// <returns> mesh normals data pointer. </returns>
            std::shared_ptr<std::vector<glm::vec3>> get_normals() { return normals_; };

            /// <summary>
            /// Gets the uvs.
            /// </summary>
            /// <returns>mesh uv data pointer.</returns>
            std::shared_ptr<std::vector<glm::vec2>> get_uvs() { return uvs_; };

            /// <summary>
            /// Gets the indexs.
            /// </summary>
            /// <returns>mesh vertex index data pointer.</returns>
            std::shared_ptr<std::vector<unsigned int>> get_indexs() { return indexs_; };

            /// <summary>
            /// Gets the vertex count.
            /// </summary>
            /// <returns>mesh vertex count.</returns>
            int get_vertex_count() { return vertex_count_; };

            /// <summary>
            /// Gets the normal count.
            /// </summary>
            /// <returns>mesh normal count.</returns>
            int get_normal_count() { return normal_count_; };

            /// <summary>
            /// Gets the uv count.
            /// </summary>
            /// <returns>mesh uv count.</returns>
            int get_uv_count() { return uv_count_; };

            /// <summary>
            /// Gets the index count.
            /// </summary>
            /// <returns>mesh vertex index count.</returns>
            int get_index_count() { return index_count_; };

            /// <summary>
            /// Set this mesh type.
            /// </summary>
            /// <param name="type">type is this mesh type.</param>
            void set_type(MeshType type) { type_ = type; };

        private:
            /// mesh vertexs data pointer.
            std::shared_ptr<std::vector<glm::vec3>>      vertexs_;

            /// mesh normals data pointer.
            std::shared_ptr<std::vector<glm::vec3>>      normals_;

            /// mesh uvs data pointer.
            std::shared_ptr<std::vector<glm::vec2>>      uvs_;

            /// mesh vertex index data pointer.
            std::shared_ptr<std::vector<unsigned int>>  indexs_;

            /// mesh vertex count.
            int vertex_count_;

            /// mesh normal count.
            int normal_count_;

            /// mesh uv count.
            int uv_count_;

            /// mesh vertex index count.
            int index_count_;

            /// this mesh type.
            MeshType type_;

        };
    }
}