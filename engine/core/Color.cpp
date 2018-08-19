#include "Color.h"

qe::core::Color::Color()
{

}

qe::core::Color::Color(const float & r, const float & g, const float & b, const float & a)
    : r_(r),
    g_(g),
    b_(b),
    a_(a)
{

}

qe::core::Color::~Color()
{

}

glm::vec4 qe::core::Color::get_glm_color(const Color & color)
{
    return glm::vec4(color.r_, color.g_, color.b_, color.a_);
}
