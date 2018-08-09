#include "Camera.h"

#include "RenderTexture.h"
#include "Color.h"
#include "Scene.h"
#include "Shader.h"
#include "QuarkObject.h"

// init static camera pointer list
std::list<qe::core::Camera*> qe::core::Camera::cameras_;


qe::core::Camera::Camera()
    :transparency_sort_axis_(0, 0, 1)
{
    cameras_.push_back(this);
}

qe::core::Camera::~Camera()
{
    auto result = std::find(cameras_.begin(), cameras_.end(), this);
    if (result != cameras_.end()) {
        cameras_.erase(result);
    }
}

auto qe::core::Camera::get_all_camera() -> std::list<Camera*>
{
    return cameras_;
}

auto qe::core::Camera::get_all_camera_count() -> int
{
    return cameras_.size();
}

auto qe::core::Camera::current() -> Camera *
{
    return cameras_.front();
}

auto qe::core::Camera::main() -> Camera *
{
    return cameras_.front();
}

auto qe::core::Camera::ActiveTexture() -> std::shared_ptr<RenderTexture>
{
    return std::shared_ptr<RenderTexture>();
}

auto qe::core::Camera::AllowDynamicResolution() -> bool
{
    return false;
}

auto qe::core::Camera::AllowHDR() -> bool
{
    return false;
}

auto qe::core::Camera::AllowMSAA() -> bool
{
    return false;
}

auto qe::core::Camera::Aspect() -> float
{
    return 0.0f;
}

auto qe::core::Camera::GetBackgroundColor() -> std::shared_ptr<Color>
{
    return background_color_;
}

void qe::core::Camera::SetBackgroundColor(std::shared_ptr<Color> color)
{
    background_color_ = color;
}

auto qe::core::Camera::GetCameraToWorldMatrix() -> glm::mat4
{
    return glm::mat4();
}

auto qe::core::Camera::GetCameraType() -> qe::core::Camera::CameraType
{
    return camera_type_;
}

auto qe::core::Camera::GetClearFlags() -> qe::core::Camera::ClearFlags
{
    return clear_flags_;
}

auto qe::core::Camera::GetCullingMask() -> int
{
    return culling_mask_;
}

void qe::core::Camera::SetCullingMask(const int & mask)
{
    culling_mask_ = mask;
}

auto qe::core::Camera::GetCullingMatrix() -> glm::mat4
{
    return culling_matrix_;
}

void qe::core::Camera::SetCullingMatrix(const glm::mat4 & mat)
{
    culling_matrix_ = mat;
}

auto qe::core::Camera::Depth() -> float
{
    return depth_;
}

auto qe::core::Camera::FarClipPlane() -> float
{
    return far_clip_plane_;
}

auto qe::core::Camera::FieldOfView() -> float
{
    return field_of_view_;
}

auto qe::core::Camera::OrthoGraphic() -> bool
{
    return ortho_graphic_;
}

auto qe::core::Camera::PixelHeight() -> int
{
    return pixel_height_;
}

auto qe::core::Camera::Rect() -> glm::vec2
{
    return rect_;
}

auto qe::core::Camera::Scene() -> qe::core::Scene*
{
    return get_quark_object()->get_scene();
}

auto qe::core::Camera::GetTargetDisplay() -> int
{
    return target_deisplay_;
}

void qe::core::Camera::SetTargetDisplay(const int & target)
{
    target_deisplay_ = target;
}

auto qe::core::Camera::GetTargetTexture() -> std::shared_ptr<RenderTexture>
{
    return target_texture_;
}

void qe::core::Camera::SetTargetTexture(std::shared_ptr<RenderTexture> texture)
{
    target_texture_ = texture;
}

auto qe::core::Camera::GetTransparencySortAxis() -> glm::vec3
{
    return transparency_sort_axis_;
}

void qe::core::Camera::SetTransparencySortAxis(const glm::vec3 & axis)
{
    transparency_sort_axis_ = axis;
}

auto qe::core::Camera::GetTransparencySortMode() -> qe::core::Camera::TransparencySortMode
{
    return transparency_sort_mode_;
}

void qe::core::Camera::SetTransparencySortMode(const TransparencySortMode & mode)
{
    transparency_sort_mode_ = mode;
}

auto qe::core::Camera::UseOcclusionCulling() -> bool
{
    return use_occlusion_culling_;
}

void qe::core::Camera::SetUseOcclusionCulling(bool use)
{
    use_occlusion_culling_ = use;
}

auto qe::core::Camera::UsePhysicalProperties() -> bool
{
    return use_physical_properties_;
}

void qe::core::Camera::SetUsePhysicalProperties(bool use)
{
    use_physical_properties_ = use;
}

auto qe::core::Camera::GetVelocity() -> glm::vec3
{
    return velocity_;
}

void qe::core::Camera::SetVelocity(const glm::vec3 & velocity)
{
    velocity_ = velocity;
}

auto qe::core::Camera::WorldToCameraMatrix() -> glm::mat4
{
    return glm::mat4();
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
