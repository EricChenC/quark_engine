#include "Renderer.h"
#include "Material.h"

qe::core::Renderer::Renderer()
{
}

qe::core::Renderer::~Renderer()
{
}

auto qe::core::Renderer::Material() const -> const std::shared_ptr<qe::core::Material>&
{
    if (materials_.size() <= 0) return nullptr;

    return materials_[0];
}

auto qe::core::Renderer::Materials() const -> const std::vector<std::shared_ptr<qe::core::Material>>&
{
    return materials_;
}

void qe::core::Renderer::AddMaterial(const std::shared_ptr<qe::core::Material>& material)
{
    materials_.push_back(material);
}


