/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
/// VIObject class is a base class for engine use vulkan api render

#pragma once

#define VK_USE_PLATFORM_WIN32_KHR 1

#include "RenderObject.h"
#include "vulkan/vulkan.hpp"

namespace qe {
    namespace render {
        namespace vulkan {
            class DLL_EXPORT VulkanObject : public core::RenderObject {
            public:
                explicit VulkanObject();
                ~VulkanObject();

            };
        }
    }
}


