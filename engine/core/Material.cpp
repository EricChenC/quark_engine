#include "Material.h"
#include "Shader.h"

qe::core::Material::Material()
{
}

qe::core::Material::Material(std::shared_ptr<Shader> shader)
    : shader_(shader)
{

}

qe::core::Material::~Material()
{
}

std::shared_ptr<qe::core::Shader> qe::core::Material::get_shader()
{
    return shader_;
}

void qe::core::Material::set_shader(std::shared_ptr<Shader> shader)
{
    shader_ = shader;
}

