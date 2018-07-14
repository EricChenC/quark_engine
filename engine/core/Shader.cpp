#include "Shader.h"
#include "Texture.h"

#include <stdexcept>

qe::core::Shader::Shader()
{
    shader_data_type_map_ = std::make_shared<std::map<std::string, ShaderDataType>>();

    color_map_ = std::make_shared<std::map<std::string, glm::vec4>>();

    color_list_map_ = std::make_shared<std::map<std::string, std::list<glm::vec4>>>();

    float_map_ = std::make_shared<std::map<std::string, float>>();

    float_list_map_ = std::make_shared<std::map<std::string, std::list<float>>>();

    int_map_ = std::make_shared<std::map<std::string, int>>();

    int_list_map_ = std::make_shared<std::map<std::string, std::list<int>>>();

    mat_map_ = std::make_shared<std::map<std::string, glm::mat4>>();

    mat_list_map_ = std::make_shared<std::map<std::string, std::list<glm::mat4>>>();

    texture_map_ = std::make_shared<std::map<std::string, std::shared_ptr<Texture>>>();

    texture_list_map_ = std::make_shared<std::map<std::string, std::list<std::shared_ptr<Texture>>>>();

    vec_map_ = std::make_shared<std::map<std::string, glm::vec4>>();

    vec_list_map_ = std::make_shared<std::map<std::string, std::list<glm::vec4>>>();

}

qe::core::Shader::~Shader()
{

}

std::string qe::core::Shader::get_path()
{
    return path_;
}

void qe::core::Shader::set_path(const std::string & path)
{
    path_ = path;
}

glm::vec4 qe::core::Shader::get_global_color(const std::string & name)
{
    glm::vec4 color(0.0);

    auto it = color_map_->find(name);
    if (it != color_map_->end())
        color = color_map_->at(name);

    return color;
}

std::list<glm::vec4> qe::core::Shader::get_global_color_array(const std::string & name)
{
    std::list<glm::vec4> color_list;

    auto it = color_list_map_->find(name);
    if (it != color_list_map_->end())
        color_list = color_list_map_->at(name);

    return color_list;
}

float qe::core::Shader::get_global_float(const std::string & name)
{
    float value = 0.0;

    auto it = float_map_->find(name);
    if (it != float_map_->end())
        value = float_map_->at(name);

    return value;
}

std::list<float> qe::core::Shader::get_global_float_array(const std::string & name)
{
    std::list<float> float_list;

    auto it = float_list_map_->find(name);
    if (it != float_list_map_->end())
        float_list = float_list_map_->at(name);

    return float_list;
}

int qe::core::Shader::get_global_int(const std::string & name)
{
    int value = 0;

    auto it = int_map_->find(name);
    if (it != int_map_->end())
        value = int_map_->at(name);

    return value;
}

std::list<int> qe::core::Shader::get_global_int_array(const std::string & name)
{
    std::list<int> int_list;

    auto it = int_list_map_->find(name);
    if (it != int_list_map_->end())
        int_list = int_list_map_->at(name);

    return int_list;
}

glm::mat4 qe::core::Shader::get_global_matrix(const std::string & name)
{
    glm::mat4 mat;

    auto it = mat_map_->find(name);
    if (it != mat_map_->end())
        mat = mat_map_->at(name);

    return mat_map_->at(name);
}

std::list<glm::mat4> qe::core::Shader::get_global_matrix_array(const std::string & name)
{
    std::list<glm::mat4> mat_list;

    auto it = mat_list_map_->find(name);
    if (it != mat_list_map_->end())
        mat_list = mat_list_map_->at(name);

    return mat_list;
}

std::shared_ptr<qe::core::Texture> qe::core::Shader::get_global_texture(const std::string & name)
{
    auto texture = std::make_shared<qe::core::Texture>();

    auto it = texture_map_->find(name);
    if (it != texture_map_->end())
        texture = texture_map_->at(name);

    return texture;
}

std::list<std::shared_ptr<qe::core::Texture>> qe::core::Shader::get_global_texture_array(const std::string & name)
{
    std::list<std::shared_ptr<qe::core::Texture>> texture_list;

    auto it = texture_list_map_->find(name);
    if (it != texture_list_map_->end())
        texture_list = texture_list_map_->at(name);

    return texture_list;
}

glm::vec4 qe::core::Shader::get_global_vector(const std::string & name)
{
    glm::vec4 vec;

    auto it = vec_map_->find(name);
    if (it != vec_map_->end())
        vec = vec_map_->at(name);

    return vec;
}

std::list<glm::vec4> qe::core::Shader::get_global_vector_array(const std::string & name)
{
    std::list<glm::vec4> vec_list;

    auto it = vec_list_map_->find(name);
    if (it != vec_list_map_->end())
        vec_list = vec_list_map_->at(name);

    return vec_list;
}

auto qe::core::Shader::get_shader_map() -> std::shared_ptr<std::map<std::string, qe::core::Shader::ShaderDataType>>
{
    return shader_data_type_map_;
}

void qe::core::Shader::set_global_color(const std::string& name, const glm::vec4 & color)
{

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

void qe::core::Shader::set_global_color_array(const std::string & name, const std::list<glm::vec4>& color_list)
{
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

void qe::core::Shader::set_global_float(const std::string& name, const float & value)
{
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

void qe::core::Shader::set_global_float_array(const std::string& name, const std::list<float>& value_list)
{
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

void qe::core::Shader::set_global_int(const std::string& name, const int & value)
{
    auto it = shader_data_type_map_->find(name);
    if (it == shader_data_type_map_->end()) {
        throw std::runtime_error("can't find this property");
        return;
    }

    if (it->second != ShaderDataType::INT) {
        throw std::runtime_error("property not int data type");
        return;
    }

    int_map_->emplace(name,value);
}

void qe::core::Shader::set_global_int_array(const std::string & name, const std::list<int>& value_list)
{
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

void qe::core::Shader::set_global_matrix(const std::string& name, const glm::mat4 & mat)
{
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

void qe::core::Shader::set_global_matrix_array(const std::string& name, const std::list<glm::mat4>&& mat_list)
{
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

void qe::core::Shader::set_global_texture(const std::string& name, std::shared_ptr<Texture> texture)
{

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

void qe::core::Shader::set_global_texture_array(const std::string& name, const std::list<std::shared_ptr<Texture>>& texture_list)
{
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

void qe::core::Shader::set_global_vector(const std::string& name, const glm::vec4 & vec)
{
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

void qe::core::Shader::set_global_vector_array(const std::string& name, const std::list<glm::vec4>& vec_list)
{
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

void qe::core::Shader::set_shader_map(const std::string & name, const ShaderDataType & type)
{
    shader_data_type_map_->emplace(name, type);
}




