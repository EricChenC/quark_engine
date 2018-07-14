/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "CoreObject.h"

#include <string>
#include <glm/glm.hpp>
#include <list>
#include <map>

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

            std::string get_path();

            void set_path(const std::string& path);

            glm::vec4 get_global_color(const std::string& name);

            std::list<glm::vec4> get_global_color_array(const std::string& name);

            float get_global_float(const std::string& name);

            std::list<float> get_global_float_array(const std::string& name);

            int get_global_int(const std::string& name);

            std::list<int> get_global_int_array(const std::string& name);

            glm::mat4 get_global_matrix(const std::string& name);

            std::list<glm::mat4> get_global_matrix_array(const std::string& name);

            std::shared_ptr<Texture> get_global_texture(const std::string& name);

            std::list<std::shared_ptr<Texture>> get_global_texture_array(const std::string& name);

            glm::vec4 get_global_vector(const std::string& name);

            std::list<glm::vec4> get_global_vector_array(const std::string& name);

            auto get_shader_map() -> std::shared_ptr<std::map<std::string, ShaderDataType>>;

            void set_global_color(const std::string& name, const glm::vec4& color);

            void set_global_color_array(const std::string& name, const std::list<glm::vec4>& color_list);

            void set_global_float(const std::string& name, const float& value);

            void set_global_float_array(const std::string& name, const std::list<float>& value_list);

            void set_global_int(const std::string& name, const int& value);

            void set_global_int_array(const std::string& name, const std::list<int>& value_list);

            void set_global_matrix(const std::string& name, const glm::mat4& mat);

            void set_global_matrix_array(const std::string& name, const std::list<glm::mat4>&& mat_list);

            void set_global_texture(const std::string& name, std::shared_ptr<Texture> texture);

            void set_global_texture_array(const std::string& name, const std::list<std::shared_ptr<Texture>>& texture_list);

            void set_global_vector(const std::string& name, const glm::vec4& vec);

            void set_global_vector_array(const std::string& name, const std::list<glm::vec4>& vec_list);

            void set_shader_map(const std::string& name, const ShaderDataType& type);

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
