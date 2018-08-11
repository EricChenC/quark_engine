#include "Component.h"
#include "QuarkObject.h"


qe::core::Component::Component()
    : quark_object_(nullptr)
{

}

qe::core::Component::~Component()
{
}

std::shared_ptr<qe::core::QuarkObject> qe::core::Component::get_quark_object()
{
    return quark_object_;
}

void qe::core::Component::set_quark_object(std::shared_ptr<qe::core::QuarkObject> quark_object)
{
    quark_object_ = quark_object;
}
