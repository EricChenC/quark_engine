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

qe::core::Color qe::core::Color::Black()
{
    return Color(0, 0, 0, 1);
}

qe::core::Color qe::core::Color::Blue()
{
    return Color(0, 0, 1, 1);
}

qe::core::Color qe::core::Color::Clear()
{
    return Color(0, 0, 0, 0);
}

qe::core::Color qe::core::Color::Cyan()
{
    return Color(0, 1, 1, 1);
}

qe::core::Color qe::core::Color::Gray()
{
    return Color(0.5, 0.5, 0.5, 1);
}

qe::core::Color qe::core::Color::Green()
{
    return Color(0, 1, 0, 1);
}

qe::core::Color qe::core::Color::Magenta()
{
    return Color(1, 0, 1, 1);
}

qe::core::Color qe::core::Color::Red()
{
    return Color(1, 0, 0, 1);
}

qe::core::Color qe::core::Color::White()
{
    return Color(1, 1, 1, 1);
}

qe::core::Color qe::core::Color::Yellow()
{
    return Color(1, 0.92, 0.016, 1);
}

glm::vec4 qe::core::Color::get_glm_color(const Color & color)
{
    return glm::vec4(color.r_, color.g_, color.b_, color.a_);
}