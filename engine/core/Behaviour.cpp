#include "Behaviour.h"

qe::core::Behaviour::Behaviour()
{
}

qe::core::Behaviour::~Behaviour()
{
}

void qe::core::Behaviour::set_enable(bool enable)
{
    enable_ = enable;
}

bool qe::core::Behaviour::get_enable()
{
    return enable_;
}


