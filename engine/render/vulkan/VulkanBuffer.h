/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "VulkanObject.h"

namespace qe {
    namespace render {
        namespace vulkan {
            class VulkanBuffer : public VulkanObject {
            public:
                vk::Device device;
                vk::Buffer buffer;
                vk::DeviceMemory memory;
                vk::DescriptorBufferInfo descriptor;

                vk::DeviceSize size = 0;
                vk::DeviceSize alignment = 0;
                void* mapped = nullptr;


                /// Usage flags to be filled by external source at buffer creation (to query at some later point) */
                vk::BufferUsageFlags usageFlags;
                /// Memory propertys flags to be filled by external source at buffer creation (to query at some later point) */
                vk::MemoryPropertyFlagBits memoryPropertyFlags;

            public:
                explicit VulkanBuffer(vk::DeviceSize device_size);
                ~VulkanBuffer();


                /// Map a memory range of this buffer. If successful, mapped points to the specified buffer range.
                ///
                /// @param size (Optional) Size of the memory range to map. Pass VK_WHOLE_SIZE to map the complete buffer range.
                /// @param offset (Optional) Byte offset from beginning
                ///
                /// @return vk::Result  of the buffer mapping call
                vk::Result  map(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);


                /// Unmap a mapped memory range
                ///
                /// @note Does not return a result as vkUnmapMemory can't fail
                void unmap();


                /// Attach the allocated memory block to the buffer
                ///
                /// @param offset (Optional) Byte offset (from the beginning) for the memory region to bind
                ///
                /// @return vk::Result  of the bindBufferMemory call
                vk::Result  bind(vk::DeviceSize offset = 0);


                /// Setup the default descriptor for this buffer
                ///
                /// @param size (Optional) Size of the memory range of the descriptor
                /// @param offset (Optional) Byte offset from beginning
                ///
                void setupDescriptor(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);


                /// Copies the specified data to the mapped buffer
                ///
                /// @param data Pointer to the data to copy
                /// @param size Size of the data to copy in machine units
                void copyTo(void* data, vk::DeviceSize size);


                /// Flush a memory range of the buffer to make it visible to the device
                ///
                /// @note Only required for non-coherent memory
                ///
                /// @param size (Optional) Size of the memory range to flush. Pass VK_WHOLE_SIZE to flush the complete buffer range.
                /// @param offset (Optional) Byte offset from beginning
                ///
                /// @return vk::Result  of the flush call
                vk::Result  flush(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);



                /// Invalidate a memory range of the buffer to make it visible to the host
                ///
                /// @note Only required for non-coherent memory
                ///
                /// @param size (Optional) Size of the memory range to invalidate. Pass VK_WHOLE_SIZE to invalidate the complete buffer range.
                /// @param offset (Optional) Byte offset from beginning
                ///
                /// @return vk::Result  of the invalidate call
                vk::Result  invalidate(vk::DeviceSize size = VK_WHOLE_SIZE, vk::DeviceSize offset = 0);


                /// Release all Vulkan resources held by this buffer
                void destroy();

            };
        }
    }
}