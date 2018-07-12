#include "VulkanBuffer.h"

qe::render::vulkan::VulkanBuffer::VulkanBuffer(vk::DeviceSize device_size)
{
    size = device_size;
}

qe::render::vulkan::VulkanBuffer::~VulkanBuffer()
{
    if (!device) return;

    if(buffer)
        device.destroyBuffer(buffer);

    if(memory)
        device.freeMemory(memory);
}

vk::Result  qe::render::vulkan::VulkanBuffer::map(vk::DeviceSize size, vk::DeviceSize offset)
{
    return device.mapMemory(memory, offset, size, vk::MemoryMapFlagBits(), &mapped);
}

void qe::render::vulkan::VulkanBuffer::unmap()
{
    if (mapped)
    {
        vkUnmapMemory(device, memory);
        mapped = nullptr;
    }
}

vk::Result  qe::render::vulkan::VulkanBuffer::bind(vk::DeviceSize offset)
{
    device.bindBufferMemory(buffer, memory, offset);

    return vk::Result::eSuccess;
}

void qe::render::vulkan::VulkanBuffer::setupDescriptor(vk::DeviceSize size, vk::DeviceSize offset)
{
    descriptor.offset = offset;
    descriptor.buffer = buffer;
    descriptor.range = size;
}

void qe::render::vulkan::VulkanBuffer::copyTo(void* data, vk::DeviceSize size)
{
    assert(mapped);
    memcpy(mapped, data, size);
}

vk::Result  qe::render::vulkan::VulkanBuffer::flush(vk::DeviceSize size, vk::DeviceSize offset)
{
    vk::MappedMemoryRange mappedRange;
    mappedRange.memory = memory;
    mappedRange.offset = offset;
    mappedRange.size = size;

    return device.flushMappedMemoryRanges(1, &mappedRange);
}

vk::Result  qe::render::vulkan::VulkanBuffer::invalidate(vk::DeviceSize size, vk::DeviceSize offset)
{
    vk::MappedMemoryRange mappedRange = {};
    mappedRange.memory = memory;
    mappedRange.offset = offset;
    mappedRange.size = size;

    return device.invalidateMappedMemoryRanges(1, &mappedRange);
}

void qe::render::vulkan::VulkanBuffer::destroy()
{
    if (buffer)
    {
        device.destroyBuffer(buffer, nullptr);
    }
    if (memory)
    {
        device.freeMemory(memory, nullptr);
    }
}