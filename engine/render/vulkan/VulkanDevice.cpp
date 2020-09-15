#include "VulkanDevice.h"

#include "Texture.h"
#include "VulkanTexture.h"
#include "VulkanBuffer.h"
#include "VulkanTools.h"


qe::render::vulkan::VulkanDevice::VulkanDevice(HWND window, bool enable_validation, int gpu_index)
{
    b_enable_validation_ = enable_validation;
    window_ = window;

    CreateInstance(instance_);
    if (!instance_) {
        throw "can't create instance!";
        return;
    }

    CreateSurface(surface_);
    if (!surface_) {
        throw "can't create surface!";
        return;
    }

    GetPhysicalDevice(physical_device_ ,gpu_index);
    if (!physical_device_) {
        throw "can't find valid physical device!";
        return;
    }


    // Store Properties features, limits and properties of the physical device for later use
    // Device properties also contain limits and sparse properties
    physical_device_.getProperties(&device_properties_);

    // Features should be checked by the examples before using them
    physical_device_.getFeatures(&device_features_);
    // Memory properties are used regularly for creating all kinds of buffers
    physical_device_.getMemoryProperties(&memory_properties_);
    // Queue family properties, used for setting up requested queues upon device creation
    uint32_t queueFamilyCount;
    physical_device_.getQueueFamilyProperties(&queueFamilyCount, nullptr);
    assert(queueFamilyCount > 0);
    queue_family_properties_.resize(queueFamilyCount);
    physical_device_.getQueueFamilyProperties(&queueFamilyCount, queue_family_properties_.data());

    device_features_.sampleRateShading = true;

    msaa_samples_ = GetMSAASample(device_properties_);

    // Get list of supported extensions
    uint32_t extCount = 0;
    VK_CHECK_RESULT(physical_device_.enumerateDeviceExtensionProperties(nullptr, &extCount, nullptr));
    if (extCount > 0)
    {
        std::vector<vk::ExtensionProperties> extensions(extCount);

        if (physical_device_.enumerateDeviceExtensionProperties(nullptr, &extCount, &extensions.front()) == vk::Result::eSuccess)
        {
            for (auto ext : extensions)
            {
                supported_extensions_.push_back(ext.extensionName);
            }
        }
    }

    VK_CHECK_RESULT(CreateLogicalDevice(logic_device_ ,device_features_, enabled_device_extensions_));
    if (!logic_device_) {
        throw "can't create logic device!";
        return;
    }


    // Get a graphics queue from the device
    logic_device_.getQueue(queue_family_indices_.graphics, 0, &queue_);

    // Find a suitable depth format
    vk::Bool32 validDepthFormat = GetSupportedDepthFormat(physical_device_, &depth_format_);
    assert(validDepthFormat);

    //swapChain.connect(instance, physicalDevice, device);

    // Create synchronization objects
    vk::SemaphoreCreateInfo semaphoreCreateInfo;
    // Create a semaphore used to synchronize image presentation
    // Ensures that the image is displayed before we start submitting new commands to the queu
    logic_device_.createSemaphore(&semaphoreCreateInfo, nullptr, &present_complete_semaphore_);
    // Create a semaphore used to synchronize command submission
    // Ensures that the image is not presented until all commands have been sumbitted and executed
    logic_device_.createSemaphore(&semaphoreCreateInfo, nullptr, &render_complete_semaphore_);

    InitSwapChain();

    CreateRenderPass();

    CreateFrameBuffer();

}

qe::render::vulkan::VulkanDevice::VulkanDevice()
{
    std::cout << "one" << std::endl;


}

qe::render::vulkan::VulkanDevice::~VulkanDevice()
{   
    if (present_complete_semaphore_) {
        logic_device_.destroySemaphore(present_complete_semaphore_);
    }

    if (render_complete_semaphore_) {
        logic_device_.destroySemaphore(render_complete_semaphore_);
    }

    if (command_pool_) {
        logic_device_.destroyCommandPool(command_pool_);
    }

    if (swap_chain_) {
        logic_device_.destroySwapchainKHR(swap_chain_);
    }

    if (color_image_) {
        logic_device_.destroyImage(color_image_);
    }

    if (color_image_memory_) {
        logic_device_.freeMemory(color_image_memory_);
    }

    if (color_image_view_) {
        logic_device_.destroyImageView(color_image_view_);
    }

    if (frame_buffer_depth_image_) {
        logic_device_.destroyImage(frame_buffer_depth_image_);
    }

    if (frame_buffer_depth_image_memory_) {
        logic_device_.freeMemory(frame_buffer_depth_image_memory_);
    }

    if (frame_buffer_depth_image_view_) {
        logic_device_.destroyImageView(frame_buffer_depth_image_view_);
    }

    for (int i = 0; i < swap_chain_images_.size(); i++) {
        //logic_device_.destroyImage(swap_chain_images_[i]);
        logic_device_.destroyImageView(swap_chain_image_views_[i]);
        logic_device_.destroyFramebuffer(swap_chain_frame_buffers_[i]);
    }

    if (render_pass_) {
        logic_device_.destroyRenderPass(render_pass_);
    }

    if (surface_) {
        instance_.destroySurfaceKHR(surface_);
    }

    if (logic_device_) {
        logic_device_.destroy();
    }

    if (instance_) {
        instance_.destroy();
    }
}

void qe::render::vulkan::VulkanDevice::CreateInstance(vk::Instance& instance)
{
    auto name = "quark engine";

    vk::ApplicationInfo appInfo;
    appInfo.pApplicationName = name;
    appInfo.pEngineName = name;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    std::vector<const char*> instanceExtensions = { VK_KHR_SURFACE_EXTENSION_NAME };

    // Enable surface extensions depending on os
    instanceExtensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);

    vk::InstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    if (instanceExtensions.size() > 0)
    {
        if (b_enable_validation_)
        {
            instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }
        instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
        instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
    }
    if (b_enable_validation_)
    {
        instanceCreateInfo.enabledLayerCount = validation_layer_count_;
        instanceCreateInfo.ppEnabledLayerNames = validation_layer_names_;
    }

    VK_CHECK_RESULT(vk::createInstance(&instanceCreateInfo, nullptr, &instance));
}

void qe::render::vulkan::VulkanDevice::GetPhysicalDevice(vk::PhysicalDevice& physical_device, const int& gpuIndex)
{
    // Physical device
    uint32_t gpuCount = 0;
    // Get number of available physical devices
    VK_CHECK_RESULT(instance_.enumeratePhysicalDevices(&gpuCount, nullptr));
    assert(gpuCount > 0);
    // Enumerate devices
    std::vector<vk::PhysicalDevice> physicalDevices(gpuCount);
    VK_CHECK_RESULT(instance_.enumeratePhysicalDevices(&gpuCount, physicalDevices.data()));

    // we just simple use first gpu.
    if(physicalDevices.size() - 1 >= gpuIndex)
        physical_device = physicalDevices[gpuIndex];
}

