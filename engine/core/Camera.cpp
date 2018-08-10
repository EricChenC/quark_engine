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

auto qe::core::Camera::GetAspect() -> float
{
    return aspect_;
}

void qe::core::Camera::SetAspect(const float & aspect)
{
    aspect_ = aspect;
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

auto qe::core::Camera::GetDepth() -> float
{
    return depth_;
}

void qe::core::Camera::SetDepth(const float & depth)
{
    depth_ = depth;
}

auto qe::core::Camera::GetNearClipPlane() -> float
{
    return near_clip_plane_;
}

void qe::core::Camera::SetNearClipPlane(const float &near)
{
    near_clip_plane_ = near;
}

auto qe::core::Camera::GetFarClipPlane() -> float
{
    return far_clip_plane_;
}

void qe::core::Camera::SetFarClipPlane(const float &far)
{
    far_clip_plane_ = far;
}

auto qe::core::Camera::GetFieldOfView() -> float
{
    return field_of_view_;
}

void qe::core::Camera::SetFieldOfView(const float & fov)
{
    field_of_view_ = fov;
}

auto qe::core::Camera::UseOrthoGraphic() -> bool
{
    return ortho_graphic_;
}

void qe::core::Camera::SetUseOrthoGraphic(bool ortho)
{
    ortho_graphic_ = ortho;
}

auto qe::core::Camera::GetOrthoGraphicSize() -> float
{
    return ortho_graphic_size_;
}

void qe::core::Camera::SetOrthoGraphicSize(const float & size)
{
    ortho_graphic_size_ = size;
}

auto qe::core::Camera::PixelHeight() -> int
{
    return pixel_height_;
}

auto qe::core::Camera::GetRect() -> Rect
{
    return rect_;
}

void qe::core::Camera::SetRect(const Rect & rect)
{
    rect_ = rect;
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
