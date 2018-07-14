/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "VulkanObject.h"

#include <vector>

namespace qe {
    namespace core {
        class Texture;
    }

    namespace render {
        namespace vulkan {
            class VulkanTexture;
            class VulkanBuffer;

            class DLL_EXPORT VulkanDevice : public VulkanObject {
            public:
                vk::Instance instance_;
                /// Physical device representation */
                vk::PhysicalDevice physical_device_;
                /// Logical device representation (application's view of the device) */
                vk::Device logic_device_;

                vk::Queue queue_;

                vk::SurfaceKHR surface_;

                vk::SwapchainKHR swap_chain_;

                HWND window_;

                std::vector<vk::Image> swap_chain_images_;

                vk::Format swap_chain_image_format_;

                vk::Extent2D swap_chain_extent_;

                std::vector<vk::ImageView> swap_chain_image_views_;

                vk::RenderPass render_pass_;

                vk::Image frame_buffer_depth_image_;

                vk::DeviceMemory frame_buffer_depth_image_memory_;

                vk::ImageView frame_buffer_depth_image_view_;

                std::vector<vk::Framebuffer> swap_chain_frame_buffers_;

                /// Properties of the physical device including limits that the application can check against */
                vk::PhysicalDeviceProperties device_properties_;
                /// Features of the physical device that an application can use to check if a feature is supported */
                vk::PhysicalDeviceFeatures device_features_;
                /// Memory types and heaps of the physical device */
                vk::PhysicalDeviceMemoryProperties memory_properties_;
                /// Queue family properties of the physical device */
                std::vector<vk::QueueFamilyProperties> queue_family_properties_;
                /// List of extensions supported by the device */
                std::vector<std::string> supported_extensions_;

                std::vector<const char*> enabled_device_extensions_;

                vk::Format depth_format_;

                vk::Semaphore present_complete_semaphore_;

                vk::Semaphore render_complete_semaphore_;

                bool b_enable_validation_ = true;

                /// Default command pool for the graphics queue family index */
                vk::CommandPool command_pool_;

                /// Set to true when the debug marker extension is detected */
                bool enable_debug_markers_ = false;

                /// Contains queue family indices */
                struct
                {
                    uint32_t graphics;
                    uint32_t compute;
                    uint32_t transfer;
                } queue_family_indices_;

                struct SwapChainSupportDetails {
                    vk::SurfaceCapabilitiesKHR capabilities;
                    std::vector<vk::SurfaceFormatKHR> formats;
                    std::vector<vk::PresentModeKHR> presentModes;
                };

                // On desktop the LunarG loaders exposes a meta layer that contains all layers
                int32_t validation_layer_count_ = 1;

                const char *validation_layer_names_[1] = {
                    "VK_LAYER_LUNARG_standard_validation"
                };

            public:


                /// Default constructor
                ///
                /// @param physicalDevice Physical device that is to be used
                explicit VulkanDevice(HWND window, bool enable_validation = true, int gpu_index = 0);

                explicit VulkanDevice();

                /// Default destructor
                ///
                /// @note Frees the logical device
                ~VulkanDevice();

                void CreateInstance(vk::Instance& instance);

                /// <summary>
                /// Gets the physical device.
                /// </summary>
                /// <param name="gpuIndex">Index of the gpu.</param>
                void GetPhysicalDevice(vk::PhysicalDevice& physical_device, const int& gpuIndex = 0);


                /// Get the index of a memory type that has all the requested property bits set
                ///
                /// @param typeBits Bitmask with bits set for each memory type supported by the resource to request for (from vk::MemoryRequirements)
                /// @param properties Bitmask of properties for the memory type to request
                /// @param (Optional) memTypeFound Pointer to a bool that is set to true if a matching memory type has been found
                ///
                /// @return Index of the requested memory type
                ///
                /// @throw Throws an exception if memTypeFound is null and no memory type could be found that supports the requested properties
                uint32_t GetMemoryType(uint32_t typeBits, vk::MemoryPropertyFlags properties, VkBool32 *memTypeFound = nullptr);


                /// Get the index of a queue family that supports the requested queue flags
                ///
                /// @param queueFlags Queue flags to find a queue family index for
                ///
                /// @return Index of the queue family index that matches the flags
                ///
                /// @throw Throws an exception if no queue family index could be found that supports the requested flags
                uint32_t GetQueueFamilyIndex(vk::QueueFlags queueFlags);


                /// Create the logical device based on the assigned physical device, also gets default queue family indices
                ///
                /// @param enabledFeatures Can be used to enable certain features upon device creation
                /// @param useSwapChain Set to false for headless rendering to omit the swapchain device extensions
                /// @param requestedQueueTypes Bit flags specifying the queue types to be requested from the device
                ///
                /// @return vk::Result  of the device creation call
                vk::Result  CreateLogicalDevice(
                    vk::Device& logic_device, 
                    vk::PhysicalDeviceFeatures enabledFeatures,
                    std::vector<const char*> enabledExtensions,
                    bool useSwapChain = true,
                    vk::QueueFlags requestedQueueTypes = vk::QueueFlagBits::eGraphics | vk::QueueFlagBits::eCompute);


                /// Create a buffer on the device
                ///
                /// @param usageFlags Usage flag bitmask for the buffer (i.e. index, vertex, uniform buffer)
                /// @param memoryPropertyFlags Memory properties for this buffer (i.e. device local, host visible, coherent)
                /// @param size Size of the buffer in byes
                /// @param buffer Pointer to the buffer handle acquired by the function
                /// @param memory Pointer to the memory handle acquired by the function
                /// @param data Pointer to the data that should be copied to the buffer after creation (optional, if not set, no data is copied over)
                ///
                /// @return VK_SUCCESS if buffer handle and memory have been created and (optionally passed) data has been copied
                vk::Result  CreateBuffer(vk::BufferUsageFlags usageFlags, vk::MemoryPropertyFlags memoryPropertyFlags, vk::DeviceSize size, vk::Buffer *buffer, vk::DeviceMemory *memory, void *data = nullptr);


