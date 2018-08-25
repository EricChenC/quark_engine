#include "QuarkWindow.h"

#include <qevent.h>
#include <QDragEnterEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <qtimer.h>
#include <QTime>
#include <qcursor.h>
#include <qpixmap.h>

#include <qmimedata.h>

#include "Scene.h"
#include "Transform.h"
#include "Mesh.h"
#include "QuarkObject.h"
#include "Resource.h"
#include "VulkanTools.h"
#include "VulkanDevice.h"
#include "CameraController.h"
#include "VulkanBuffer.h"
#include "Material.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "QuarkString.h"
#include "AwakeBehaviour.h"
#include "Shader.h"
#include "ScriptBehaviour.h"
#include "Camera.h"

#include <iostream>


qe::edit::QuarkWindow::QuarkWindow()
    : vi_device_(std::make_shared<qe::render::vulkan::VulkanDevice>(reinterpret_cast<HWND>(this->winId())))
    , resource_(std::make_shared<qe::core::Resource>())
    , camera_controller_(nullptr)
    , scene_(nullptr)
    , frame_count_(0)
    , fps_number_(0)
    , fps_time_(0.0f)
    , delta_time_(0.0f)
    , key_press_time_(0.0f)
    , is_update_material_(false)
    , left_button_press_(false)
    , right_button_press_(false)
    , middle_button_press_(false)
    , key_press_(false)
    , alt_button_press_(false)
    , init_mouse_pos_(false)
    , kShaderPath("D:/project/quark_engine/media/shader/standard.shader")
{
    eye_lookat_cursor_ = std::make_shared<QCursor>(QPixmap("D:/project/quark_engine/media/image/eye_lookat.png"));
    eye_rotate_cursor_ = std::make_shared<QCursor>(QPixmap("D:/project/quark_engine/media/image/eye_rotate.png"));
    eye_smooth_cursor_ = std::make_shared<QCursor>(QPixmap("D:/project/quark_engine/media/image/eye_smooth.png"));
}

qe::edit::QuarkWindow::~QuarkWindow()
{
    ReleaseRenderData();
}

void qe::edit::QuarkWindow::Init()
{
    light_dir_ = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);

    graphics_timer_ = std::make_shared<QTimer>();
    graphics_timer_->setInterval(1);
    connect(graphics_timer_.get(), SIGNAL(timeout()), this, SLOT(update()));
    graphics_timer_->start(1);
}

void qe::edit::QuarkWindow::resizeEvent(QResizeEvent * event)
{
    if (!scene_) return;

    auto size = event->size();
    SetCameraAspect(size.width(), size.height());
}

void qe::edit::QuarkWindow::mouseMoveEvent(QMouseEvent * event)
{

    if (!scene_) return;

    if (!left_button_press_ && !right_button_press_ && !middle_button_press_) {
        return;
    }

    if (!init_mouse_pos_) {
        init_mouse_pos_ = true;
        mouse_last_pos_ = glm::vec2(event->pos().x(), event->pos().y());
        return;
    }

    glm::vec2 mouse_pos = glm::vec2(event->pos().x(), event->pos().y());
    glm::vec2 move_span = mouse_last_pos_ - mouse_pos;
    mouse_last_pos_ = mouse_pos;

    if (alt_button_press_) {
        if (left_button_press_) {
            this->setCursor(*(eye_lookat_cursor_.get()));
            camera_controller_->LookAtRotate(move_span);
        }

        if (right_button_press_) {

            this->setCursor(*(eye_smooth_cursor_.get()));

            if (move_span.y > 0) {
                camera_controller_->SmoothZoom(-delta_time_);
            }
            else {
                camera_controller_->SmoothZoom(delta_time_);
            }
            
        }
    }
    else {
        if (right_button_press_) {
            camera_controller_->RotateCamera(move_span);
        }
    }

    if (middle_button_press_) {
        camera_controller_->DragCamera(move_span * 0.01f);
    }

}

void qe::edit::QuarkWindow::mousePressEvent(QMouseEvent * event)
{
    if (!scene_) return;

    switch (event->button())
    {
    case Qt::LeftButton:
    {
        left_button_press_ = true;
        break;
    }
    case Qt::RightButton:
    {
        right_button_press_ = true;
        this->setCursor(*(eye_rotate_cursor_.get()));
        break;
    }
    case Qt::MiddleButton:
    {
        middle_button_press_ = true;
        this->setCursor(Qt::OpenHandCursor);
        break;
    }
    default:
        break;
    }
}

