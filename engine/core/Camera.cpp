#include "Camera.h"

#include "RenderTexture.h"
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
