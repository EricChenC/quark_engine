#include "Scene.h"
#include "QuarkObject.h"


qe::core::Scene::Scene()
{
}

qe::core::Scene::~Scene()
{
}

std::vector<std::shared_ptr<qe::core::QuarkObject>> qe::core::Scene::get_roots()
{
    return roots_;
}

void qe::core::Scene::add_root(std::shared_ptr<qe::core::QuarkObject> root)
{
    root->set_scene(this);

    roots_.push_back(root);
}
