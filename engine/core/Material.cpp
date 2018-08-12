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



