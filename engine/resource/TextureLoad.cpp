#include "TextureLoad.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <algorithm>

qe::resource::TextureLoad::TextureLoad()
{
}

qe::resource::TextureLoad::~TextureLoad()
{
}

std::shared_ptr<qe::core::Texture> qe::resource::TextureLoad::Load(const std::string & path)
{
    auto texture = std::make_shared<qe::core::Texture>();

    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    size_t imageSize = texWidth * texHeight * 4;
    uint32_t mipLevels = floor(log2(std::max(texWidth, texHeight))) + 1;
                
    texture->set_width(texWidth);
    texture->set_height(texHeight);
    texture->set_channel(texChannels);
    texture->set_size(imageSize);
    texture->set_mip_level(mipLevels);
    texture->set_data(pixels);

    return texture;
}
