/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "CoreObject.h"

#include <string>
#include <glm/glm.hpp>
#include <list>
#include <map>
#include <stdexcept>

namespace qe {
    namespace core {
        class Texture;

        class DLL_EXPORT Shader : public CoreObject {
        public:
            enum class ShaderDataType
            {
                COLOR,
                COLORARRAY,
                FLOAT,
                FLOATARRAY,
                INT,
                INTARRAY,
                MATRIX4X4,
                MATRIX4X4ARRAY,
                VECTOR,
                VECTORARRAY,
                TEXTURE1D,
                TEXTURE1DARRAY,
                TEXTURE2D,
                TEXTURE2DARRAY,
                TEXTURE3D,
                TEXTURE3DARRAY
            };

        public:
            explicit Shader();

            ~Shader();

        // properties
        public:

            /// <summary>
            /// Gets the path.
            /// </summary>
            /// <returns></returns>
            inline auto get_path()const -> const std::string& { return path_; }

            /// <summary>
            /// Sets the path.
            /// </summary>
            /// <param name="path">The path.</param>
            inline auto set_path(const std::string& path) { path_ = path; }

            /// <summary>
            /// Gets the color of the global.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_color(const std::string& name) const -> const glm::vec4& {

                auto it = color_map_->find(name);
                if (it != color_map_->end())
                    return color_map_->at(name);

                return glm::vec4(0.0);
            }

            /// <summary>
            /// Sets the color of the global.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="color">The color.</param>
            inline auto set_global_color(const std::string& name, const glm::vec4& color) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::COLOR) {
                    throw std::runtime_error("property not color data type");
                    return;
                }

