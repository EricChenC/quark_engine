#include "QuarkObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Component.h"
#include "Material.h"


qe::core::QuarkObject::QuarkObject()
    : id_(0)
    ,parent_(nullptr)
{
    transform_ = AddComponent<qe::core::Transform>();
}

qe::core::QuarkObject::~QuarkObject()
{
}

inline void qe::core::QuarkObject::AddChild(const std::shared_ptr<qe::core::QuarkObject>& child)
{
    childs_.push_back(child);

    child->set_parent(this);
    child->set_scene(scene_);
}

inline void qe::core::QuarkObject::DetachChild(const std::shared_ptr<qe::core::QuarkObject>& child)
{
    auto result = std::find(childs_.begin(), childs_.end(), child);
    if (result != childs_.end()) {
        childs_.erase(result);
    }
}

