#include "QuarkObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Component.h"
#include "Material.h"


qe::core::QuarkObject::QuarkObject()
    : id_(0)
{
    transform_ = add_component<qe::core::Transform>();
}

qe::core::QuarkObject::~QuarkObject()
{
}

void qe::core::QuarkObject::set_id(const int & id)
{
    id_ = id;
}

int qe::core::QuarkObject::get_id()
{
    return id_;
}

auto qe::core::QuarkObject::get_transform() -> std::shared_ptr<qe::core::Transform>
{
    return transform_;
}

auto qe::core::QuarkObject::get_scene() -> Scene*
{
    return scene_;
}

void qe::core::QuarkObject::set_scene(Scene* scene)
{
    scene_ = scene;
}


