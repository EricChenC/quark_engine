/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "VulkanObject.h"

#include <vulkan/vulkan.hpp>

namespace qe {
    namespace render {
        namespace vulkan {
            class DLL_EXPORT VulkanTexture : public VulkanObject {
            public:
                explicit VulkanTexture();
                ~VulkanTexture();

                vk::Device device;
                vk::Sampler sampler;

                vk::Image image;
                vk::ImageLayout imageLayout{ vk::ImageLayout::eUndefined };

                vk::MemoryAllocateInfo mem_alloc;
                vk::DeviceMemory mem;
                vk::ImageView view;

                uint32_t mip_level;
                uint32_t layer_count;

                vk::DescriptorImageInfo descriptor;

                int32_t tex_width{ 0 };
                int32_t tex_height{ 0 };

            };
        }
    }
}