void qe::edit::QuarkWindow::mouseReleaseEvent(QMouseEvent * event)
{
    if (!scene_) return;

    switch (event->button())
    {
    case Qt::LeftButton:
    {
        left_button_press_ = false;
        break;
    }
    case Qt::RightButton:
    {
        right_button_press_ = false;
        break;
    }
    case Qt::MiddleButton:
    {
        middle_button_press_ = false;
        break;
    }
    default:
        break;
    }

    init_mouse_pos_ = false;
    this->setCursor(Qt::ArrowCursor);

}

void qe::edit::QuarkWindow::wheelEvent(QWheelEvent * event)
{
    if (!scene_) return;

    if (event->angleDelta().y() > 0 || event->angleDelta().x() > 0) {
        camera_controller_->ShrinkMove(-delta_time_ * 0.1);
    }
    else {
        camera_controller_->ShrinkMove(delta_time_ * 0.1);
    }
}

void qe::edit::QuarkWindow::keyPressEvent(QKeyEvent * event)
{
    if (!scene_) return;

    if (!key_press_) {
        key_press_ = true;
        press_time_ = std::chrono::high_resolution_clock::now();
    }
    
    auto new_time = std::chrono::high_resolution_clock::now();
    auto press_span = std::chrono::duration<double, std::milli>(new_time - press_time_).count();
    auto max_span = glm::max(1.0, press_span / 1000.0f);

    switch (event->key())
    {
    case Qt::Key_W: // forward
        if (!right_button_press_) break;

        camera_controller_->ShrinkMove(-delta_time_ * max_span);
        break;
    case Qt::Key_S: // back
        if (!right_button_press_) break;

        camera_controller_->ShrinkMove(delta_time_* max_span);
        break;
    case Qt::Key_A: // left
        if (!right_button_press_) break;

        camera_controller_->HorizontalMove(delta_time_* max_span);
        break;
    case Qt::Key_D: // right
        if (!right_button_press_) break;

        camera_controller_->HorizontalMove(-delta_time_* max_span);
        break;
    case Qt::Key_Q: // down
        if (!right_button_press_) break;

        camera_controller_->VerticalMove(-delta_time_* max_span);
        break;
    case Qt::Key_E: // up
        if (!right_button_press_) break;

        camera_controller_->VerticalMove(delta_time_* max_span);
        break;
    case Qt::Key_Alt:
        alt_button_press_ = true;
        break;
    default:
        break;
    }
}

void qe::edit::QuarkWindow::keyReleaseEvent(QKeyEvent * event)
{

    if (!scene_ || event->isAutoRepeat()) return;

    key_press_ = false;

    switch (event->key())
    {
    case Qt::Key_Alt:
        alt_button_press_ = false;
        break;
    }

}

void qe::edit::QuarkWindow::update()
{
    if (!scene_) return;

    auto tStart = std::chrono::high_resolution_clock::now();

    UpdateBehaviour();
    UpdateUniformBuffer();
    Draw();

    frame_count_++;

    auto tEnd = std::chrono::high_resolution_clock::now();
    auto tDiff = std::chrono::duration<double, std::milli>(tEnd - tStart).count();

    delta_time_ = glm::clamp(tDiff, 0.0, 1.0);

    fps_time_ += (float)tDiff;

    if (fps_time_ > 1000.0f)
    {
        fps_number_ = frame_count_;

        fps_time_ = 0.0f;
        frame_count_ = 0.0f;
    }
}

void qe::edit::QuarkWindow::LoadSceneReadyRender(std::shared_ptr<qe::core::Scene> scene)
{
    auto roots = scene->Roots();

    auto standard_shader = std::dynamic_pointer_cast<qe::core::Shader>(resource_->Load(kShaderPath));
    standard_shader->set_global_vector("lightDir", light_dir_);

    auto standard_material = std::make_shared<qe::core::Material>();
    standard_material->set_shader(standard_shader);

    CreateDescriptorSetLayout();

    auto path = standard_material->get_shader()->get_path();
    auto pre_path = qe::core::QuarkString::PathPrefixed(path);
    auto name = qe::core::QuarkString::FileName(path);

    kShaderPre = pre_path + name;

    CreatePipeline();

    CreateUniformBuffer();

    CreateDescriptorSet();

    for (auto root : roots) {
        LoadQuarkObject(root, standard_material);
    }
}

