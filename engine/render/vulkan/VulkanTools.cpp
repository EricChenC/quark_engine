#include "VulkanTools.h"

#include <iostream>
#include <fstream>
#include <string.h>

qe::render::vulkan::VulkanTools::VulkanTools()
{
}

qe::render::vulkan::VulkanTools::~VulkanTools()
{
}


std::string qe::render::vulkan::VulkanTools::errorString(vk::Result errorCode)
{
    switch (errorCode)
    {
#define STR(r) case vk::Result:: ##r: return #r
        STR(eSuccess);
        STR(eNotReady);
        STR(eTimeout);
        STR(eEventSet);
        STR(eEventReset);
        STR(eIncomplete);
        STR(eErrorOutOfHostMemory);
        STR(eErrorOutOfDeviceMemory);
        STR(eErrorInitializationFailed);
        STR(eErrorDeviceLost);
        STR(eErrorMemoryMapFailed);
        STR(eErrorLayerNotPresent);
        STR(eErrorExtensionNotPresent);
        STR(eErrorFeatureNotPresent);
        STR(eErrorIncompatibleDriver);
        STR(eErrorTooManyObjects);
        STR(eErrorFormatNotSupported);
        STR(eErrorFragmentedPool);
        STR(eErrorOutOfPoolMemory);
        STR(eErrorInvalidExternalHandle);
        STR(eErrorSurfaceLostKHR);
        STR(eErrorNativeWindowInUseKHR);
        STR(eSuboptimalKHR);
        STR(eErrorOutOfDateKHR);
        STR(eErrorIncompatibleDisplayKHR);
        STR(eErrorValidationFailedEXT);
        STR(eErrorInvalidShaderNV);
        STR(eErrorNotPermittedEXT);
    default:
        return "UNKNOWN_ERROR";
    }
}


std::string qe::render::vulkan::VulkanTools::physicalDeviceTypeString(vk::PhysicalDeviceType type)
{
    switch (type)
    {
#define STR(r) case vk::PhysicalDeviceType:: ##r: return #r
        STR(eOther);
        STR(eIntegratedGpu);
        STR(eDiscreteGpu);
        STR(eVirtualGpu);
        STR(eCpu);
#undef STR
    default: return "UNKNOWN_DEVICE_TYPE";
    }
}


VkBool32 qe::render::vulkan::VulkanTools::getSupportedDepthFormat(vk::PhysicalDevice physicalDevice, vk::Format * depthFormat)
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


void qe::render::vulkan::VulkanTools::setImageLayout(
    vk::CommandBuffer cmdbuffer, 
    vk::Image image, 
    vk::ImageLayout oldImageLayout,
    vk::ImageLayout newImageLayout,
    vk::ImageSubresourceRange subresourceRange,
    vk::PipelineStageFlagBits srcStageMask,
    vk::PipelineStageFlagBits dstStageMask)
{
    // Create an image barrier object
    vk::ImageMemoryBarrier imageMemoryBarrier;
    imageMemoryBarrier.oldLayout = oldImageLayout;
    imageMemoryBarrier.newLayout = newImageLayout;
    imageMemoryBarrier.image = image;
    imageMemoryBarrier.subresourceRange = subresourceRange;

    // Source layouts (old)
    // Source access mask controls actions that have to be finished on the old layout
    // before it will be transitioned to the new layout
    switch (oldImageLayout)
    {
    case vk::ImageLayout::eColorAttachmentOptimal:
        // Image is a color attachment
        // Make sure any writes to the color buffer have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
        break;
    case vk::ImageLayout::eDepthStencilAttachmentOptimal:
        // Image is a depth/stencil attachment
        // Make sure any writes to the depth/stencil buffer have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eDepthStencilAttachmentWrite;
        break;
    case vk::ImageLayout::eShaderReadOnlyOptimal:
        // Image is read by a shader
        // Make sure any shader reads from the image have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eShaderRead;
        break;
    case vk::ImageLayout::eTransferSrcOptimal:
        // Image is a transfer source 
        // Make sure any reads from the image have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
        break;
    case vk::ImageLayout::eTransferDstOptimal:
        // Image is a transfer destination
        // Make sure any writes to the image have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
        break;
    case vk::ImageLayout::ePreinitialized:
        // Image is preinitialized
        // Only valid as initial layout for linear images, preserves memory contents
        // Make sure host writes have been finished
        imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eHostWrite;
        break;
    default:
        break;
    }

    // Target layouts (new)
    // Destination access mask controls the dependency for the new image layout
    switch (newImageLayout)
    {
    case vk::ImageLayout::eColorAttachmentOptimal:
        // Image will be used as a color attachment
        // Make sure any writes to the color buffer have been finished
        imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
        break;
    case vk::ImageLayout::eDepthStencilAttachmentOptimal:
        // Image layout will be used as a depth/stencil attachment
        // Make sure any writes to depth/stencil buffer have been finished
        imageMemoryBarrier.dstAccessMask = imageMemoryBarrier.dstAccessMask | vk::AccessFlagBits::eDepthStencilAttachmentWrite;
        break;
    case vk::ImageLayout::eShaderReadOnlyOptimal:
        // Image will be read in a shader (sampler, input attachment)
        // Make sure any writes to the image have been finished
        if (imageMemoryBarrier.srcAccessMask == vk::AccessFlags())
        {
            imageMemoryBarrier.srcAccessMask = vk::AccessFlagBits::eHostWrite | vk::AccessFlagBits::eTransferWrite;
        }
        imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;
        break;
    case vk::ImageLayout::eTransferSrcOptimal:
        // Image will be used as a transfer source
        // Make sure any reads from the image have been finished
        imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;
        break;
    case vk::ImageLayout::eTransferDstOptimal:
        // Image will be used as a transfer destination
        // Make sure any writes to the image have been finished
        imageMemoryBarrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;
        break;
    default:
        break;
    }


    cmdbuffer.pipelineBarrier(
        srcStageMask, 
        dstStageMask, 
        vk::DependencyFlags(), 
        0, nullptr,
        0, nullptr,
        1, &imageMemoryBarrier);
}


    void qe::render::vulkan::VulkanTools::setImageLayout(vk::CommandBuffer cmdbuffer,
    vk::Image image,
    vk::ImageAspectFlagBits aspectMask,
    vk::ImageLayout oldImageLayout,
    vk::ImageLayout newImageLayout,
    vk::PipelineStageFlagBits srcStageMask,
    vk::PipelineStageFlagBits dstStageMask)
{
    vk::ImageSubresourceRange subresourceRange;
    subresourceRange.aspectMask = aspectMask;
    subresourceRange.baseMipLevel = 0;
    subresourceRange.levelCount = 1;
    subresourceRange.layerCount = 1;
    setImageLayout(cmdbuffer, image, oldImageLayout, newImageLayout, subresourceRange, srcStageMask, dstStageMask);
}


    void qe::render::vulkan::VulkanTools::insertImageMemoryBarrier(
    vk::CommandBuffer cmdbuffer,
    vk::Image image,
    vk::AccessFlagBits srcAccessMask,
    vk::AccessFlagBits dstAccessMask,
    vk::ImageLayout oldImageLayout,
    vk::ImageLayout newImageLayout,
    vk::PipelineStageFlagBits srcStageMask,
    vk::PipelineStageFlagBits dstStageMask,
    vk::ImageSubresourceRange subresourceRange)
{
    vk::ImageMemoryBarrier imageMemoryBarrier;
    imageMemoryBarrier.srcAccessMask = srcAccessMask;
    imageMemoryBarrier.dstAccessMask = dstAccessMask;
    imageMemoryBarrier.oldLayout = oldImageLayout;
    imageMemoryBarrier.newLayout = newImageLayout;
    imageMemoryBarrier.image = image;
    imageMemoryBarrier.subresourceRange = subresourceRange;

    cmdbuffer.pipelineBarrier(
        srcStageMask,
        dstStageMask,
        vk::DependencyFlags(),
        0, nullptr,
        0, nullptr,
        1, &imageMemoryBarrier);
}


    void qe::render::vulkan::VulkanTools::exitFatal(std::string message, std::string caption)
{
    std::cout << message << " " << caption << std::endl;

    exit(1);
}

