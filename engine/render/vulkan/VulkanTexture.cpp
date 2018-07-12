#include "VulkanTexture.h"

qe::render::vulkan::VulkanTexture::VulkanTexture()
{
}

qe::render::vulkan::VulkanTexture::~VulkanTexture()
{
    if (!device) return;

    if(image)
        device.destroyImage(image);

    if (sampler)
        device.destroySampler(sampler);

    if (view)
        device.destroyImageView(view);

    if (mem)
        device.freeMemory(mem);
}



