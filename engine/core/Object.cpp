#include "Object.h"

qe::core::Object::Object()
{
}

qe::core::Object::~Object()
{
}

void qe::core::Object::set_name(const std::string & name)
{
    name_ = name;
}

void qe::core::Object::set_name(const char * name)
{
    name_ = name;
}

std::string qe::core::Object::get_name()
{
    return name_;
}