void qe::edit::QuarkWindow::LoadQuarkObject(
    std::shared_ptr<qe::core::QuarkObject> quark_object,
    std::shared_ptr<qe::core::Material> standard_material)
{
    auto mesh_filter = quark_object->GetComponent<qe::core::MeshFilter>();
    if (!mesh_filter) {
        auto childs = quark_object->GetChilds();
        for (auto child : childs) {
            LoadQuarkObject(child, standard_material);
        }

        return;
    }

    auto mesh_renderer = quark_object->AddComponent<qe::core::MeshRenderer>();
    mesh_renderer->AddMaterial(standard_material);

    auto behaviour = quark_object->AddComponent<qe::core::AwakeBehaviour>();
    //behaviours_.push_back(behaviour);

    LoadDrawData(quark_object->GetComponent<qe::core::Transform>()->get_local_matrix(), mesh_filter, mesh_renderer);

    auto childs = quark_object->GetChilds();
    for (auto child : childs) {
        LoadQuarkObject(child, standard_material);
    }
}

void qe::edit::QuarkWindow::LoadDrawData(
    glm::mat4 m,
    std::shared_ptr<qe::core::MeshFilter> mesh_filter,
    std::shared_ptr<qe::core::MeshRenderer> mesh_renderer)
{
    std::vector<Vertex> vertexs;
    std::vector<uint> indexs;

    GetMeshData(mesh_filter->get_mesh(), vertexs, indexs);

    auto vertex_buffer = std::make_shared<qe::render::vulkan::VulkanBuffer>(sizeof(vertexs[0]) * vertexs.size());
    auto index_buffer = std::make_shared<qe::render::vulkan::VulkanBuffer>(sizeof(indexs[0]) * indexs.size());

    vi_device_->CreateH2DBuffer(vertex_buffer.get(), vertexs.data(),vk::BufferUsageFlagBits::eVertexBuffer);
    vi_device_->CreateH2DBuffer(index_buffer.get(), indexs.data(), vk::BufferUsageFlagBits::eIndexBuffer);

    meshData mesh_data;
    mesh_data.vertexs = vertexs;
    mesh_data.indexs = indexs;
    mesh_data.vertex_buffer = vertex_buffer;
    mesh_data.index_buffer = index_buffer;
    mesh_data.m = m;

    mesh_datas_.push_back(mesh_data);

}

void qe::edit::QuarkWindow::GetMeshData(std::shared_ptr<qe::core::Mesh> mesh, std::vector<Vertex>& vertexs, std::vector<uint>& indexs)
{
    for (int i = 0; i < mesh->get_vertex_count(); i++) {
        Vertex vertex = {};

        vertex.pos = mesh->get_vertexs()->at(i);
        vertex.normal = mesh->get_normals()->at(i);
        vertex.uv = mesh->get_uvs()->at(i);

        vertexs.push_back(vertex);
    }

    for (int j = 0; j < mesh->get_index_count(); j++) {
        indexs.push_back(mesh->get_indexs()->at(j));
    }
}

void qe::edit::QuarkWindow::CreateDescriptorSetLayout()
{
    vk::DescriptorSetLayoutBinding uboLayoutBinding = {};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
    uboLayoutBinding.pImmutableSamplers = nullptr;
    uboLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;

    vk::DescriptorSetLayoutBinding uldLayoutBinding = {};
    uldLayoutBinding.binding = 1;
    uldLayoutBinding.descriptorCount = 1;
    uldLayoutBinding.descriptorType = vk::DescriptorType::eUniformBuffer;
    uldLayoutBinding.pImmutableSamplers = nullptr;
    uldLayoutBinding.stageFlags = vk::ShaderStageFlagBits::eVertex;

    std::array<vk::DescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, uldLayoutBinding };

    vk::DescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    VK_CHECK_RESULT(vi_device_->logic_device_.createDescriptorSetLayout(&layoutInfo, nullptr, &descriptor_set_layout_));
}

