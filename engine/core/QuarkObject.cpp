#include "QuarkObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Component.h"
#include "Material.h"


qe::core::QuarkObject::QuarkObject()
    : id_(0)
    ,parent_(nullptr)
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

auto qe::core::QuarkObject::get_scene() -> Scene*
{
    return scene_;
}

void qe::core::QuarkObject::set_scene(Scene* scene)
{
    scene_ = scene;
}

qe::core::QuarkObject * qe::core::QuarkObject::get_parent()
{
    return parent_;
}

std::vector<std::shared_ptr<qe::core::QuarkObject>> qe::core::QuarkObject::get_childs()
{
    return childs_;
}

void qe::core::QuarkObject::add_child(std::shared_ptr<qe::core::QuarkObject> child)
{
    childs_.push_back(child);
    child->parent_ = this;

    child->set_scene(this->get_scene());
}

void qe::core::QuarkObject::detach_child(std::shared_ptr<qe::core::QuarkObject> child)
{
    auto result = std::find(childs_.begin(), childs_.end(), child);
    if (result != childs_.end()) {
        childs_.erase(result);
    }
}