uint32_t qe::render::vulkan::VulkanDevice::GetMemoryType(uint32_t typeBits, vk::MemoryPropertyFlags properties, VkBool32 *memTypeFound)
{
    for (uint32_t i = 0; i < memory_properties_.memoryTypeCount; i++)
    {
        if ((typeBits & 1) == 1)
        {
            if ((memory_properties_.memoryTypes[i].propertyFlags & properties) == properties)
            {
                if (memTypeFound)
                {
                    *memTypeFound = true;
                }
                return i;
            }
        }
        typeBits >>= 1;
    }

    if (memTypeFound)
    {
        *memTypeFound = false;
        return 0;
    }
    else
    {
        throw std::runtime_error("Could not find a matching memory type");
    }
}

uint32_t qe::render::vulkan::VulkanDevice::GetQueueFamilyIndex(vk::QueueFlags queueFlags)
{
    // Dedicated queue for compute
    // Try to find a queue family index that supports compute but not graphics
    if (queueFlags)
    {
        for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties_.size()); i++)
        {
            if ((queue_family_properties_[i].queueFlags & queueFlags))
            {
                vk::Bool32 support = false;
                physical_device_.getSurfaceSupportKHR(i, surface_, &support);

                if (support) {
                    return i;
                }
            }
        }
    }

    // Dedicated queue for transfer
    // Try to find a queue family index that supports transfer but not graphics and compute
    if (queueFlags & vk::QueueFlagBits::eTransfer)
    {
        for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties_.size()); i++)
        {
            if ((queue_family_properties_[i].queueFlags & queueFlags)
                && !(queue_family_properties_[i].queueFlags & vk::QueueFlagBits::eGraphics)
                && !(queue_family_properties_[i].queueFlags & vk::QueueFlagBits::eCompute))
            {
                return i;
                break;
            }
        }
    }

    // For other queue types or if no separate compute queue is present, return the first one to support the requested flags
    for (uint32_t i = 0; i < static_cast<uint32_t>(queue_family_properties_.size()); i++)
    {
        if (queue_family_properties_[i].queueFlags & queueFlags)
        {
            return i;
            break;
        }
    }

    throw std::runtime_error("Could not find a matching queue family index");
}

vk::Result  qe::render::vulkan::VulkanDevice::CreateLogicalDevice(
    vk::Device& logic_device,
    vk::PhysicalDeviceFeatures enabledFeatures,
    std::vector<const char*> enabledExtensions,
    bool useSwapChain,
    vk::QueueFlags requestedQueueTypes)
{

    // Desired queues need to be requested upon logical device creation
    // Due to differing queue family configurations of Vulkan implementations this can be a bit tricky, especially if the application
    // requests different queue types
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos{};

    // Get queue family indices for the requested queue family types
    // Note that the indices may overlap depending on the implementation

    const float defaultQueuePriority(0.0f);

    // Graphics queue
    if (requestedQueueTypes & vk::QueueFlagBits::eGraphics)
    {
        queue_family_indices_.graphics = GetQueueFamilyIndex(vk::QueueFlagBits::eGraphics);
        vk::DeviceQueueCreateInfo queueInfo{};
        queueInfo.queueFamilyIndex = queue_family_indices_.graphics;
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &defaultQueuePriority;
        queueCreateInfos.push_back(queueInfo);
    }
    else
    {
        queue_family_indices_.graphics = VK_NULL_HANDLE;
    }

    // Dedicated compute queue
    if (requestedQueueTypes & vk::QueueFlagBits::eCompute)
    {
        queue_family_indices_.compute = GetQueueFamilyIndex(vk::QueueFlagBits::eCompute);
        if (queue_family_indices_.compute != queue_family_indices_.graphics)
        {
            // If compute family index differs, we need an additional queue create info for the compute queue
            vk::DeviceQueueCreateInfo queueInfo{};
            queueInfo.queueFamilyIndex = queue_family_indices_.compute;
            queueInfo.queueCount = 1;
            queueInfo.pQueuePriorities = &defaultQueuePriority;
            queueCreateInfos.push_back(queueInfo);
        }
    }
    else
    {
        // Else we use the same queue
        queue_family_indices_.compute = queue_family_indices_.graphics;
    }

    // Dedicated transfer queue
    if (requestedQueueTypes & vk::QueueFlagBits::eTransfer)
    {
        queue_family_indices_.transfer = GetQueueFamilyIndex(vk::QueueFlagBits::eTransfer);
        if ((queue_family_indices_.transfer != queue_family_indices_.graphics)
            && (queue_family_indices_.transfer != queue_family_indices_.compute))
        {
            // If compute family index differs, we need an additional queue create info for the compute queue
            vk::DeviceQueueCreateInfo queueInfo{};
            queueInfo.queueFamilyIndex = queue_family_indices_.transfer;
            queueInfo.queueCount = 1;
            queueInfo.pQueuePriorities = &defaultQueuePriority;
            queueCreateInfos.push_back(queueInfo);
        }
    }
    else
    {
        // Else we use the same queue
        queue_family_indices_.transfer = queue_family_indices_.graphics;
    }

    // Create the logical device representation
    std::vector<const char*> deviceExtensions(enabledExtensions);
    if (useSwapChain)
    {
        // If the device will be used for presenting to a display via a swapchain we need to request the swapchain extension
        deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
    }


    vk::DeviceCreateInfo deviceCreateInfo = {};
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

    // Enable the debug marker extension if it is present (likely meaning a debugging tool is present)
    if (ExtensionSupported(VK_EXT_DEBUG_MARKER_EXTENSION_NAME))
    {
        deviceExtensions.push_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
        enable_debug_markers_ = true;
    }

    if (deviceExtensions.size() > 0)
    {
        deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
        deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
    }

    vk::Result  result = physical_device_.createDevice(&deviceCreateInfo, nullptr, &logic_device);

    if (result == vk::Result::eSuccess)
    {
        // Create a default command pool for graphics command buffers
        command_pool_ = CreateCommandPool(queue_family_indices_.graphics);
    }

    return result;
}

vk::Result qe::render::vulkan::VulkanDevice::CreateBuffer(vk::BufferUsageFlags usageFlags, vk::MemoryPropertyFlags memoryPropertyFlags, vk::DeviceSize size, vk::Buffer *buffer, vk::DeviceMemory *memory, void *data)
{
    // Create the buffer handle
    vk::BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.setUsage(usageFlags);
    bufferCreateInfo.setSize(size);
    bufferCreateInfo.setSharingMode(vk::SharingMode::eExclusive);
    VK_CHECK_RESULT(logic_device_.createBuffer(&bufferCreateInfo, nullptr, buffer));

    // Create the memory backing up the buffer handle
    vk::MemoryRequirements memReqs;
    vk::MemoryAllocateInfo memAlloc;
    logic_device_.getBufferMemoryRequirements(*buffer, &memReqs);
    memAlloc.allocationSize = memReqs.size;
    // Find a memory type index that fits the properties of the buffer
    memAlloc.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
    VK_CHECK_RESULT(logic_device_.allocateMemory(&memAlloc, nullptr, memory));

    // If a pointer to the buffer data has been passed, map the buffer and copy over the data
    if (data != nullptr)
    {
        void *mapped;
        VK_CHECK_RESULT(logic_device_.mapMemory(*memory, 0, size, vk::MemoryMapFlagBits(), &mapped));
        memcpy(mapped, data, size);
        // If host coherency hasn't been requested, do a manual flush to make writes visible
        if (!(memoryPropertyFlags & vk::MemoryPropertyFlagBits::eHostCoherent))
        {
            vk::MappedMemoryRange mappedRange;
            mappedRange.memory = *memory;
            mappedRange.offset = 0;
            mappedRange.size = size;
            logic_device_.flushMappedMemoryRanges(mappedRange);
        }

        logic_device_.unmapMemory(*memory);
    }

    // Attach the memory to the buffer object
    logic_device_.bindBufferMemory(*buffer, *memory, 0);

    return vk::Result::eSuccess;
}

