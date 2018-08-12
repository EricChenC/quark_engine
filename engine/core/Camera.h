/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "Behaviour.h"
#include "CoreModule.h"

#include <glm/glm.hpp>
#include <list>

typedef void(*AwakeFP)();

namespace qe {
    namespace core {

        class RenderTexture;
        class Color;
        class Scene;
        class Shader;

        /// <summary>
        /// A Camera is a device through which the player views the world.  
        ///A screen space point is defined in pixels.The bottom - left of the screen is(0, 0); the right - top is(pixelWidth, pixelHeight).The z position is in world units from the Camera.  
        /// </summary>
        /// <seealso cref="Behaviour" />
        class DLL_EXPORT Camera : public Behaviour {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="Camera"/> class.
            /// </summary>
            explicit Camera();

            /// <summary>
            /// Finalizes an instance of the <see cref="Camera"/> class.
            /// </summary>
            ~Camera();


        public:
            enum class CameraType
            {
                GAME,
                SCENEVIEW,
                PREVIEW,
                VR,
                REFLECTION
            };

            enum class ClearFlags
            {
                SKYBOX,
                SOLIDCOLOR,
                DEPTH,
                NOTHING
            };

            enum class TransparencySortMode
            {
                DEFAULT,
                PERSPECTIVE,
                ORTHOGRAPHIC,
                CUSTOMAXIS
            };
            
        // static public
        public:

            /// <summary>
            /// Save the scene all cameras.
            /// </summary>
            static std::list<Camera*> cameras;

            /// <summary>
            /// Gets all enabled camera in scene.
            /// </summary>
            /// <returns></returns>
            static auto AllCamera()->std::list<Camera*>;

            /// <summary>
            /// The number of cameras in the current scene.
            /// </summary>
            /// <returns></returns>
            static auto AllCameraCount() -> int;


            /// <summary>
            /// The camera we are currently rendering with.
            /// </summary>
            /// <returns></returns>
            static auto Current()->Camera*;


            /// <summary>
            /// The first enabled camera tagged "MainCamera".
            /// </summary>
            /// <returns></returns>
            static auto MainCamera()->Camera*;

        // Properties
        public:
            /// <summary>
            /// Gets the allow dynamic resolution.
            /// </summary>
            /// <returns></returns>
            auto get_allow_dynamic_resolution() const -> const bool&;

            /// <summary>
            /// Sets the allow dynamic resolution.
            /// </summary>
            /// <param name="allow">The allow.</param>
            void set_allow_dynamic_resolution(const bool& allow);

            /// <summary>
            /// Gets the allow HDR.
            /// </summary>
            /// <returns></returns>
            auto get_allow_hdr() const -> const bool&;

            /// <summary>
            /// Sets the allow HDR.
            /// </summary>
            /// <param name="allow">The allow.</param>
            void set_allow_hdr(const bool& allow);

            /// <summary>
            /// Gets the allow msaa.
            /// </summary>
            /// <returns></returns>
            auto get_allow_msaa() const -> const bool&;

            /// <summary>
            /// Sets the allow msaa.
            /// </summary>
            /// <param name="allow">The allow.</param>
            void set_allow_msaa(const bool& allow);

            /// <summary>
            /// Gets the aspect.
            /// </summary>
            /// <returns></returns>
            auto get_aspect() const -> const float&;

            /// <summary>
            /// Sets the aspect.
            /// </summary>
            /// <param name="aspect">The aspect.</param>
            void set_aspect(const float& aspect);

            /// <summary>
            /// Gets the color of the background.
            /// </summary>
            /// <returns></returns>
            auto get_background_color() const ->const std::shared_ptr<Color>&;

            /// <summary>
            /// Sets the color of the background.
            /// </summary>
            /// <param name="color">The color.</param>
            void set_background_color(const std::shared_ptr<Color>& color);

            /// <summary>
            /// Gets the type of the camera.
            /// </summary>
            /// <returns></returns>
            auto get_camera_type() const ->const CameraType&;

            /// <summary>
            /// Sets the type of the camera.
            /// </summary>
            /// <param name="type">The type.</param>
            /// <returns></returns>
            auto set_camera_type(const CameraType& type);

            /// <summary>
            /// Gets the clear flags.
            /// </summary>
            /// <returns></returns>
            auto get_clear_flags() const ->const ClearFlags&;

            /// <summary>
            /// Sets the clear flags.
            /// </summary>
            /// <param name="flag">The flag.</param>
            void set_clear_flags(const ClearFlags& flag);

            /// <summary>
            /// Gets the culling mask.
            /// </summary>
            /// <returns></returns>
            auto get_culling_mask() const ->const int&;

            /// <summary>
            /// Sets the culling mask.
            /// </summary>
            /// <param name="mask">The mask.</param>
            void set_culling_mask(const int& mask);

            /// <summary>
            /// Gets the culling matrix.
            /// </summary>
            /// <returns></returns>
            auto get_culling_matrix() const->const glm::mat4&;

