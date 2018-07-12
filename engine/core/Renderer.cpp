#include "Renderer.h"
#include "Material.h"

qe::core::Renderer::Renderer()
{
}

qe::core::Renderer::~Renderer()
{
}

auto qe::core::Renderer::get_material() -> std::shared_ptr<Material>
{
    if (materials_.size() <= 0) return nullptr;

    return materials_[0];
}

auto qe::core::Renderer::get_materials() -> std::vector<std::shared_ptr<Material>>
{
    return materials_;
}

void qe::core::Renderer::add_material(std::shared_ptr<Material> material)
{
    materials_.push_back(material);
}

bool qe::core::Renderer::get_enable()
{
    return enable_;
}

void qe::core::Renderer::set_enable(bool enable)
{
    enable_ = enable;
}