void qe::render::vulkan::VulkanDevice::CopyBuffer(render::vulkan::VulkanBuffer *src, render::vulkan::VulkanBuffer *dst, vk::Queue queue, vk::BufferCopy *copyRegion)
{
    assert(dst->size <= src->size);
    assert(src->buffer && src->buffer);
    vk::CommandBuffer copyCmd = CreateCommandBuffer(vk::CommandBufferLevel::ePrimary, true);
    vk::BufferCopy bufferCopy{};
    if (copyRegion == nullptr)
    {
        bufferCopy.size = src->size;
    }
    else
    {
        bufferCopy = *copyRegion;
    }

    copyCmd.copyBuffer(src->buffer, dst->buffer, 1, &bufferCopy);

    FlushCommandBuffer(copyCmd, queue);
}

void qe::render::vulkan::VulkanDevice::CreateH2DBuffer(render::vulkan::VulkanBuffer * buffer, void * data, vk::BufferUsageFlagBits flag)
{
    render::vulkan::VulkanBuffer stagingBuffer(buffer->size);

    CreateBuffer(
        vk::BufferUsageFlagBits::eTransferSrc | flag,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
        buffer->size,
        &(stagingBuffer.buffer),
        &(stagingBuffer.memory),
        data);

    CreateBuffer(
        vk::BufferUsageFlagBits::eTransferDst | flag,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        buffer->size,
        &(buffer->buffer),
        &(buffer->memory));

    // set vulkan buffer device for auto release 
    stagingBuffer.device = buffer->device = logic_device_;

    CopyBuffer(&stagingBuffer, buffer, queue_);

}

auto qe::render::vulkan::VulkanDevice::CreateImage(
    core::Texture kTexture, 
    vk::Format format, 
    vk::ImageUsageFlagBits imageUsage, 
    vk::ImageLayout imageLayout, 
    bool forceLinear) -> std::shared_ptr<qe::render::vulkan::VulkanTexture>
{
    switch (kTexture.get_type())
    {
    case qe::core::Texture::Type::T2D:
        return Create2DImage(kTexture, format, msaa_samples_, imageUsage, imageLayout, forceLinear);
        break;
    case qe::core::Texture::Type::T2DARRAY:
        return Create2DArrayImage(kTexture, format, imageUsage, imageLayout, forceLinear);
        break;
    case qe::core::Texture::Type::TCUBEMAP:
        return CreateCubeMapImage(kTexture, format, imageUsage, imageLayout, forceLinear);
        break;
    default:
        return std::shared_ptr<qe::render::vulkan::VulkanTexture>();
        break;
    }
}

void qe::render::vulkan::VulkanDevice::createImage(
    uint32_t width, 
    uint32_t height, 
    vk::Format format, 
    vk::ImageTiling tiling, 
    vk::ImageUsageFlagBits usage, 
    vk::MemoryPropertyFlagBits properties, 
    vk::Image & image, 
    vk::DeviceMemory & imageMemory)
{
    vk::ImageCreateInfo imageInfo = {};
    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = width;
    imageInfo.extent.height = height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = format;
    imageInfo.tiling = tiling;
    imageInfo.initialLayout = vk::ImageLayout::ePreinitialized;
    imageInfo.usage = usage;
    imageInfo.samples = msaa_samples_;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;

    VK_CHECK_RESULT(logic_device_.createImage(&imageInfo, nullptr, &image));

    vk::MemoryRequirements memRequirements;
    logic_device_.getImageMemoryRequirements(image, &memRequirements);

    vk::MemoryAllocateInfo allocInfo = {};
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = GetMemoryType(memRequirements.memoryTypeBits, properties);

    VK_CHECK_RESULT(logic_device_.allocateMemory(&allocInfo, nullptr, &imageMemory));

    logic_device_.bindImageMemory(image, imageMemory, 0);

}

vk::ImageView qe::render::vulkan::VulkanDevice::CreateImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags)
{
    vk::ImageViewCreateInfo viewInfo = {};
    viewInfo.image = image;
    viewInfo.viewType = vk::ImageViewType::e2D;
    viewInfo.format = format;
    viewInfo.subresourceRange.aspectMask = aspectFlags;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    vk::ImageView imageView;

    VK_CHECK_RESULT(logic_device_.createImageView(&viewInfo, nullptr, &imageView));

    return imageView;
}

vk::CommandPool qe::render::vulkan::VulkanDevice::CreateCommandPool(uint32_t queueFamilyIndex, vk::CommandPoolCreateFlags createFlags)
{
    vk::CommandPoolCreateInfo cmdPoolInfo;
    cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
    cmdPoolInfo.flags = createFlags;
    vk::CommandPool cmdPool;
    logic_device_.createCommandPool(&cmdPoolInfo, nullptr, &cmdPool);
    return cmdPool;
}

vk::CommandBuffer qe::render::vulkan::VulkanDevice::CreateCommandBuffer(vk::CommandBufferLevel level, bool begin)
{
    vk::CommandBufferAllocateInfo cmdBufAllocateInfo;
    cmdBufAllocateInfo.setCommandPool(command_pool_);
    cmdBufAllocateInfo.setLevel(level);
    cmdBufAllocateInfo.setCommandBufferCount(1);

    vk::CommandBuffer cmdBuffer;
    VK_CHECK_RESULT(logic_device_.allocateCommandBuffers(&cmdBufAllocateInfo, &cmdBuffer));

    // If requested, also start recording for the new command buffer
    if (begin)
    {
        vk::CommandBufferBeginInfo cmdBufInfo;
        VK_CHECK_RESULT(cmdBuffer.begin(&cmdBufInfo));
    }

    return cmdBuffer;
}

void qe::render::vulkan::VulkanDevice::FlushCommandBuffer(vk::CommandBuffer commandBuffer, vk::Queue queue, bool free)
{
    if (!commandBuffer)
    {
        return;
    }

    commandBuffer.end();

    vk::SubmitInfo submitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    // Create fence to ensure that the command buffer has finished executing
    vk::FenceCreateInfo fenceInfo;
    vk::Fence fence;
    VK_CHECK_RESULT(logic_device_.createFence(&fenceInfo, nullptr, &fence));

    // Submit to the queue
    VK_CHECK_RESULT(queue.submit(1, &submitInfo, fence));
    // Wait for the fence to signal that command buffer has finished executing
    VK_CHECK_RESULT(logic_device_.waitForFences(1, &fence, VK_TRUE, DEFAULT_FENCE_TIMEOUT));

    logic_device_.destroyFence(fence, nullptr);

    if (free)
    {
        logic_device_.freeCommandBuffers(command_pool_, 1, &commandBuffer);
    }
}