                /// Copy buffer data from src to dst using VkCmdCopyBuffer
                ///
                /// @param src Pointer to the source buffer to copy from
                /// @param dst Pointer to the destination buffer to copy tp
                /// @param queue Pointer
                /// @param copyRegion (Optional) Pointer to a copy region, if NULL, the whole buffer is copied
                ///
                /// @note Source and destionation pointers must have the approriate transfer usage flags set (TRANSFER_SRC / TRANSFER_DST)
                void CopyBuffer(qe::render::vulkan::VulkanBuffer *src, qe::render::vulkan::VulkanBuffer *dst, vk::Queue queue, vk::BufferCopy *copyRegion = nullptr);


                /// create host memory buffer then copy to device memory buffer.
                /// @param buffer is create buffer point
                /// @param data is buffer data
                void CreateH2DBuffer(qe::render::vulkan::VulkanBuffer *buffer, void *data, vk::BufferUsageFlagBits flag);;


                /// <summary>
                /// Creates the image.
                /// </summary>
                /// <param name="kTexture">The k texture.</param>
                /// <param name="format">The format.</param>
                /// <param name="imageUsage">The image usage.</param>
                /// <param name="imageLayout">The image layout.</param>
                /// <param name="forceLinear">if set to <c>true</c> [force linear].</param>
                /// <returns> return a vulkan texture smart pointer </returns>
                auto CreateImage(
                    core::Texture kTexture,
                    vk::Format format,
                    vk::ImageUsageFlagBits imageUsage = vk::ImageUsageFlagBits::eSampled,
                    vk::ImageLayout imageLayout = vk::ImageLayout::eShaderReadOnlyOptimal,
                    bool forceLinear = false) ->std::shared_ptr<VulkanTexture>;

                void createImage(
                    uint32_t width, 
                    uint32_t height, 
                    vk::Format format, 
                    vk::ImageTiling tiling, 
                    vk::ImageUsageFlagBits usage,
                    vk::MemoryPropertyFlagBits properties,
                    vk::Image& image,
                    vk::DeviceMemory& imageMemory);

                vk::ImageView CreateImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags);


                /// Create a command pool for allocation command buffers from
                ///
                /// @param queueFamilyIndex Family index of the queue to create the command pool for
                /// @param createFlags (Optional) Command pool creation flags (Defaults to VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
                ///
                /// @note Command buffers allocated from the created pool can only be submitted to a queue with the same family index
                ///
                /// @return A handle to the created command buffer
                vk::CommandPool CreateCommandPool(uint32_t queueFamilyIndex, vk::CommandPoolCreateFlags createFlags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer);


                /// Allocate a command buffer from the command pool
                ///
                /// @param level Level of the new command buffer (primary or secondary)
                /// @param (Optional) begin If true, recording on the new command buffer will be started (vkBeginCommandBuffer) (Defaults to false)
                ///
                /// @return A handle to the allocated command buffer
                vk::CommandBuffer CreateCommandBuffer(vk::CommandBufferLevel level, bool begin = false);


                /// Finish command buffer recording and submit it to a queue
                ///
                /// @param commandBuffer Command buffer to flush
                /// @param queue Queue to submit the command buffer to
                /// @param free (Optional) Free the command buffer once it has been submitted (Defaults to true)
                ///
                /// @note The queue that the command buffer is submitted to must be from the same family index as the pool it was allocated from
                /// @note Uses a fence to ensure command buffer has finished executing
                void FlushCommandBuffer(vk::CommandBuffer commandBuffer, vk::Queue queue, bool free = true);


                /// Check if an extension is supported by the (physical device)
                ///
                /// @param extension Name of the extension to check
                ///
                /// @return True if the extension is supported (present in the list read at device creation time)
                bool ExtensionSupported(std::string extension);

                vk::Bool32 GetSupportedDepthFormat(vk::PhysicalDevice physicalDevice, vk::Format *depthFormat);


            public:
                std::shared_ptr<VulkanTexture> Create2DImage(
                    core::Texture kTexture,
                    vk::Format format,
                    vk::ImageUsageFlagBits imageUsage,
                    vk::ImageLayout imageLayout,
                    bool forceLinear);

                std::shared_ptr<VulkanTexture> Create2DArrayImage(
                    core::Texture kTexture,
                    vk::Format format,
                    vk::ImageUsageFlagBits imageUsage,
                    vk::ImageLayout imageLayout,
                    bool forceLinear);

                std::shared_ptr<VulkanTexture> CreateCubeMapImage(
                    core::Texture kTexture,
                    vk::Format format,
                    vk::ImageUsageFlagBits imageUsage,
                    vk::ImageLayout imageLayout,
                    bool forceLinear);

                void CreateSurface(vk::SurfaceKHR& surface);

                auto QuerySwapChainSupport()->SwapChainSupportDetails;

                void CreateSwapChain();

                void CreateSwapChainImageView();

                auto VulkanDevice::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)->vk::SurfaceFormatKHR;

                auto VulkanDevice::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR> availablePresentModes)->vk::PresentModeKHR;

                auto ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities)->vk::Extent2D;

                void InitSwapChain();

                void CreateRenderPass();

                void CreateFrameBuffer();

            };
        }
    }

}