            /// <summary>
            /// Sets the culling matrix.
            /// </summary>
            /// <param name="mat">The mat.</param>
            void set_culling_matrix(const glm::mat4& mat);

            /// <summary>
            /// Gets the depth.
            /// </summary>
            /// <returns></returns>
            auto get_depth() const ->const float&;

            /// <summary>
            /// Sets the depth.
            /// </summary>
            /// <param name="depth">The depth.</param>
            void set_depth(const float& depth);

            /// <summary>
            /// Gets the near clip plane.
            /// </summary>
            /// <returns></returns>
            auto get_near_clip_plane() const -> const float&;

            /// <summary>
            /// Sets the near clip plane.
            /// </summary>
            /// <param name="">The .</param>
            void set_near_clip_plane(const float& near);

            /// <summary>
            /// Gets the far clip plane.
            /// </summary>
            /// <returns></returns>
            auto get_far_clip_plane() const ->const float&;

            /// <summary>
            /// Sets the far clip plane.
            /// </summary>
            /// <param name="">The .</param>
            void set_far_clip_plane(const float& far);

            /// <summary>
            /// Fields the of view (fov).
            /// </summary>
            /// <returns></returns>
            auto get_field_of_view() const ->const float&;

            /// <summary>
            /// Sets the field of view.
            /// </summary>
            /// <param name="fov">The fov.</param>
            void set_field_of_view(const float& fov);

            /// <summary>
            /// Gets the use ortho graphic.
            /// </summary>
            /// <returns></returns>
            auto get_use_ortho_graphic() const ->const bool&;

            /// <summary>
            /// Sets the use ortho graphic.
            /// </summary>
            /// <param name="ortho">The ortho.</param>
            void set_use_ortho_graphic(const bool& ortho);

            /// <summary>
            /// Gets the size of the ortho graphic.
            /// </summary>
            /// <returns></returns>
            auto get_ortho_graphic_size() const ->const float&;

            /// <summary>
            /// Sets the size of the ortho graphic.
            /// </summary>
            /// <param name="size">The size.</param>
            void set_ortho_graphic_size(const float& size);

            /// <summary>
            /// Gets the pixel x.
            /// </summary>
            /// <returns></returns>
            auto get_pixel_x() const ->const int&;

            /// <summary>
            /// Sets the pixel x.
            /// </summary>
            /// <param name="x">The x.</param>
            void set_pixel_x(const int& x);

            /// <summary>
            /// Gets the pixel y.
            /// </summary>
            /// <returns></returns>
            auto get_pixel_y() const ->const int&;

            /// <summary>
            /// Sets the pixel y.
            /// </summary>
            /// <param name="y">The y.</param>
            void set_pixel_y(const int& y);

            /// <summary>
            /// Gets the width of the pixel.
            /// </summary>
            /// <returns></returns>
            auto get_pixel_width() const ->const int&;

            /// <summary>
            /// Sets the width of the pixel.
            /// </summary>
            /// <param name="width">The width.</param>
            void set_pixel_width(const int& width);

            /// <summary>
            /// Gets the height of the pixel.
            /// </summary>
            /// <returns></returns>
            auto get_pixel_height() const ->const int&;

            /// <summary>
            /// Sets the height of the pixel.
            /// </summary>
            /// <param name="height">The height.</param>
            void set_pixel_height(const int& height);

            /// <summary>
            /// Gets the pixel rect.
            /// </summary>
            /// <returns></returns>
            auto get_pixel_rect() const ->const Rect&;

            /// <summary>
            /// Sets the pixel rect.
            /// </summary>
            /// <param name="rect">The rect.</param>
            void set_pixel_rect(const Rect& rect);

            /// <summary>
            /// Gets the rect.
            /// </summary>
            /// <returns></returns>
            auto get_rect() const->const Rect&;

            /// <summary>
            /// Sets the rect.
            /// </summary>
            /// <param name="rect">The rect.</param>
            void set_rect(const Rect& rect);

            /// <summary>
            /// Gets the target display.
            /// </summary>
            /// <returns></returns>
            auto get_target_display()const ->const int&;

            /// <summary>
            /// Sets the target display.
            /// </summary>
            /// <param name="target">The target.</param>
            void set_target_display(const int& target);

            /// <summary>
            /// Gets the target texture.
            /// </summary>
            /// <returns></returns>
            auto get_target_texture() const -> const std::shared_ptr<RenderTexture>&;

            /// <summary>
            /// Sets the target texture.
            /// </summary>
            /// <param name="texture">The texture.</param>
            void set_target_texture(const std::shared_ptr<RenderTexture>& texture);

            /// <summary>
            /// Gets the transparency sort axis.
            /// </summary>
            /// <returns></returns>
            auto get_transparency_sort_axis() const ->const glm::vec3&;

            /// <summary>
            /// Sets the transparency sort axis.
            /// </summary>
            /// <param name="axis">The axis.</param>
            void set_transparency_sort_axis(const glm::vec3& axis);

            /// <summary>
            /// Gets the transparency sort mode.
            /// </summary>
            /// <returns></returns>
            auto get_transparency_sort_mode() const -> const TransparencySortMode&;