bool qe::render::vulkan::VulkanDevice::ExtensionSupported(std::string extension)
{
    return (std::find(supported_extensions_.begin(), supported_extensions_.end(), extension) != supported_extensions_.end());
}

vk::Bool32 qe::render::vulkan::VulkanDevice::GetSupportedDepthFormat(vk::PhysicalDevice physicalDevice, vk::Format *depthFormat)
{
    // Since all depth formats may be optional, we need to find a suitable depth format to use
    // Start with the highest precision packed format
    std::vector<vk::Format> depthFormats = {
        vk::Format::eD32SfloatS8Uint,
        vk::Format::eD32Sfloat,
        vk::Format::eD24UnormS8Uint,
        vk::Format::eD16UnormS8Uint,
        vk::Format::eD16Unorm
    };

    for (auto& format : depthFormats)
    {
        vk::FormatProperties formatProps;
        physicalDevice.getFormatProperties(format, &formatProps);
        // Format must support depth stencil attachment for optimal tiling
        if (formatProps.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
        {
            *depthFormat = format;
            return true;
        }
    }

    return false;
}

std::shared_ptr<qe::render::vulkan::VulkanTexture> qe::render::vulkan::VulkanDevice::Create2DImage(core::Texture kTexture, vk::Format format, vk::SampleCountFlagBits numSamples, vk::ImageUsageFlagBits imageUsage, vk::ImageLayout imageLayout, bool forceLinear)
{
    auto vi_texture = std::make_shared<qe::render::vulkan::VulkanTexture>();

    vi_texture->tex_width = kTexture.get_width();
    vi_texture->tex_height = kTexture.get_height();
    vi_texture->mip_level = kTexture.get_mip_level();

    // Get device properites for the requested texture format
    vk::FormatProperties formatProperties;
    physical_device_.getFormatProperties(format, &formatProperties);

    // Only use linear tiling if requested (and supported by the device)
    // Support for linear tiling is mostly limited, so prefer to use
    // optimal tiling instead
    // On most implementations linear tiling will only support a very
    // limited amount of formats and features (mip maps, cubemaps, arrays, etc.)
    vk::Bool32 useStaging = !forceLinear;

    vk::MemoryAllocateInfo memAllocInfo;
    vk::MemoryRequirements memReqs;

    // Use a separate command buffer for texture loading
    vk::CommandBuffer copyCmd = CreateCommandBuffer(vk::CommandBufferLevel::ePrimary, true);

    if (useStaging)
    {
        // Create a host-visible staging buffer that contains the raw image data
        vk::Buffer stagingBuffer;
        vk::DeviceMemory stagingMemory;

        vk::BufferCreateInfo bufferCreateInfo;
        bufferCreateInfo.size = kTexture.get_size();
        // This buffer is used as a transfer source for the buffer copy
        bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
        bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

        VK_CHECK_RESULT(logic_device_.createBuffer(&bufferCreateInfo, nullptr, &stagingBuffer));

        // Get memory requirements for the staging buffer (alignment, memory type bits)
        logic_device_.getBufferMemoryRequirements(stagingBuffer, &memReqs);

        memAllocInfo.allocationSize = memReqs.size;
        // Get memory type index for a host visible buffer
        memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);

        VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &stagingMemory));
        logic_device_.bindBufferMemory(stagingBuffer, stagingMemory, 0);

        // Copy texture data into staging buffer
        void *data;
        VK_CHECK_RESULT(logic_device_.mapMemory(stagingMemory, 0, memReqs.size, vk::MemoryMapFlagBits(), &data));
        memcpy(data, kTexture.get_data(), kTexture.get_size());
        logic_device_.unmapMemory(stagingMemory);

        // Setup buffer copy regions for each mip level
        std::vector<vk::BufferImageCopy> bufferCopyRegions;
        uint32_t offset = 0;

        for (uint32_t i = 0; i < vi_texture->mip_level; i++)
        {
            vk::BufferImageCopy bufferCopyRegion;
            bufferCopyRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
            bufferCopyRegion.imageSubresource.mipLevel = i;
            bufferCopyRegion.imageSubresource.baseArrayLayer = 0;
            bufferCopyRegion.imageSubresource.layerCount = 1;
            bufferCopyRegion.imageExtent.width = static_cast<uint32_t>(kTexture.get_width());
            bufferCopyRegion.imageExtent.height = static_cast<uint32_t>(kTexture.get_height());
            bufferCopyRegion.imageExtent.depth = 1;
            bufferCopyRegion.bufferOffset = offset;

            bufferCopyRegions.push_back(bufferCopyRegion);

            offset += static_cast<uint32_t>(kTexture.get_size());
        }

        // Create optimal tiled target image
        vk::ImageCreateInfo imageCreateInfo;
        imageCreateInfo.imageType = vk::ImageType::e2D;
        imageCreateInfo.format = format;
        imageCreateInfo.mipLevels = vi_texture->mip_level;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.samples = numSamples;
        imageCreateInfo.tiling = vk::ImageTiling::eOptimal;
        imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;
        imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
        imageCreateInfo.extent = { kTexture.get_width(), kTexture.get_height(), 1 };
        imageCreateInfo.usage = imageUsage;
        // Ensure that the TRANSFER_DST bit is set for staging
        if (!(imageCreateInfo.usage & vk::ImageUsageFlagBits::eTransferDst))
        {
            imageCreateInfo.usage |= vk::ImageUsageFlagBits::eTransferDst;
        }

        VK_CHECK_RESULT(logic_device_.createImage(&imageCreateInfo, nullptr, &vi_texture->image));

        logic_device_.getImageMemoryRequirements(vi_texture->image, &memReqs);

        memAllocInfo.allocationSize = memReqs.size;

        memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

        VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &vi_texture->mem));
        logic_device_.bindImageMemory(vi_texture->image, vi_texture->mem, 0);

        vk::ImageSubresourceRange subresourceRange;
        subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        subresourceRange.baseMipLevel = 0;
        subresourceRange.levelCount = vi_texture->mip_level;
        subresourceRange.layerCount = 1;

        // Image barrier for optimal image (target)
        // Optimal image will be used as destination for the copy

        render::vulkan::VulkanTools::setImageLayout(
            copyCmd,
            vi_texture->image,
            vk::ImageLayout::eUndefined,
            vk::ImageLayout::eTransferDstOptimal,
            subresourceRange
        );

        copyCmd.copyBufferToImage(
            stagingBuffer,
            vi_texture->image,
            vk::ImageLayout::eTransferDstOptimal,
            static_cast<uint32_t>(bufferCopyRegions.size()),
            bufferCopyRegions.data()
        );

        // Change texture image layout to shader read after all mip levels have been copied
        vi_texture->imageLayout = imageLayout;
        render::vulkan::VulkanTools::setImageLayout(
            copyCmd,
            vi_texture->image,
            vk::ImageLayout::eTransferDstOptimal,
            imageLayout,
            subresourceRange);

        FlushCommandBuffer(copyCmd, queue_);

        // Clean up staging resources
        logic_device_.freeMemory(stagingMemory);
        logic_device_.destroyBuffer(stagingBuffer);
    }
    else
    {
        // Prefer using optimal tiling, as linear tiling 
        // may support only a small set of features 
        // depending on implementation (e.g. no mip maps, only one layer, etc.)

        // Check if this support is supported for linear tiling
        assert(formatProperties.linearTilingFeatures & vk::FormatFeatureFlagBits::eSampledImage);

        vk::Image mappableImage;
        vk::DeviceMemory mappableMemory;

        vk::ImageCreateInfo imageCreateInfo;
        imageCreateInfo.imageType = vk::ImageType::e2D;
        imageCreateInfo.format = format;
        imageCreateInfo.extent = { kTexture.get_width(), kTexture.get_height(), 1 };
        imageCreateInfo.mipLevels = 1;
        imageCreateInfo.arrayLayers = 1;
        imageCreateInfo.samples = numSamples;
        imageCreateInfo.tiling = vk::ImageTiling::eLinear;
        imageCreateInfo.usage = imageUsage;
        imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;
        imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;

        // Load mip map level 0 to linear tiling image
        VK_CHECK_RESULT(logic_device_.createImage(&imageCreateInfo, nullptr, &mappableImage));

        // Get memory requirements for this image 
        // like size and alignment
        logic_device_.getImageMemoryRequirements(mappableImage, &memReqs);
        // Set memory allocation size to required memory size
        memAllocInfo.allocationSize = memReqs.size;

        // Get memory type that can be mapped to host memory
        memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);

        // Allocate host memory
        VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &mappableMemory));

        // Bind allocated image for use
        logic_device_.bindImageMemory(mappableImage, mappableMemory, 0);

        // Get sub resource layout
        // Mip map count, array layer, etc.
        vk::ImageSubresource subRes;
        subRes.aspectMask = vk::ImageAspectFlagBits::eColor;
        subRes.mipLevel = 0;

        vk::SubresourceLayout subResLayout;
        void *data;

        // Get sub resources layout 
        // Includes row pitch, size offsets, etc.
        logic_device_.getImageSubresourceLayout(mappableImage, &subRes, &subResLayout);

        // Map image memory
        VK_CHECK_RESULT(logic_device_.mapMemory(mappableMemory, 0, memReqs.size, vk::MemoryMapFlagBits(), &data));

        // Copy image data into memory
        memcpy(data, kTexture.get_data(), kTexture.get_size());

        logic_device_.unmapMemory(mappableMemory);

        // Linear tiled images don't need to be staged
        // and can be directly used as textures
        vi_texture->image = mappableImage;
        vi_texture->mem = mappableMemory;
        imageLayout = imageLayout;

        // Setup image memory barrier
        render::vulkan::VulkanTools::setImageLayout(
            copyCmd,
            vi_texture->image,
            vk::ImageAspectFlagBits::eColor,
            vk::ImageLayout::eUndefined,
            imageLayout);

        FlushCommandBuffer(copyCmd, queue_);
    }

    // Create a defaultsampler
    vk::SamplerCreateInfo samplerCreateInfo;
    samplerCreateInfo.magFilter = vk::Filter::eLinear;
    samplerCreateInfo.minFilter = vk::Filter::eLinear;
    samplerCreateInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
    samplerCreateInfo.addressModeU = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.addressModeV = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.addressModeW = vk::SamplerAddressMode::eRepeat;
    samplerCreateInfo.mipLodBias = 0.0f;
    samplerCreateInfo.compareOp = vk::CompareOp::eNever;
    samplerCreateInfo.minLod = 0.0f;
    // Max level-of-detail should match mip level count
    samplerCreateInfo.maxLod = (useStaging) ? (float)kTexture.get_mip_level() : 0.0f;
    // Enable anisotropic filtering
    samplerCreateInfo.maxAnisotropy = 8;
    samplerCreateInfo.anisotropyEnable = VK_TRUE;
    samplerCreateInfo.borderColor = vk::BorderColor::eFloatOpaqueWhite;

    VK_CHECK_RESULT(logic_device_.createSampler(&samplerCreateInfo, nullptr, &vi_texture->sampler));

    // Create image view
    // Textures are not directly accessed by the shaders and
    // are abstracted by image views containing additional
    // information and sub resource ranges
    vk::ImageViewCreateInfo viewCreateInfo;
    viewCreateInfo.viewType = vk::ImageViewType::e2D;
    viewCreateInfo.format = format;
    viewCreateInfo.components = { vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA };

    viewCreateInfo.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };
    // Linear tiling usually won't support mip maps
    // Only set mip map count if optimal tiling is used
    viewCreateInfo.subresourceRange.levelCount = (useStaging) ? kTexture.get_mip_level() : 1;
    viewCreateInfo.image = vi_texture->image;

    VK_CHECK_RESULT(logic_device_.createImageView(&viewCreateInfo, nullptr, &vi_texture->view));

    // Update descriptor image info member that can be used for setting up descriptor sets
    vi_texture->descriptor.sampler = vi_texture->sampler;
    vi_texture->descriptor.imageView = vi_texture->view;
    vi_texture->descriptor.imageLayout = vi_texture->imageLayout;

    return vi_texture;
}