void qe::edit::QuarkWindow::CreatePipeline()
{
    auto vertShaderPath = kShaderPre + ".vert.spv";
    auto fragShaderPath = kShaderPre + ".frag.spv";

    auto vertShaderModule = qe::render::vulkan::VulkanTools::loadShader(vertShaderPath.c_str(), vi_device_->logic_device_);
    auto fragShaderModule = qe::render::vulkan::VulkanTools::loadShader(fragShaderPath.c_str(), vi_device_->logic_device_);

    vk::PipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();

    vk::PipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
    inputAssembly.primitiveRestartEnable = false;

    vk::Viewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = vi_device_->swap_chain_extent_.width;
    viewport.height = vi_device_->swap_chain_extent_.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
   
    vk::Rect2D scissor = {};
    scissor.offset = { 0, 0 };
    scissor.extent = vi_device_->swap_chain_extent_;
    
    vk::PipelineViewportStateCreateInfo viewportState = {};
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;
    
    vk::PipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.depthClampEnable = false;
    rasterizer.rasterizerDiscardEnable = false;
    rasterizer.polygonMode = vk::PolygonMode::eFill;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = vk::CullModeFlagBits::eBack;
    rasterizer.frontFace = vk::FrontFace::eCounterClockwise;
    rasterizer.depthBiasEnable = false;

    vk::PipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sampleShadingEnable = false;
    multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;

    vk::PipelineDepthStencilStateCreateInfo depthStencil = {};
    depthStencil.depthTestEnable = true;
    depthStencil.depthWriteEnable = true;
    depthStencil.depthCompareOp = vk::CompareOp::eLess;
    depthStencil.depthBoundsTestEnable = false;
    depthStencil.stencilTestEnable = false;

    vk::PipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = false;
    colorBlendAttachment.colorBlendOp = vk::BlendOp::eAdd;
    colorBlendAttachment.srcColorBlendFactor = vk::BlendFactor::eSrcColor;
    colorBlendAttachment.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcColor;
    colorBlendAttachment.alphaBlendOp = vk::BlendOp::eAdd;
    colorBlendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eSrcAlpha;
    colorBlendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;

    vk::PipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.logicOpEnable = false;
    colorBlending.logicOp = vk::LogicOp::eCopy;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    // Push constants for model matrices
    vk::PushConstantRange pushConstantRange = {};
    pushConstantRange.stageFlags = vk::ShaderStageFlagBits::eVertex;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(ModelMatrix);

    vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &descriptor_set_layout_;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    VK_CHECK_RESULT(vi_device_->logic_device_.createPipelineLayout(&pipelineLayoutInfo, nullptr, &pipeline_layout_));

    vk::GraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = pipeline_layout_;
    pipelineInfo.renderPass = vi_device_->render_pass_;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = nullptr;

    pipeline_ = vi_device_->logic_device_.createGraphicsPipeline(nullptr, pipelineInfo);

    vi_device_->logic_device_.destroyShaderModule(vertShaderModule);
    vi_device_->logic_device_.destroyShaderModule(fragShaderModule);

}

void qe::edit::QuarkWindow::CreateUniformBuffer()
{
    vi_device_->CreateBuffer(
        vk::BufferUsageFlagBits::eUniformBuffer,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
        sizeof(UniformCameraBuffer),
        &ubo_buffer_,
        &ubo_buffer_memory_);

    vi_device_->CreateBuffer(
        vk::BufferUsageFlagBits::eUniformBuffer,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
        sizeof(UniformLightBuffer),
        &uld_buffer_,
        &uld_buffer_memory_);
}

