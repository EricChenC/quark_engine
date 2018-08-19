/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "VulkanObject.h"

#include <string>
#include <iostream>

// Custom define for better code readability
#define VK_FLAGS_NONE 0
// Default fence timeout in nanoseconds
#define DEFAULT_FENCE_TIMEOUT 100000000000



namespace qe {
    namespace render {
        namespace vulkan {
            class DLL_EXPORT VulkanTools : public VulkanObject {
            public:
                explicit VulkanTools();
                ~VulkanTools();

                /// <summary>
                /// Errors the string.
                /// </summary>
                /// <param name="errorCode">The error code.</param>
                /// <returns></returns>
                /// @brief Returns an error code as a string */
                static std::string errorString(vk::Result  errorCode);

                /// <summary>
                /// Physicals the device type string.
                /// </summary>
                /// <param name="type">The type.</param>
                /// <returns></returns>
                /// @brief Returns the device type as a string */
                static std::string physicalDeviceTypeString(vk::PhysicalDeviceType type);

                /// <summary>
                /// Gets the supported depth format.
                /// </summary>
                /// <param name="physicalDevice">The physical device.</param>
                /// <param name="depthFormat">The depth format.</param>
                /// <returns></returns>
                /// Selected a suitable supported depth format starting with 32 bit down to 16 bit
                /// Returns false if none of the depth formats in the list is supported by the device
                static vk::Bool32 getSupportedDepthFormat(vk::PhysicalDevice physicalDevice, vk::Format *depthFormat);

                /// <summary>
                /// Sets the image layout.
                /// </summary>
                /// <param name="cmdbuffer">The cmdbuffer.</param>
                /// <param name="image">The image.</param>
                /// <param name="oldImageLayout">The old image layout.</param>
                /// <param name="newImageLayout">The new image layout.</param>
                /// <param name="subresourceRange">The subresource range.</param>
                /// <param name="srcStageMask">The source stage mask.</param>
                /// <param name="dstStageMask">The DST stage mask.</param>
                /// Put an image memory barrier for setting an image layout on the sub resource into the given command buffer
                static void setImageLayout(
                    vk::CommandBuffer cmdbuffer,
                    vk::Image image,
                    vk::ImageLayout oldImageLayout,
                    vk::ImageLayout newImageLayout,
                    vk::ImageSubresourceRange subresourceRange,
                    vk::PipelineStageFlagBits srcStageMask = vk::PipelineStageFlagBits::eAllCommands,
                    vk::PipelineStageFlagBits dstStageMask = vk::PipelineStageFlagBits::eAllCommands);

                /// <summary>
                /// Sets the image layout.
                /// </summary>
                /// <param name="cmdbuffer">The cmdbuffer.</param>
                /// <param name="image">The image.</param>
                /// <param name="aspectMask">The aspect mask.</param>
                /// <param name="oldImageLayout">The old image layout.</param>
                /// <param name="newImageLayout">The new image layout.</param>
                /// <param name="srcStageMask">The source stage mask.</param>
                /// <param name="dstStageMask">The DST stage mask.</param>
                /// Uses a fixed sub resource layout with first mip level and layer
                static void setImageLayout(
                    vk::CommandBuffer cmdbuffer,
                    vk::Image image,
                    vk::ImageAspectFlagBits aspectMask,
                    vk::ImageLayout oldImageLayout,
                    vk::ImageLayout newImageLayout,
                    vk::PipelineStageFlagBits srcStageMask = vk::PipelineStageFlagBits::eAllCommands,
                    vk::PipelineStageFlagBits dstStageMask = vk::PipelineStageFlagBits::eAllCommands);

                /// <summary>
                /// Inserts the image memory barrier.
                /// </summary>
                /// <param name="cmdbuffer">The cmdbuffer.</param>
                /// <param name="image">The image.</param>
                /// <param name="srcAccessMask">The source access mask.</param>
                /// <param name="dstAccessMask">The DST access mask.</param>
                /// <param name="oldImageLayout">The old image layout.</param>
                /// <param name="newImageLayout">The new image layout.</param>
                /// <param name="srcStageMask">The source stage mask.</param>
                /// <param name="dstStageMask">The DST stage mask.</param>
                /// <param name="subresourceRange">The subresource range.</param>
                /// @brief Inser an image memory barrier into the command buffer */
                static void insertImageMemoryBarrier(
                    vk::CommandBuffer cmdbuffer,
                    vk::Image image,
                    vk::AccessFlagBits srcAccessMask,
                    vk::AccessFlagBits dstAccessMask,
                    vk::ImageLayout oldImageLayout,
                    vk::ImageLayout newImageLayout,
                    vk::PipelineStageFlagBits srcStageMask,
                    vk::PipelineStageFlagBits dstStageMask,
                    vk::ImageSubresourceRange subresourceRange);

                /// <summary>
                /// Exits the fatal.
                /// </summary>
                /// <param name="message">The message.</param>
                /// <param name="caption">The caption.</param>
                /// Display error message and exit on fatal error
                static void exitFatal(std::string message, std::string caption);

                static std::string readTextFile(const char *fileName);

                static vk::ShaderModule loadShader(const char *fileName, vk::Device device);

                /// <summary>
                /// Loads the shader GLSL.
                /// </summary>
                /// <param name="fileName">Name of the file.</param>
                /// <param name="device">The device.</param>
                /// <param name="stage">The stage.</param>
                /// <returns></returns>
                /// Load a GLSL shader (text)
                /// Note: GLSL support requires vendor-specific extensions to be enabled and is not a core-feature of Vulkan
                static vk::ShaderModule loadShaderGLSL(const char *fileName, vk::Device device, vk::ShaderStageFlagBits stage);

                /// <summary>
                /// Files the exists.
                /// </summary>
                /// <param name="filename">The filename.</param>
                /// <returns></returns>
                /// @brief Checks if a file exists
                static bool fileExists(const std::string &filename);



            };
        }
    }
}


#define VK_CHECK_RESULT(f)                                                                                \
{                                                                                                        \
    vk::Result res = (f);                                                                                    \
    if (res != vk::Result::eSuccess)                                                                                \
    {                                                                                                    \
        std::cout << "Fatal : vk::Result  is \"" << qe::render::vulkan::VulkanTools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
        assert(res == vk::Result::eSuccess);                                                                        \
    }\
}