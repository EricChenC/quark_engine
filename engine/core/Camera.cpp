#include "Camera.h"

#include "RenderTexture.h"
#include "Color.h"
#include "Scene.h"
#include "Shader.h"
#include "QuarkObject.h"

// init static camera pointer list
std::list<qe::core::Camera*> qe::core::Camera::cameras;


qe::core::Camera::Camera()
    :transparency_sort_axis_(0, 0, 1)
{
    cameras.push_back(this);
}

qe::core::Camera::~Camera()
{
    auto result = std::find(cameras.begin(), cameras.end(), this);
    if (result != cameras.end()) {
        cameras.erase(result);
    }
}

auto qe::core::Camera::AllCamera() -> std::list<Camera*>
{
    return cameras;
}

auto qe::core::Camera::AllCameraCount() -> int
{
    return cameras.size();
}

auto qe::core::Camera::Current() -> Camera *
{
    return cameras.front();
}

auto qe::core::Camera::MainCamera() -> Camera *
{
    return cameras.front();
}

auto qe::core::Camera::get_allow_dynamic_resolution()  const -> const bool&
{
    return allow_dynamic_resolution_;
}

void qe::core::Camera::set_allow_dynamic_resolution(const bool & allow)
{
    allow_dynamic_resolution_ = allow;
}

auto qe::core::Camera::get_allow_hdr() const -> const bool&
{
    return allow_hdr_;
}

void qe::core::Camera::set_allow_hdr(const bool & allow)
{
    allow_hdr_ = allow;
}

auto qe::core::Camera::get_allow_msaa() const -> const bool &
{
    return allow_msaa_;
}

void qe::core::Camera::set_allow_msaa(const bool & allow)
{
    allow_msaa_ = allow;
}

auto qe::core::Camera::get_aspect() const -> const float&
{
    return aspect_;
}

void qe::core::Camera::set_aspect(const float & aspect)
{
    aspect_ = aspect;
}

auto qe::core::Camera::get_background_color() const ->const std::shared_ptr<Color>&
{
    return background_color_;
}

void qe::core::Camera::set_background_color(const std::shared_ptr<Color>& color)
{
    background_color_ = color;
}

auto qe::core::Camera::get_camera_type() const -> const CameraType &
{
    return camera_type_;
}

auto qe::core::Camera::set_camera_type(const CameraType & type)
{
    camera_type_ = type;
}

auto qe::core::Camera::get_clear_flags() const -> const ClearFlags &
{
    return clear_flags_;
}

void qe::core::Camera::set_clear_flags(const ClearFlags & flag)
{
    clear_flags_ = flag;
}

auto qe::core::Camera::get_culling_mask() const -> const int &
{
    return culling_mask_;
}

void qe::core::Camera::set_culling_mask(const int & mask)
{
    culling_mask_ = mask;
}

auto qe::core::Camera::get_culling_matrix() const -> const glm::mat4 &
{
    return culling_matrix_;
}

void qe::core::Camera::set_culling_matrix(const glm::mat4 & mat)
{
    culling_matrix_ = mat;
}

auto qe::core::Camera::get_depth() const -> const float &
{
    return depth_;
}

void qe::core::Camera::set_depth(const float & depth)
{
    depth_ = depth;
}

auto qe::core::Camera::get_near_clip_plane() const -> const float &
{
    return near_clip_plane_;
}

void qe::core::Camera::set_near_clip_plane(const float & near)
{
    near_clip_plane_ = near;
}

auto qe::core::Camera::get_far_clip_plane() const -> const float &
{
    return far_clip_plane_;
}

void qe::core::Camera::set_far_clip_plane(const float &far)
{
    far_clip_plane_ = far;
}

auto qe::core::Camera::get_field_of_view() const -> const float &
{
    return field_of_view_;
}

void qe::core::Camera::set_field_of_view(const float & fov)
{
    field_of_view_ = fov;
}

auto qe::core::Camera::get_use_ortho_graphic() const -> const bool &
{
    return ortho_graphic_;
}

void qe::core::Camera::set_use_ortho_graphic(const bool & ortho)
{
    ortho_graphic_ = ortho;
}

auto qe::core::Camera::get_ortho_graphic_size() const -> const float &
{
    return ortho_graphic_size_;
}

void qe::core::Camera::set_ortho_graphic_size(const float & size)
{
    ortho_graphic_size_ = size;
}

auto qe::core::Camera::get_pixel_x() const -> const int &
{
    return pixel_rect_.x;
}

void qe::core::Camera::set_pixel_x(const int & x)
{
    pixel_rect_.x = x;
}

auto qe::core::Camera::get_pixel_y() const -> const int &
{
    return pixel_rect_.y;
}

void qe::core::Camera::set_pixel_y(const int & y)
{
    pixel_rect_.y = y;
}

auto qe::core::Camera::get_pixel_width() const -> const int &
{
    return pixel_rect_.width;
}

void qe::core::Camera::set_pixel_width(const int & width)
{
    pixel_rect_.width = width;
}

auto qe::core::Camera::get_pixel_height() const -> const int &
{
    return pixel_rect_.height;
}

void qe::core::Camera::set_pixel_height(const int & height)
{
    pixel_rect_.height = height;
}

auto qe::core::Camera::get_pixel_rect() const -> const Rect &
{
    return pixel_rect_;
}

void qe::core::Camera::set_pixel_rect(const Rect & rect)
{
    pixel_rect_ = rect;
}

auto qe::core::Camera::get_rect() const -> const Rect &
{
    return rect_;
}

void qe::core::Camera::set_rect(const Rect & rect)
{
    rect_ = rect;
}

auto qe::core::Camera::get_target_display()const ->const int&
{
    return target_deisplay_;
}

void qe::core::Camera::set_target_display(const int & target)
{
    target_deisplay_ = target;
}

auto qe::core::Camera::get_target_texture() const -> const std::shared_ptr<RenderTexture>&
{
    return target_texture_;
}

void qe::core::Camera::set_target_texture(const std::shared_ptr<RenderTexture>& texture)
{
    target_texture_ = texture;
}

auto qe::core::Camera::get_transparency_sort_axis() const -> const glm::vec3 &
{
    return transparency_sort_axis_;
}

void qe::core::Camera::set_transparency_sort_axis(const glm::vec3 & axis)
{
    transparency_sort_axis_ = axis;
}

auto qe::core::Camera::get_transparency_sort_mode() const -> const TransparencySortMode &
{
    return transparency_sort_mode_;
}

void qe::core::Camera::set_transparency_sort_mode(const TransparencySortMode & mode)
{
    transparency_sort_mode_ = mode;
}

auto qe::core::Camera::get_use_occlusion_culling() const -> const bool &
{
    return use_occlusion_culling_;
}

void qe::core::Camera::set_use_occlusion_culling(const bool & use)
{
    use_occlusion_culling_ = use;
}

auto qe::core::Camera::get_use_physical_properties() const -> const bool &
{
    return use_physical_properties_;
}

void qe::core::Camera::set_use_physical_properties(const bool & use)
{
    use_physical_properties_ = use;
}

auto qe::core::Camera::get_velocity() const -> const glm::vec3 &
{
    return velocity_;
}

void qe::core::Camera::set_velocity(const glm::vec3 & velocity)
{
    velocity_ = velocity;
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