void qe::edit::QuarkWindow::CreateDescriptorSet()
{
    
    std::array<vk::DescriptorPoolSize, 2> poolSizes = {};
    poolSizes[0].type = vk::DescriptorType::eUniformBuffer;
    poolSizes[0].descriptorCount = 1;

    poolSizes[1].type = vk::DescriptorType::eUniformBuffer;
    poolSizes[1].descriptorCount = 1;

    vk::DescriptorPoolCreateInfo poolInfo = {};
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = 1;
    
    VK_CHECK_RESULT(vi_device_->logic_device_.createDescriptorPool(&poolInfo, nullptr, &descriptor_set_pool_));

    vk::DescriptorSetLayout layouts[] = { descriptor_set_layout_ };
    vk::DescriptorSetAllocateInfo allocInfo = {};
    allocInfo.descriptorPool = descriptor_set_pool_;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = layouts;

    VK_CHECK_RESULT(vi_device_->logic_device_.allocateDescriptorSets(&allocInfo, &descriptor_set_));

    vk::DescriptorBufferInfo uboBufferInfo = {};
    uboBufferInfo.buffer = ubo_buffer_;
    uboBufferInfo.offset = 0;
    uboBufferInfo.range = sizeof(UniformCameraBuffer);

    vk::DescriptorBufferInfo uldBufferInfo = {};
    uldBufferInfo.buffer = uld_buffer_;
    uldBufferInfo.offset = 0;
    uldBufferInfo.range = sizeof(UniformLightBuffer);

    std::array<vk::WriteDescriptorSet, 2> descriptorWrites = {};

    descriptorWrites[0].dstSet = descriptor_set_;
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = vk::DescriptorType::eUniformBuffer;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &uboBufferInfo;

    descriptorWrites[1].dstSet = descriptor_set_;
    descriptorWrites[1].dstBinding = 1;
    descriptorWrites[1].dstArrayElement = 0;
    descriptorWrites[1].descriptorType = vk::DescriptorType::eUniformBuffer;
    descriptorWrites[1].descriptorCount = 1;
    descriptorWrites[1].pBufferInfo = &uldBufferInfo;

    vi_device_->logic_device_.updateDescriptorSets(static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);

}

void qe::edit::QuarkWindow::CreateCommandBuffer()
{
    command_buffers_.resize(vi_device_->swap_chain_frame_buffers_.size());

    vk::CommandBufferAllocateInfo allocInfo = {};
    allocInfo.commandPool = vi_device_->command_pool_;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t)command_buffers_.size();

    VK_CHECK_RESULT(vi_device_->logic_device_.allocateCommandBuffers(&allocInfo, command_buffers_.data()));

    for (size_t i = 0; i < command_buffers_.size(); i++) {
        vk::CommandBufferBeginInfo beginInfo = {};
        beginInfo.flags = vk::CommandBufferUsageFlagBits::eSimultaneousUse;

        command_buffers_[i].begin(&beginInfo);

        vk::RenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.renderPass = vi_device_->render_pass_;
        renderPassInfo.framebuffer = vi_device_->swap_chain_frame_buffers_[i];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = vi_device_->swap_chain_extent_;

        vk::ClearColorValue c_color;
        c_color.float32[0] = camera_->get_background_color()->get_r();
        c_color.float32[1] = camera_->get_background_color()->get_g();
        c_color.float32[2] = camera_->get_background_color()->get_b();
        c_color.float32[3] = camera_->get_background_color()->get_a();

        std::array<vk::ClearValue, 2> clearValues = {};
        clearValues[0].color = c_color;
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        command_buffers_[i].beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

        for (int index = 0; index < mesh_datas_.size(); index++) {

            command_buffers_[i].bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline_);

            vk::DeviceSize offsets[] = { 0 };
            command_buffers_[i].bindVertexBuffers(0, 1, &(mesh_datas_[index].vertex_buffer->buffer), offsets);

            command_buffers_[i].bindIndexBuffer(mesh_datas_[index].index_buffer->buffer, 0, vk::IndexType::eUint32);

            command_buffers_[i].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, pipeline_layout_, 0, 1, &descriptor_set_, 0, nullptr);

            glm::mat4 model = mesh_datas_[index].m;
            command_buffers_[i].pushConstants(pipeline_layout_, vk::ShaderStageFlagBits::eVertex, 0, sizeof(ModelMatrix), &model);

            command_buffers_[i].drawIndexed(static_cast<uint32_t>(mesh_datas_[index].indexs.size()), 1, 0, 0, 0);
        }

        command_buffers_[i].endRenderPass();

        command_buffers_[i].end();

    }

}