std::shared_ptr<qe::render::vulkan::VulkanTexture> qe::render::vulkan::VulkanDevice::Create2DArrayImage(core::Texture kTexture, vk::Format format, vk::ImageUsageFlagBits imageUsage, vk::ImageLayout imageLayout, bool forceLinear)
{
    auto vi_texture = std::make_shared<qe::render::vulkan::VulkanTexture>();

    vi_texture->tex_width = kTexture.get_width();
    vi_texture->tex_height = kTexture.get_height();
    vi_texture->layer_count = kTexture.get_mip_level();
    vi_texture->mip_level = kTexture.get_mip_level();

    vk::MemoryAllocateInfo memAllocInfo;
    vk::MemoryRequirements memReqs;

    // Create a host-visible staging buffer that contains the raw image data
    vk::Buffer stagingBuffer;
    vk::DeviceMemory stagingMemory;

    vk::BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = kTexture.get_size();
    // This buffer is used as a transfer source for the buffer copy
    bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
    bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

    VK_CHECK_RESULT(logic_device_.createBuffer(&bufferCreateInfo, nullptr, &stagingBuffer));

    // Get memory requirements for the staging buffer (alignment, memory type bits)
    logic_device_.getBufferMemoryRequirements(stagingBuffer, &memReqs);

    memAllocInfo.allocationSize = memReqs.size;
    // Get memory type index for a host visible buffer
    memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    
    VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &stagingMemory));
    logic_device_.bindBufferMemory(stagingBuffer, stagingMemory, 0);

    // Copy texture data into staging buffer
    void *data;
    VK_CHECK_RESULT(logic_device_.mapMemory(stagingMemory, 0, memReqs.size, vk::MemoryMapFlagBits(), &data));
    memcpy(data, kTexture.get_data(), static_cast<size_t>(kTexture.get_size()));
    logic_device_.unmapMemory(stagingMemory);

    // Setup buffer copy regions for each layer including all of it's miplevels
    std::vector<vk::BufferImageCopy> bufferCopyRegions;
    size_t offset = 0;

    for (uint32_t layer = 0; layer < kTexture.get_layer_count(); layer++)
    {
        for (uint32_t level = 0; level < kTexture.get_mip_level(); level++)
        {
            vk::BufferImageCopy bufferCopyRegion;
            bufferCopyRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
            bufferCopyRegion.imageSubresource.mipLevel = level;
            bufferCopyRegion.imageSubresource.baseArrayLayer = layer;
            bufferCopyRegion.imageSubresource.layerCount = 1;
            bufferCopyRegion.imageExtent.width = kTexture.get_width();
            bufferCopyRegion.imageExtent.height = kTexture.get_height();
            bufferCopyRegion.imageExtent.depth = 1;
            bufferCopyRegion.bufferOffset = offset;

            bufferCopyRegions.push_back(bufferCopyRegion);

            // Increase offset into staging buffer for next level / face
            //offset += tex2DArray[layer][level].size();
            offset += kTexture.get_size();
        }
    }

    // Create optimal tiled target image
    vk::ImageCreateInfo imageCreateInfo;
    imageCreateInfo.imageType = vk::ImageType::e2D;
    imageCreateInfo.format = format;
    imageCreateInfo.samples = vk::SampleCountFlagBits::e1;
    imageCreateInfo.tiling = vk::ImageTiling::eOptimal;
    imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;
    imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageCreateInfo.extent = { kTexture.get_width(), kTexture.get_height(), 1 };
    imageCreateInfo.usage = imageUsage;
    // Ensure that the TRANSFER_DST bit is set for staging
    if (!(imageCreateInfo.usage & vk::ImageUsageFlagBits::eTransferDst))
    {
        imageCreateInfo.usage |= vk::ImageUsageFlagBits::eTransferDst;
    }
    imageCreateInfo.arrayLayers = kTexture.get_layer_count();
    imageCreateInfo.mipLevels = kTexture.get_mip_level();

    VK_CHECK_RESULT(logic_device_.createImage(&imageCreateInfo, nullptr, &vi_texture->image));

    logic_device_.getImageMemoryRequirements(vi_texture->image, &memReqs);

    memAllocInfo.allocationSize = memReqs.size;
    memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);
    
    VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &vi_texture->mem));
    logic_device_.bindImageMemory(vi_texture->image, vi_texture->mem, 0);

    // Use a separate command buffer for texture loading
    vk::CommandBuffer copyCmd = CreateCommandBuffer(vk::CommandBufferLevel::ePrimary, true);

    // Image barrier for optimal image (target)
    // Set initial layout for all array layers (faces) of the optimal (target) tiled texture
    vk::ImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = kTexture.get_mip_level();
    subresourceRange.layerCount = kTexture.get_layer_count();

    // Setup image memory barrier
    render::vulkan::VulkanTools::setImageLayout(
        copyCmd,
        vi_texture->image,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eTransferDstOptimal,
        subresourceRange);

    // Copy the layers and mip levels from the staging buffer to the optimal tiled image
    copyCmd.copyBufferToImage(
        stagingBuffer,
        vi_texture->image,
        vk::ImageLayout::eTransferDstOptimal,
        static_cast<uint32_t>(bufferCopyRegions.size()),
        bufferCopyRegions.data()
    );

    // Change texture image layout to shader read after all mip levels have been copied
    vi_texture->imageLayout = imageLayout;
    render::vulkan::VulkanTools::setImageLayout(
        copyCmd,
        vi_texture->image,
        vk::ImageLayout::eTransferDstOptimal,
        imageLayout,
        subresourceRange);

    FlushCommandBuffer(copyCmd, queue_);

    // Create sampler
    vk::SamplerCreateInfo samplerCreateInfo;
    samplerCreateInfo.magFilter = vk::Filter::eLinear;
    samplerCreateInfo.minFilter = vk::Filter::eLinear;
    samplerCreateInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
    samplerCreateInfo.addressModeU = vk::SamplerAddressMode::eClampToEdge;
    samplerCreateInfo.addressModeV = samplerCreateInfo.addressModeU;
    samplerCreateInfo.addressModeW = samplerCreateInfo.addressModeU;
    samplerCreateInfo.mipLodBias = 0.0f;
    samplerCreateInfo.maxAnisotropy = 8;
    samplerCreateInfo.compareOp = vk::CompareOp::eNever;
    samplerCreateInfo.minLod = 0.0f;
    samplerCreateInfo.maxLod = kTexture.get_mip_level();
    samplerCreateInfo.borderColor = vk::BorderColor::eFloatOpaqueWhite;
    VK_CHECK_RESULT(logic_device_.createSampler(&samplerCreateInfo, nullptr, &vi_texture->sampler));

    // Create image view
    vk::ImageViewCreateInfo viewCreateInfo;
    viewCreateInfo.viewType = vk::ImageViewType::e2DArray;
    viewCreateInfo.format = format;
    viewCreateInfo.components = { vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA };
    viewCreateInfo.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };
    viewCreateInfo.subresourceRange.layerCount = kTexture.get_layer_count();
    viewCreateInfo.subresourceRange.levelCount = kTexture.get_mip_level();
    viewCreateInfo.image = vi_texture->image;
    VK_CHECK_RESULT(logic_device_.createImageView(&viewCreateInfo, nullptr, &vi_texture->view));

    // Clean up staging resources
    logic_device_.freeMemory(stagingMemory);
    logic_device_.destroyBuffer(stagingBuffer);

    // Update descriptor image info member that can be used for setting up descriptor sets
    vi_texture->descriptor.sampler = vi_texture->sampler;
    vi_texture->descriptor.imageView = vi_texture->view;
    vi_texture->descriptor.imageLayout = vi_texture->imageLayout;

    return vi_texture;
}

