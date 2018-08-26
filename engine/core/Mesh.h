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


        // properties
        public:

            /// <summary>
            /// Gets the vertexs.
            /// </summary>
            /// <returns> mesh vertexs data pointer. </returns>
            inline auto get_vertexs() const -> const std::shared_ptr<std::vector<glm::vec3>>& { return vertexs_; };

            /// <summary>
            /// Set vertex data to mesh.
            /// </summary>
            /// <param name="vertexs">The mesh vertex data.</param>
            inline auto set_vertexs(const std::shared_ptr<std::vector<glm::vec3>>& vertexs) { vertexs_ = vertexs; };

            /// <summary>
            /// Gets the normals.
            /// </summary>
            /// <returns> mesh normals data pointer. </returns>
            inline auto get_normals() const -> const std::shared_ptr<std::vector<glm::vec3>>& { return normals_; };

            /// <summary>
            /// Set normal data to mesh.
            /// </summary>
            /// <param name="normals">The mesh normal data.</param>
            inline auto set_normals(const std::shared_ptr<std::vector<glm::vec3>>& normals) { normals_ = normals; };

            /// <summary>
            /// Gets the uvs.
            /// </summary>
            /// <returns>mesh uv data pointer.</returns>
            inline auto get_uvs() const -> const std::shared_ptr<std::vector<glm::vec2>>& { return uvs_; };

            /// <summary>
            /// Set uv data to mesh.
            /// </summary>
            /// <param name="uvs">The mesh uv data.</param>
            inline auto set_uvs(const std::shared_ptr<std::vector<glm::vec2>>& uvs) { uvs_ = uvs; };

            /// <summary>
            /// Gets the indexs.
            /// </summary>
            /// <returns>mesh vertex index data pointer.</returns>
            inline auto get_indexs() const -> std::shared_ptr<std::vector<unsigned int>> { return indexs_; };

            /// <summary>
            /// Set index data to mesh.
            /// </summary>
            /// <param name="indexs">The mesh index data.</param>
            inline auto set_indexs(const std::shared_ptr<std::vector<unsigned int>>& indexs) { indexs_ = indexs; };

            /// <summary>
            /// Gets the vertex count.
            /// </summary>
            /// <returns>mesh vertex count.</returns>
            inline auto get_vertex_count() const -> const int& { return vertex_count_; };

            /// <summary>
            /// Set vertex count.
            /// </summary>
            /// <param name="vertexs_count">The mesh vertex count.</param>
            inline auto set_vertexs_count(const int& vertexs_count) { vertex_count_ = vertexs_count; };

            /// <summary>
            /// Gets the normal count.
            /// </summary>
            /// <returns>mesh normal count.</returns>
            inline auto get_normal_count() const -> const int& { return normal_count_; };

            /// <summary>
            /// Sets the normals count.
            /// </summary>
            /// <param name="normals_count">The normals count.</param>
            inline auto set_normals_count(const int& normals_count) { normal_count_ = normals_count; };

            /// <summary>
            /// Gets the uv count.
            /// </summary>
            /// <returns>mesh uv count.</returns>
            inline auto get_uv_count() const -> const int& { return uv_count_; };

            /// <summary>
            /// Sets the uvs count.
            /// </summary>
            /// <param name="uvs_count">The uvs count.</param>
            inline auto set_uvs_count(const int& uvs_count) { uv_count_ = uvs_count; };

            /// <summary>
            /// Gets the index count.
            /// </summary>
            /// <returns>mesh vertex index count.</returns>
            inline auto get_index_count() const -> const int& { return index_count_; };

            /// <summary>
            /// Sets the indexs count.
            /// </summary>
            /// <param name="indexs_count">The indexs count.</param>
            inline auto set_indexs_count(const int& indexs_count) { index_count_ = indexs_count; };


            /// <summary>
            /// Gets the type.
            /// </summary>
            /// <returns></returns>
            inline auto get_type() const -> const MeshType& { return type_; }

            /// <summary>
            /// Set this mesh type.
            /// </summary>
            /// <param name="type">type is this mesh type.</param>
            inline auto set_type(const MeshType& type) { type_ = type; };

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