std::string qe::render::vulkan::VulkanTools::readTextFile(const char * fileName)
{
    std::string fileContent;
    std::ifstream fileStream(fileName, std::ios::in);
    if (!fileStream.is_open()) {
        printf("File %s not found\n", fileName);
        return "";
    }
    std::string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        fileContent.append(line + "\n");
    }
    fileStream.close();
    return fileContent;
}

vk::ShaderModule qe::render::vulkan::VulkanTools::loadShader(const char * fileName, vk::Device device)
{
    std::ifstream is(fileName, std::ios::binary | std::ios::in | std::ios::ate);

    if (is.is_open())
    {
        size_t size = is.tellg();
        is.seekg(0, std::ios::beg);
        char* shaderCode = new char[size];
        is.read(shaderCode, size);
        is.close();

        assert(size > 0);

        vk::ShaderModule shaderModule;
        vk::ShaderModuleCreateInfo moduleCreateInfo;
        moduleCreateInfo.codeSize = size;
        moduleCreateInfo.pCode = (uint32_t*)shaderCode;

        VK_CHECK_RESULT(device.createShaderModule(&moduleCreateInfo, NULL, &shaderModule));

        delete[] shaderCode;

        return shaderModule;
    }
    else
    {
        std::cerr << "Error: Could not open shader file \"" << fileName << "\"" << std::endl;
        return vk::ShaderModule();
    }
}


vk::ShaderModule qe::render::vulkan::VulkanTools::loadShaderGLSL(const char *fileName, vk::Device device, vk::ShaderStageFlagBits stage)
{
    std::string shaderSrc = readTextFile(fileName);
    const char *shaderCode = shaderSrc.c_str();
    size_t size = strlen(shaderCode);
    assert(size > 0);

    vk::ShaderModule shaderModule;
    vk::ShaderModuleCreateInfo moduleCreateInfo;
    moduleCreateInfo.pNext = NULL;
    moduleCreateInfo.codeSize = 3 * sizeof(uint32_t) + size + 1;
    moduleCreateInfo.pCode = (uint32_t*)malloc(moduleCreateInfo.codeSize);

    // Magic SPV number
    ((uint32_t *)moduleCreateInfo.pCode)[0] = 0x07230203;
    ((uint32_t *)moduleCreateInfo.pCode)[1] = 0;
    ((uint32_t *)moduleCreateInfo.pCode)[2] = (uint32_t)stage;
    memcpy(((uint32_t *)moduleCreateInfo.pCode + 3), shaderCode, size + 1);

    VK_CHECK_RESULT(device.createShaderModule(&moduleCreateInfo, NULL, &shaderModule));

    return shaderModule;
}


bool qe::render::vulkan::VulkanTools::fileExists(const std::string & filename)
{
    std::ifstream f(filename.c_str());
    return !f.fail();
}