std::shared_ptr<qe::render::vulkan::VulkanTexture> qe::render::vulkan::VulkanDevice::CreateCubeMapImage(core::Texture kTexture, vk::Format format, vk::ImageUsageFlagBits imageUsage, vk::ImageLayout imageLayout, bool forceLinear)
{
    auto vi_texture = std::make_shared<qe::render::vulkan::VulkanTexture>();

    vi_texture->tex_width = kTexture.get_width();
    vi_texture->tex_height = kTexture.get_height();
    vi_texture->mip_level = kTexture.get_mip_level();

    vk::MemoryAllocateInfo memAllocInfo;
    vk::MemoryRequirements memReqs;

    // Create a host-visible staging buffer that contains the raw image data
    vk::Buffer stagingBuffer;
    vk::DeviceMemory stagingMemory;

    vk::BufferCreateInfo bufferCreateInfo;
    bufferCreateInfo.size = kTexture.get_size();
    // This buffer is used as a transfer source for the buffer copy
    bufferCreateInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
    bufferCreateInfo.sharingMode = vk::SharingMode::eExclusive;

    VK_CHECK_RESULT(logic_device_.createBuffer(&bufferCreateInfo, nullptr, &stagingBuffer));

    // Get memory requirements for the staging buffer (alignment, memory type bits)
    logic_device_.getBufferMemoryRequirements(stagingBuffer, &memReqs);

    memAllocInfo.allocationSize = memReqs.size;
    // Get memory type index for a host visible buffer
    memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);

    VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &stagingMemory));
    logic_device_.bindBufferMemory(stagingBuffer, stagingMemory, 0);

    // Copy texture data into staging buffer
    void *data;
    VK_CHECK_RESULT(logic_device_.mapMemory(stagingMemory, 0, memReqs.size, vk::MemoryMapFlagBits(), &data));
    memcpy(data, kTexture.get_data(), static_cast<size_t>(kTexture.get_size()));
    logic_device_.unmapMemory(stagingMemory);

    // Setup buffer copy regions for each layer including all of it's miplevels
    std::vector<vk::BufferImageCopy> bufferCopyRegions;
    size_t offset = 0;

    for (uint32_t face = 0; face < 6; face++)
    {
        for (uint32_t level = 0; level < vi_texture->mip_level; level++)
        {
            vk::BufferImageCopy bufferCopyRegion;
            bufferCopyRegion.imageSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
            bufferCopyRegion.imageSubresource.mipLevel = level;
            bufferCopyRegion.imageSubresource.baseArrayLayer = face;
            bufferCopyRegion.imageSubresource.layerCount = 1;
            bufferCopyRegion.imageExtent.width = kTexture.get_width();
            bufferCopyRegion.imageExtent.height = kTexture.get_height();
            bufferCopyRegion.imageExtent.depth = 1;
            bufferCopyRegion.bufferOffset = offset;

            bufferCopyRegions.push_back(bufferCopyRegion);

            // Increase offset into staging buffer for next level / face
            //offset += texCube[face][level].size();
            offset += kTexture.get_size();
        }
    }

    // Create optimal tiled target image
    vk::ImageCreateInfo imageCreateInfo;
    imageCreateInfo.imageType = vk::ImageType::e2D;
    imageCreateInfo.format = format;
    imageCreateInfo.mipLevels = vi_texture->mip_level;
    imageCreateInfo.samples = vk::SampleCountFlagBits::e1;
    imageCreateInfo.tiling = vk::ImageTiling::eOptimal;
    imageCreateInfo.sharingMode = vk::SharingMode::eExclusive;
    imageCreateInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageCreateInfo.extent = { kTexture.get_width(), kTexture.get_height(), 1 };
    imageCreateInfo.usage = imageUsage;
    // Ensure that the TRANSFER_DST bit is set for staging
    if (!(imageCreateInfo.usage & vk::ImageUsageFlagBits::eTransferDst))
    {
        imageCreateInfo.usage |= vk::ImageUsageFlagBits::eTransferDst;
    }
    imageCreateInfo.arrayLayers = 6;
    imageCreateInfo.flags = vk::ImageCreateFlagBits::eCubeCompatible;

    VK_CHECK_RESULT(logic_device_.createImage(&imageCreateInfo, nullptr, &vi_texture->image));

    logic_device_.getImageMemoryRequirements(vi_texture->image, &memReqs);

    memAllocInfo.allocationSize = memReqs.size;
    memAllocInfo.memoryTypeIndex = GetMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

    VK_CHECK_RESULT(logic_device_.allocateMemory(&memAllocInfo, nullptr, &vi_texture->mem));
    logic_device_.bindImageMemory(vi_texture->image, vi_texture->mem, 0);

    // Use a separate command buffer for texture loading
    vk::CommandBuffer copyCmd = CreateCommandBuffer(vk::CommandBufferLevel::ePrimary, true);

    // Image barrier for optimal image (target)
    // Set initial layout for all array layers (faces) of the optimal (target) tiled texture
    vk::ImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = kTexture.get_mip_level();
    subresourceRange.layerCount = 6;

    // Setup image memory barrier
    render::vulkan::VulkanTools::setImageLayout(
        copyCmd,
        vi_texture->image,
        vk::ImageLayout::eUndefined,
        vk::ImageLayout::eTransferDstOptimal,
        subresourceRange);

    // Copy the layers and mip levels from the staging buffer to the optimal tiled image
    copyCmd.copyBufferToImage(
        stagingBuffer,
        vi_texture->image,
        vk::ImageLayout::eTransferDstOptimal,
        static_cast<uint32_t>(bufferCopyRegions.size()),
        bufferCopyRegions.data()
    );

    // Change texture image layout to shader read after all mip levels have been copied
    vi_texture->imageLayout = imageLayout;
    render::vulkan::VulkanTools::setImageLayout(
        copyCmd,
        vi_texture->image,
        vk::ImageLayout::eTransferDstOptimal,
        imageLayout,
        subresourceRange);

    FlushCommandBuffer(copyCmd, queue_);

    // Create sampler
    vk::SamplerCreateInfo samplerCreateInfo;
    samplerCreateInfo.magFilter = vk::Filter::eLinear;
    samplerCreateInfo.minFilter = vk::Filter::eLinear;
    samplerCreateInfo.mipmapMode = vk::SamplerMipmapMode::eLinear;
    samplerCreateInfo.addressModeU = vk::SamplerAddressMode::eClampToEdge;
    samplerCreateInfo.addressModeV = samplerCreateInfo.addressModeU;
    samplerCreateInfo.addressModeW = samplerCreateInfo.addressModeU;
    samplerCreateInfo.mipLodBias = 0.0f;
    samplerCreateInfo.maxAnisotropy = 8;
    samplerCreateInfo.compareOp = vk::CompareOp::eNever;
    samplerCreateInfo.minLod = 0.0f;
    samplerCreateInfo.maxLod = kTexture.get_mip_level();
    samplerCreateInfo.borderColor = vk::BorderColor::eFloatOpaqueWhite;
    VK_CHECK_RESULT(logic_device_.createSampler(&samplerCreateInfo, nullptr, &vi_texture->sampler));

    // Create image view
    vk::ImageViewCreateInfo viewCreateInfo;
    viewCreateInfo.viewType = vk::ImageViewType::eCube;
    viewCreateInfo.format = format;
    viewCreateInfo.components = { vk::ComponentSwizzle::eR, vk::ComponentSwizzle::eG, vk::ComponentSwizzle::eB, vk::ComponentSwizzle::eA };
    viewCreateInfo.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };
    viewCreateInfo.subresourceRange.layerCount = 6;
    viewCreateInfo.subresourceRange.levelCount = kTexture.get_mip_level();
    viewCreateInfo.image = vi_texture->image;
    VK_CHECK_RESULT(logic_device_.createImageView(&viewCreateInfo, nullptr, &vi_texture->view));

    // Clean up staging resources
    logic_device_.freeMemory(stagingMemory);
    logic_device_.destroyBuffer(stagingBuffer);

    // Update descriptor image info member that can be used for setting up descriptor sets
    vi_texture->descriptor.sampler = vi_texture->sampler;
    vi_texture->descriptor.imageView = vi_texture->view;
    vi_texture->descriptor.imageLayout = vi_texture->imageLayout;

    return vi_texture;
}

