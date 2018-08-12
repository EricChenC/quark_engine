#include "Shader.h"
#include "Texture.h"


qe::core::Shader::Shader()
    : 
    shader_data_type_map_(std::make_shared<std::map<std::string, ShaderDataType>>()),
    color_map_(std::make_shared<std::map<std::string, glm::vec4>>()),
    color_list_map_(std::make_shared<std::map<std::string, std::list<glm::vec4>>>()),
    float_map_(std::make_shared<std::map<std::string, float>>()),
    float_list_map_(std::make_shared<std::map<std::string, std::list<float>>>()),
    int_map_(std::make_shared<std::map<std::string, int>>()),
    int_list_map_(std::make_shared<std::map<std::string, std::list<int>>>()),
    mat_map_(std::make_shared<std::map<std::string, glm::mat4>>()),
    mat_list_map_(std::make_shared<std::map<std::string, std::list<glm::mat4>>>()),
    texture_map_(std::make_shared<std::map<std::string, std::shared_ptr<Texture>>>()),
    texture_list_map_(std::make_shared<std::map<std::string, std::list<std::shared_ptr<Texture>>>>()),
    vec_map_(std::make_shared<std::map<std::string, glm::vec4>>()),
    vec_list_map_(std::make_shared<std::map<std::string, std::list<glm::vec4>>>())
{
 

}

qe::core::Shader::~Shader()
{

}