void qe::edit::QuarkWindow::Draw()
{
    uint32_t imageIndex;

    auto acquireResult = vi_device_->logic_device_.acquireNextImageKHR(
        vi_device_->swap_chain_,
        std::numeric_limits<uint64_t>::max(), 
        vi_device_->present_complete_semaphore_,
        vk::Fence(), 
        &imageIndex);

     if (acquireResult == vk::Result::eErrorOutOfDateKHR) {
        RecreateSwapChain();
        return;
    }
    else if (acquireResult != vk::Result::eSuccess && acquireResult != vk::Result::eSuboptimalKHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    vk::Semaphore waitSemaphores[] = { vi_device_->present_complete_semaphore_ };
    vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };

    vk::SubmitInfo submitInfo;
    submitInfo.setWaitSemaphoreCount(1);
    submitInfo.setPWaitSemaphores(waitSemaphores);
    submitInfo.setPWaitDstStageMask(waitStages);
    submitInfo.setCommandBufferCount(1);
    submitInfo.setPCommandBuffers(&command_buffers_[imageIndex]);

    vk::Semaphore signalSemaphores[] = { vi_device_->render_complete_semaphore_ };
    submitInfo.setSignalSemaphoreCount(1);
    submitInfo.setPSignalSemaphores(signalSemaphores);

    VK_CHECK_RESULT(vi_device_->queue_.submit(1, &submitInfo, vk::Fence()));

    vk::PresentInfoKHR presentInfo = {};
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &vi_device_->render_complete_semaphore_;

    vk::SwapchainKHR swapChains[] = { vi_device_->swap_chain_ };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    auto result = vi_device_->queue_.presentKHR(&presentInfo);

    if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR) {
        RecreateSwapChain();
    }
    else if (result != vk::Result::eSuccess) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    vi_device_->queue_.waitIdle();

}

void qe::edit::QuarkWindow::UpdateUniformBuffer()
{

    UniformCameraBuffer umo = {};
    umo.proj = camera_controller_->P();
    umo.view = camera_controller_->V();

    void* data;
    vi_device_->logic_device_.mapMemory(ubo_buffer_memory_, 0, sizeof(umo), vk::MemoryMapFlagBits(), &data);
    memcpy(data, &umo, sizeof(umo));
    vi_device_->logic_device_.unmapMemory(ubo_buffer_memory_);

    UniformLightBuffer ulb = {};
    ulb.lightDir = light_dir_;

    void* light_data;
    vi_device_->logic_device_.mapMemory(uld_buffer_memory_, 0, sizeof(ulb), vk::MemoryMapFlagBits(), &light_data);
    memcpy(light_data, &ulb, sizeof(ulb));
    vi_device_->logic_device_.unmapMemory(uld_buffer_memory_);
}

void qe::edit::QuarkWindow::RecreateSwapChain()
{
    vi_device_->logic_device_.waitIdle();

    CleanSwapChain();

    vi_device_->InitSwapChain();

    vi_device_->CreateRenderPass();

    vi_device_->CreateFrameBuffer();

    CreatePipeline();

    CreateCommandBuffer();
}

void qe::edit::QuarkWindow::CleanSwapChain()
{
    vi_device_->logic_device_.destroyImageView(vi_device_->frame_buffer_depth_image_view_);

    vi_device_->logic_device_.destroyImage(vi_device_->frame_buffer_depth_image_);

    vi_device_->logic_device_.freeMemory(vi_device_->frame_buffer_depth_image_memory_);

    for (int i = 0; i < vi_device_->swap_chain_frame_buffers_.size(); i++) {
        vi_device_->logic_device_.destroyFramebuffer(vi_device_->swap_chain_frame_buffers_[i]);
    }

    vi_device_->logic_device_.freeCommandBuffers(
        vi_device_->command_pool_,
        command_buffers_.size(),
        command_buffers_.data());

    vi_device_->logic_device_.destroyPipelineLayout(pipeline_layout_);

    vi_device_->logic_device_.destroyPipeline(pipeline_);

    vi_device_->logic_device_.destroyRenderPass(vi_device_->render_pass_);

    for (int i = 0; i < vi_device_->swap_chain_image_views_.size(); i++) {
        vi_device_->logic_device_.destroyImageView(vi_device_->swap_chain_image_views_[i]);
    }

    vi_device_->logic_device_.destroySwapchainKHR(vi_device_->swap_chain_);

}

void qe::edit::QuarkWindow::Awake()
{
    for (auto behaviour : behaviours_) {
        behaviour->Awake();
    }
}

void qe::edit::QuarkWindow::UpdateBehaviour()
{
    for (auto behaviour : behaviours_) {
        behaviour->Update();
    }
}