                color_map_->emplace(name, color);
            }

            /// <summary>
            /// Gets the global color array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_color_array(const std::string& name) const -> const std::list<glm::vec4>& {

                auto it = color_list_map_->find(name);
                if (it != color_list_map_->end())
                    return color_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global color array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="color_list">The color list.</param>
            inline auto set_global_color_array(const std::string& name, const std::list<glm::vec4>& color_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::COLORARRAY) {
                    throw std::runtime_error("property not color array data type");
                    return;
                }

                color_list_map_->emplace(name, color_list);
            }

            /// <summary>
            /// Gets the global float.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_float(const std::string& name) const -> const float& {

                auto it = float_map_->find(name);
                if (it != float_map_->end())
                    return float_map_->at(name);

                return 0.0;
            }

            /// <summary>
            /// Sets the global float.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="value">The value.</param>
            inline auto set_global_float(const std::string& name, const float& value) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::FLOAT) {
                    throw std::runtime_error("property not float data type");
                    return;
                }

                float_map_->emplace(name, value);
            }

            /// <summary>
            /// Gets the global float array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_float_array(const std::string& name)const ->const std::list<float>& {

                auto it = float_list_map_->find(name);
                if (it != float_list_map_->end())
                    return float_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global float array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="value_list">The value list.</param>
            inline auto set_global_float_array(const std::string& name, const std::list<float>& value_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::FLOATARRAY) {
                    throw std::runtime_error("property not float array data type");
                    return;
                }

                float_list_map_->emplace(name, value_list);
            }

            /// <summary>
            /// Gets the global int.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_int(const std::string& name)const -> const int& {

                auto it = int_map_->find(name);
                if (it != int_map_->end())
                    return int_map_->at(name);

                return 0;
            }

            /// <summary>
            /// Sets the global int.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="value">The value.</param>
            inline auto set_global_int(const std::string& name, const int& value) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::INT) {
                    throw std::runtime_error("property not int data type");
                    return;
                }

                int_map_->emplace(name, value);
            }

            /// <summary>
            /// Gets the global int array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_int_array(const std::string& name) const -> const std::list<int>& {

                auto it = int_list_map_->find(name);
                if (it != int_list_map_->end())
                    return int_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global int array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="value_list">The value list.</param>
            inline auto set_global_int_array(const std::string& name, const std::list<int>& value_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::INTARRAY) {
                    throw std::runtime_error("property not int array data type");
                    return;
                }

                int_list_map_->emplace(name, value_list);
            }

            /// <summary>
            /// Gets the global matrix.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_matrix(const std::string& name)const -> const glm::mat4& {

                auto it = mat_map_->find(name);
                if (it != mat_map_->end())
                    return mat_map_->at(name);

                return glm::mat4{};
            }

            /// <summary>
            /// Sets the global matrix.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="mat">The mat.</param>
            inline auto set_global_matrix(const std::string& name, const glm::mat4& mat) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::MATRIX4X4) {
                    throw std::runtime_error("property not matrix data type");
                    return;
                }

                mat_map_->emplace(name, mat);
            }

            /// <summary>
            /// Gets the global matrix array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_matrix_array(const std::string& name) const -> const std::list<glm::mat4>& {

                auto it = mat_list_map_->find(name);
                if (it != mat_list_map_->end())
                    return mat_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global matrix array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="mat_list">The mat list.</param>
            inline auto set_global_matrix_array(const std::string& name, const std::list<glm::mat4>&& mat_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::MATRIX4X4ARRAY) {
                    throw std::runtime_error("property not matrix array data type");
                    return;
                }

                mat_list_map_->emplace(name, mat_list);
            }

            /// <summary>
            /// Gets the global texture.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_texture(const std::string& name) const -> const std::shared_ptr<Texture>& {

                auto it = texture_map_->find(name);
                if (it != texture_map_->end())
                    return texture_map_->at(name);

                return nullptr;
            }


            /// <summary>
            /// Sets the global texture.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="texture">The texture.</param>
            inline auto set_global_texture(const std::string& name, std::shared_ptr<Texture> texture) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::TEXTURE2D) {
                    throw std::runtime_error("property not texture data type");
                    return;
                }

                texture_map_->emplace(name, texture);
            }


            /// <summary>
            /// Gets the global texture array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_texture_array(const std::string& name) const -> const std::list<std::shared_ptr<Texture>>& {

                auto it = texture_list_map_->find(name);
                if (it != texture_list_map_->end())
                    return texture_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global texture array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="texture_list">The texture list.</param>
            inline auto set_global_texture_array(const std::string& name, const std::list<std::shared_ptr<Texture>>& texture_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::TEXTURE2DARRAY) {
                    throw std::runtime_error("property not texture array data type");
                    return;
                }

                texture_list_map_->emplace(name, texture_list);
            }

            /// <summary>
            /// Gets the global vector.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_vector(const std::string& name) const -> const glm::vec4& {

                auto it = vec_map_->find(name);
                if (it != vec_map_->end())
                    return vec_map_->at(name);

                return glm::vec4{};
            }

            /// <summary>
            /// Sets the global vector.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="vec">The vec.</param>
            inline auto set_global_vector(const std::string& name, const glm::vec4& vec) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::VECTOR) {
                    throw std::runtime_error("property not vector data type");
                    return;
                }

                vec_map_->emplace(name, vec);
            }

            /// <summary>
            /// Gets the global vector array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <returns></returns>
            inline auto get_global_vector_array(const std::string& name) const -> const std::list<glm::vec4>& {

                auto it = vec_list_map_->find(name);
                if (it != vec_list_map_->end())
                    return vec_list_map_->at(name);

                return {};
            }

            /// <summary>
            /// Sets the global vector array.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="vec_list">The vec list.</param>
            inline auto set_global_vector_array(const std::string& name, const std::list<glm::vec4>& vec_list) {
                auto it = shader_data_type_map_->find(name);
                if (it == shader_data_type_map_->end()) {
                    throw std::runtime_error("can't find this property");
                    return;
                }

                if (it->second != ShaderDataType::VECTORARRAY) {
                    throw std::runtime_error("property not vector array data type");
                    return;
                }

                vec_list_map_->emplace(name, vec_list);
            }


            /// <summary>
            /// Gets the shader map.
            /// </summary>
            /// <returns></returns>
            inline auto get_shader_map() const -> const std::shared_ptr<std::map<std::string, ShaderDataType>>& {
                return shader_data_type_map_;
            }

            /// <summary>
            /// Sets the shader map.
            /// </summary>
            /// <param name="name">The name.</param>
            /// <param name="type">The type.</param>
            inline auto set_shader_map(const std::string& name, const ShaderDataType& type) {
                shader_data_type_map_->emplace(name, type);
            }

        private:
            std::shared_ptr<std::map<std::string, ShaderDataType>> shader_data_type_map_;

            std::shared_ptr<std::map<std::string, glm::vec4>> color_map_;

            std::shared_ptr<std::map<std::string, std::list<glm::vec4>>> color_list_map_;

            std::shared_ptr<std::map<std::string, float>> float_map_;

            std::shared_ptr<std::map<std::string, std::list<float>>> float_list_map_;

            std::shared_ptr<std::map<std::string, int>> int_map_;

            std::shared_ptr<std::map<std::string, std::list<int>>> int_list_map_;

            std::shared_ptr<std::map<std::string, glm::mat4>> mat_map_;

            std::shared_ptr<std::map<std::string, std::list<glm::mat4>>> mat_list_map_;

            std::shared_ptr<std::map<std::string, std::shared_ptr<Texture>>> texture_map_;

            std::shared_ptr<std::map<std::string, std::list<std::shared_ptr<Texture>>>> texture_list_map_;

            std::shared_ptr<std::map<std::string, glm::vec4>> vec_map_;

            std::shared_ptr<std::map<std::string, std::list<glm::vec4>>> vec_list_map_;

            std::string path_;

        };
    }
}
