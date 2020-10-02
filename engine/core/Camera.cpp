#include "Camera.h"

#include "RenderTexture.h"
#include "Scene.h"
#include "Shader.h"
#include "QuarkObject.h"

// init static camera pointer list
std::list<qe::core::Camera*> qe::core::Camera::cameras_;


qe::core::Camera::Camera()
    :allow_dynamic_resolution_(false)
    , allow_hdr_(false)
    , allow_msaa_(false)
    , ortho_graphic_(false)
    , ortho_graphic_size_(1.0f)
    , use_occlusion_culling_(false)
    , use_physical_properties_(false)
    , aspect_(1.0f)
    , depth_(1.0f)
    , near_clip_plane_(1.0f)
    , far_clip_plane_(1000.0f)
    , field_of_view_(45.0f)
    , culling_mask_(1.0f)
    , pixel_rect_(0.0f, 0.0f, 800.0f, 600.0f)
    , rect_(0.0f, 0.0f, 800.0f, 600.0f)
    , target_deisplay_(0)
    , background_color_(nullptr)
    , camera_type_(CameraType::SCENEVIEW)
    , clear_flags_(ClearFlags::SOLIDCOLOR)
    , culling_matrix_(1.0f)
    , transparency_sort_axis_(0, 0, 1)
    , velocity_(1.0f)
    , transparency_sort_mode_(TransparencySortMode::DEFAULT)
{
    target_texture_ = std::make_shared<RenderTexture>();
    cameras_.push_back(this);
}

qe::core::Camera::~Camera()
{
    auto result = std::find(cameras_.begin(), cameras_.end(), this);
    if (result != cameras_.end()) {
        cameras_.erase(result);
    }
}

auto qe::core::Camera::AllCamera() -> std::list<Camera*>
{
    return cameras_;
}

auto qe::core::Camera::AllCameraCount() -> int
{
    return cameras_.size();
}

auto qe::core::Camera::Current() -> Camera *
{
    return cameras_.front();
}

auto qe::core::Camera::MainCamera() -> Camera *
{
    return cameras_.front();
}

auto qe::core::Camera::ActiveTexture() -> std::shared_ptr<RenderTexture>
{
    return std::shared_ptr<RenderTexture>();
}

auto qe::core::Camera::CameraToWorldMatrix() const -> glm::mat4
{
    return glm::mat4();
}

auto qe::core::Camera::WorldToCameraMatrix() const -> glm::mat4
{
    return glm::mat4();
}

auto qe::core::Camera::Scene() -> qe::core::Scene *
{
    return get_quark_object()->get_scene();
}

void qe::core::Camera::Render()
{

}

void qe::core::Camera::RenderWithShader(std::shared_ptr<Shader> shader)
{

}

void qe::core::Camera::Reset()
{

}

auto qe::core::Camera::ScreenPointToRay(const glm::vec3 & pos) -> Ray
{
    return Ray();
}