void qe::edit::QuarkWindow::LoadScene(const std::string & scene_path)
{
    auto file_name_splits = qe::core::QuarkString::Split(scene_path, "///");

    if (file_name_splits.size() < 2) return;

    ReleaseScene();

    auto camera_object = std::make_shared<qe::core::QuarkObject>();

    camera_ = camera_object->AddComponent<qe::core::Camera>();

    camera_->get_quark_object()->GetComponent<qe::core::Transform>()->set_world_translation(glm::vec3(0.0, 2.0, 6.0));

    camera_->set_background_color(qe::core::Color::Gray());

    camera_controller_ = camera_object->AddComponent<qe::core::CameraController>();

    behaviours_.push_back(camera_controller_);

    scene_ = std::make_shared<qe::core::Scene>();

    auto root = std::dynamic_pointer_cast<qe::core::QuarkObject>(resource_->Load(file_name_splits[1]));

    scene_->AddRoot(root);

    scene_->AddRoot(camera_object);

    LoadSceneReadyRender(scene_);

    Awake();

    CreateCommandBuffer();

    SetCameraAspect(this->geometry().width(), this->geometry().height());
}

void qe::edit::QuarkWindow::ReleaseScene()
{
    if (!scene_) return;

    ReleaseSceneData();
    ReleaseRenderData();
}

void qe::edit::QuarkWindow::ReleaseRenderData()
{
    vi_device_->logic_device_.freeCommandBuffers(
        vi_device_->command_pool_,
        command_buffers_.size(),
        command_buffers_.data());

    vi_device_->logic_device_.freeMemory(ubo_buffer_memory_);
    vi_device_->logic_device_.destroyBuffer(ubo_buffer_);

    vi_device_->logic_device_.freeMemory(uld_buffer_memory_);
    vi_device_->logic_device_.destroyBuffer(uld_buffer_);

    vi_device_->logic_device_.destroyPipelineLayout(pipeline_layout_);

    vi_device_->logic_device_.destroyPipeline(pipeline_);

    vi_device_->logic_device_.destroyDescriptorSetLayout(descriptor_set_layout_);

    vi_device_->logic_device_.destroyDescriptorPool(descriptor_set_pool_);
}

void qe::edit::QuarkWindow::ReleaseSceneData()
{
    mesh_datas_.swap(std::vector<meshData>());
    scene_.swap(std::shared_ptr<qe::core::Scene>());

    camera_controller_.swap(std::shared_ptr<qe::core::CameraController>());

    behaviours_.clear();

    frame_count_ = 0;
    fps_number_ = 0;

    fps_time_ = 0.0f;
    delta_time_ = 0.0f;
    key_press_time_ = 0.0f;

    is_update_material_ = false;
    right_button_press_ = false;
    right_button_press_ = false;
    key_press_ = false;
    init_mouse_pos_ = false;

    SetCameraAspect(this->geometry().width(), this->geometry().height());
}

bool qe::edit::QuarkWindow::event(QEvent * ev)
{
    switch (ev->type())
    {
    case QEvent::Resize:
    {
        resizeEvent((QResizeEvent*)ev);
        break;
    }
    case QEvent::MouseMove:
    {
        mouseMoveEvent((QMouseEvent*)ev);
        break;
    }
    case QEvent::MouseButtonPress:
    {
        mousePressEvent((QMouseEvent*)ev);
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        mouseReleaseEvent((QMouseEvent*)ev);
        break;
    }
    case QEvent::Wheel:
    {
        wheelEvent((QWheelEvent*)ev);
        break;
    }
    case QEvent::KeyPress:
    {
        keyPressEvent((QKeyEvent*)ev);
        break;
    }
    case QEvent::KeyRelease:
    {
        keyReleaseEvent((QKeyEvent*)ev);
        break;
    }
    case QEvent::Drop:
    {
        LoadScene(((QDragEnterEvent*)ev)->mimeData()->text().toStdString());
        break;
    }
    default:
        break;
    }

    return false;
}

void qe::edit::QuarkWindow::SetCameraAspect(const int & width, const int & height)
{
    if (height <= 0) return;

    if (!camera_controller_) return;

    auto camera = camera_controller_->get_camera();

    if (!camera) return;

    camera->set_rect(qe::core::Rect(0.0, 0.0, width, height));

    camera->set_aspect((float)width / height);

    if (!scene_) return;

    UpdateUniformBuffer();
}
