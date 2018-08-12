#include "ShaderLoad.h"
#include "Shader.h"
#include "QuarkString.h"

qe::resource::ShaderLoad::ShaderLoad()
{
}

qe::resource::ShaderLoad::~ShaderLoad()
{
}

std::shared_ptr<qe::core::Shader> qe::resource::ShaderLoad::Load(const std::string & path)
{
    auto shader = std::make_shared<core::Shader>();

    shader->set_path(path);

    shader->set_name(qe::core::QuarkString::FileName(path));

    // read shader file
    // fill shader map
    shader->set_shader_map("lightDir", qe::core::Shader::ShaderDataType::VECTOR);

    return shader;
}


