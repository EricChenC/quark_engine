#include "Component.h"
#include "QuarkObject.h"


qe::core::Component::Component()
    : quark_object_(nullptr)
{

}

qe::core::Component::~Component()
{
}

qe::core::QuarkObject* qe::core::Component::get_quark_object()
{
    return quark_object_;
}

void qe::core::Component::set_quark_object(QuarkObject* quark_object)
{
    quark_object_ = quark_object;
}