auto qe::render::vulkan::VulkanDevice::QuerySwapChainSupport() -> qe::render::vulkan::VulkanDevice::SwapChainSupportDetails
{
    SwapChainSupportDetails details;

    physical_device_.getSurfaceCapabilitiesKHR(surface_, &details.capabilities);

    uint32_t formatCount;
    physical_device_.getSurfaceFormatsKHR(surface_, &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        physical_device_.getSurfaceFormatsKHR(surface_, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    physical_device_.getSurfacePresentModesKHR(surface_, &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        physical_device_.getSurfacePresentModesKHR(surface_, &presentModeCount, details.presentModes.data());
    }

    return details;
}

void qe::render::vulkan::VulkanDevice::CreateSwapChain()
{
    SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport();

    auto surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);

    auto presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);

    auto extent = ChooseSwapExtent(swapChainSupport.capabilities);

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }
    
    vk::SwapchainCreateInfoKHR createInfo = {};
    createInfo.surface = surface_;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;
    createInfo.imageSharingMode = vk::SharingMode::eExclusive;
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    VK_CHECK_RESULT(logic_device_.createSwapchainKHR(&createInfo, nullptr, &swap_chain_));

    VK_CHECK_RESULT(logic_device_.getSwapchainImagesKHR(swap_chain_, &imageCount, nullptr));

    swap_chain_images_.resize(imageCount);

    VK_CHECK_RESULT(logic_device_.getSwapchainImagesKHR(swap_chain_, &imageCount, swap_chain_images_.data()));

    swap_chain_image_format_ = surfaceFormat.format;

    swap_chain_extent_ = extent;
}