            /// <summary>
            /// Sets the transparency sort mode.
            /// </summary>
            /// <param name="mode">The mode.</param>
            void set_transparency_sort_mode(const TransparencySortMode& mode);

            /// <summary>
            /// Gets the use occlusion culling.
            /// </summary>
            /// <returns></returns>
            auto get_use_occlusion_culling() const -> const bool&;

            /// <summary>
            /// Sets the use occlusion culling.
            /// </summary>
            /// <param name="use">The use.</param>
            void set_use_occlusion_culling(const bool& use);

            /// <summary>
            /// Gets the use physical properties.
            /// </summary>
            /// <returns></returns>
            auto get_use_physical_properties() const ->const bool&;

            /// <summary>
            /// Sets the use physical properties.
            /// </summary>
            /// <param name="use">The use.</param>
            void set_use_physical_properties(const bool& use);

            /// <summary>
            /// Gets the velocity.
            /// </summary>
            /// <returns></returns>
            auto get_velocity() const->const glm::vec3&;

            /// <summary>
            /// Sets the velocity.
            /// </summary>
            /// <param name="velocity">The velocity.</param>
            void set_velocity(const glm::vec3& velocity);

        // Methods
        public:
            /// <summary>
            /// Gets the temporary RenderTexture target for this Camera.
            /// </summary>
            /// <returns></returns>
            auto ActiveTexture()->std::shared_ptr<RenderTexture>;

            /// <summary>
            /// Cameras to world matrix.
            /// </summary>
            /// <returns></returns>
            auto CameraToWorldMatrix() const->glm::mat4;

            /// <summary>
            /// Worlds to camera matrix.
            /// </summary>
            /// <returns></returns>
            auto WorldToCameraMatrix() const->glm::mat4;

            /// <summary>
            /// Scenes this instance.
            /// </summary>
            /// <returns></returns>
            auto Scene()->Scene*;

            /// <summary>
            /// Renders this instance.
            /// </summary>
            void Render();

            /// <summary>
            /// Renders the with shader.
            /// </summary>
            /// <param name="shader">The shader.</param>
            void RenderWithShader(std::shared_ptr<Shader> shader);

            /// <summary>
            /// Revert all camera parameters to default.
            /// </summary>
            void Reset();

            /// <summary>
            /// Screens the point to ray.
            /// </summary>
            /// <param name="pos">The position.</param>
            /// <returns></returns>
            auto ScreenPointToRay(const glm::vec3& pos)->Ray;

        private:
            std::list<AwakeFP> awake_functions_;

        private:
            /// <summary>
            /// The whether allow dynamic resolution
            /// </summary>
            bool allow_dynamic_resolution_;

            /// <summary>
            /// The whether allow HDR
            /// </summary>
            bool allow_hdr_;

            /// <summary>
            /// The whether allow msaa
            /// </summary>
            bool allow_msaa_;

            /// <summary>
            /// The whether ortho graphic
            /// </summary>
            bool ortho_graphic_;

            /// <summary>
            /// The ortho graphic size
            /// </summary>
            float ortho_graphic_size_;

            /// <summary>
            /// The whether use occlusion culling
            /// </summary>
            bool use_occlusion_culling_;

            /// <summary>
            /// The whether use physical properties
            /// </summary>
            bool use_physical_properties_;

            /// <summary>
            /// The aspect
            /// </summary>
            float aspect_;

            /// <summary>
            /// The depth
            /// </summary>
            float depth_;

            /// <summary>
            /// The near clip plane
            /// </summary>
            float near_clip_plane_;

            /// <summary>
            /// The far clip plane
            /// </summary>
            float far_clip_plane_;

            /// <summary>
            /// The field of view
            /// </summary>
            float field_of_view_;


            /// <summary>
            /// The culling mask
            /// </summary>
            int culling_mask_;

            /// <summary>
            /// The pixel rect in pixel coordinate
            /// </summary>
            Rect pixel_rect_;

            /// <summary>
            /// The rect of camera in normalized coordinate
            /// </summary>
            Rect rect_;

            /// <summary>
            /// The target deisplay
            /// </summary>
            int target_deisplay_;


            /// <summary>
            /// The background color of camera
            /// </summary>
            std::shared_ptr<Color> background_color_;

            /// <summary>
            /// The camera type
            /// </summary>
            CameraType camera_type_;

            /// <summary>
            /// The clear flags
            /// </summary>
            ClearFlags clear_flags_;

            /// <summary>
            /// The culling matrix
            /// </summary>
            glm::mat4 culling_matrix_;

            /// <summary>
            /// The target texture of camera
            /// </summary>
            std::shared_ptr<RenderTexture> target_texture_;

            /// <summary>
            /// The transparency sort axis
            /// </summary>
            glm::vec3 transparency_sort_axis_;

            /// <summary>
            /// The velocity of camera
            /// </summary>
            glm::vec3 velocity_;

            /// <summary>
            /// The transparency sort mode
            /// </summary>
            TransparencySortMode transparency_sort_mode_;


        };
    }
}