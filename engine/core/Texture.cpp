#include "Texture.h"

qe::core::Texture::Texture()
{
}

qe::core::Texture::~Texture()
{
}

void qe::core::Texture::set_width(const uint32_t & width)
{
    width_ = width;
}

void qe::core::Texture::set_height(const uint32_t & height)
{
    height_ = height;
}

void qe::core::Texture::set_channel(const int & channel)
{
    channel_ = channel;
}

void qe::core::Texture::set_data(void * data)
{
    data_ = data;
}

void qe::core::Texture::set_mip_level(const uint32_t & mip_level)
{
    mip_levels_ = mip_level;
}

void qe::core::Texture::set_layer_count(const uint32_t & layer_count)
{
    layer_count_ = layer_count;
}

void qe::core::Texture::set_size(const size_t & size)
{
    size_ = size;
}

void qe::core::Texture::set_type(Type type)
{
    type_ = type;
}

uint32_t qe::core::Texture::get_width()
{
    return width_;
}

uint32_t qe::core::Texture::get_height()
{
    return height_;
}

int qe::core::Texture::get_channel()
{
    return channel_;
}

void * qe::core::Texture::get_data()
{
    return data_;
}

uint32_t qe::core::Texture::get_mip_level()
{
    return mip_levels_;
}

uint32_t qe::core::Texture::get_layer_count()
{
    return layer_count_;
}

size_t qe::core::Texture::get_size()
{
    return size_;
}

qe::core::Texture::Type qe::core::Texture::get_type()
{
    return type_;
}

