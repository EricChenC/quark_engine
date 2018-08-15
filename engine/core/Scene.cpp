#include "Scene.h"
#include "QuarkObject.h"


qe::core::Scene::Scene()
{
}

qe::core::Scene::~Scene()
{
}

auto qe::core::Scene::Roots() const -> const std::vector<std::shared_ptr<qe::core::QuarkObject>>&
{
    return roots_;
}

void qe::core::Scene::AddRoot(std::shared_ptr<qe::core::QuarkObject> root)
{
    root->set_scene(this);
    roots_.push_back(root);
}