void qe::render::vulkan::VulkanDevice::CreateSwapChainImageView()
{
    swap_chain_image_views_.resize(swap_chain_images_.size());

    for (uint32_t i = 0; i < swap_chain_images_.size(); i++) {
        swap_chain_image_views_[i] = CreateImageView(swap_chain_images_[i], swap_chain_image_format_, vk::ImageAspectFlagBits::eColor);
    }
}



auto qe::render::vulkan::VulkanDevice::ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) -> vk::SurfaceFormatKHR
{
    if (availableFormats.size() == 1 && availableFormats[0].format == vk::Format::eUndefined) {
        return{ vk::Format::eB8G8R8A8Unorm, vk::ColorSpaceKHR::eSrgbNonlinear };
    }

    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == vk::Format::eB8G8R8A8Unorm 
            && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

auto qe::render::vulkan::VulkanDevice::ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR> availablePresentModes) -> vk::PresentModeKHR
{
    vk::PresentModeKHR bestMode = vk::PresentModeKHR::eFifo;

    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
            return availablePresentMode;
        }
        else if (availablePresentMode == vk::PresentModeKHR::eImmediate) {
            bestMode = availablePresentMode;
        }
    }

    return bestMode;
}


auto qe::render::vulkan::VulkanDevice::ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) -> vk::Extent2D
{
    if (capabilities.currentExtent.width != UINT_MAX) {
        return capabilities.currentExtent;
    }
    else {
        int width = 800; // temp set 800*600
        int height = 600;

        vk::Extent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = glm::max<uint32_t>(capabilities.minImageExtent.width, glm::min<uint32_t>(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = glm::max<uint32_t>(capabilities.minImageExtent.height, glm::min<uint32_t>(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}

void qe::render::vulkan::VulkanDevice::InitSwapChain()
{
    CreateSwapChain();

    CreateSwapChainImageView();
}

void qe::render::vulkan::VulkanDevice::CreateRenderPass()
{
    vk::AttachmentDescription colorAttachment = {};
    colorAttachment.format = swap_chain_image_format_;
    colorAttachment.samples = msaa_samples_;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::AttachmentDescription depthAttachment = {};
    depthAttachment.format = depth_format_;
    depthAttachment.samples = msaa_samples_;
    depthAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    depthAttachment.storeOp = vk::AttachmentStoreOp::eDontCare;
    depthAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    depthAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    depthAttachment.initialLayout = vk::ImageLayout::eUndefined;
    depthAttachment.finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

    vk::AttachmentDescription colorAttachmentResolve = {};
    colorAttachmentResolve.format = swap_chain_image_format_;
    colorAttachmentResolve.samples = vk::SampleCountFlagBits::e1;
    colorAttachmentResolve.loadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachmentResolve.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachmentResolve.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachmentResolve.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachmentResolve.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachmentResolve.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::AttachmentReference depthAttachmentRef = {};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = vk::ImageLayout::eDepthStencilAttachmentOptimal;

    vk::AttachmentReference colorAttachmentResolveRef = {};
    colorAttachmentResolveRef.attachment = 2;
    colorAttachmentResolveRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subpass = {};
    subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pResolveAttachments = &colorAttachmentResolveRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    std::array<vk::AttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, colorAttachmentResolve };

    vk::RenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 0;
    renderPassInfo.pDependencies = nullptr;

    VK_CHECK_RESULT(logic_device_.createRenderPass(&renderPassInfo, nullptr, &render_pass_));
   
}

void qe::render::vulkan::VulkanDevice::CreateFrameBuffer()
{
    swap_chain_frame_buffers_.resize(swap_chain_image_views_.size());

    createImage(
        swap_chain_extent_.width,
        swap_chain_extent_.height,
        swap_chain_image_format_,
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eColorAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        color_image_,
        color_image_memory_
    );

    color_image_view_ = CreateImageView(color_image_, swap_chain_image_format_, vk::ImageAspectFlagBits::eColor);


    createImage(
        swap_chain_extent_.width, 
        swap_chain_extent_.height, 
        depth_format_, 
        vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eDepthStencilAttachment,
        vk::MemoryPropertyFlagBits::eDeviceLocal,
        frame_buffer_depth_image_,
        frame_buffer_depth_image_memory_
        );

    frame_buffer_depth_image_view_ = CreateImageView(frame_buffer_depth_image_, depth_format_, vk::ImageAspectFlagBits::eDepth);

    for (size_t i = 0; i < swap_chain_image_views_.size(); i++) {
        std::array<vk::ImageView, 3> attachments = {
            color_image_view_,
            frame_buffer_depth_image_view_,
            swap_chain_image_views_[i]
        }; 

        vk::FramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.renderPass = render_pass_;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swap_chain_extent_.width;
        framebufferInfo.height = swap_chain_extent_.height;
        framebufferInfo.layers = 1;

        logic_device_.createFramebuffer(&framebufferInfo, nullptr, &swap_chain_frame_buffers_[i]);
    }
}

vk::SampleCountFlagBits qe::render::vulkan::VulkanDevice::GetMSAASample(vk::PhysicalDeviceProperties properties)
{
    vk::SampleCountFlags counts = properties.limits.framebufferColorSampleCounts & properties.limits.framebufferDepthSampleCounts;
    if (counts & vk::SampleCountFlagBits::e64) { return vk::SampleCountFlagBits::e64; }
    if (counts & vk::SampleCountFlagBits::e32) { return vk::SampleCountFlagBits::e32; }
    if (counts & vk::SampleCountFlagBits::e16) { return vk::SampleCountFlagBits::e16; }
    if (counts & vk::SampleCountFlagBits::e8) { return vk::SampleCountFlagBits::e8; }
    if (counts & vk::SampleCountFlagBits::e4) { return vk::SampleCountFlagBits::e4; }
    if (counts & vk::SampleCountFlagBits::e2) { return vk::SampleCountFlagBits::e2; }

    return vk::SampleCountFlagBits::e1;
}

void qe::render::vulkan::VulkanDevice::CreateSurface(vk::SurfaceKHR& surface)
{
    vk::Win32SurfaceCreateInfoKHR create_info;
    create_info.setHinstance(GetModuleHandle(nullptr));
    create_info.setHwnd(window_);
    VK_CHECK_RESULT(instance_.createWin32SurfaceKHR(&create_info, nullptr, &surface));
}
