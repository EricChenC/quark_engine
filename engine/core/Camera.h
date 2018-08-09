/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "Behaviour.h"
#include "CoreModule.h"

#include <glm/glm.hpp>
#include <list>

namespace qe {
    namespace core {

        class RenderTexture;
        class Color;
        class Scene;
        class Shader;

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
            static std::list<Camera*> cameras_;

            /// <summary>
            /// Gets all enabled camera in scene.
            /// </summary>
            /// <returns></returns>
            static auto get_all_camera()->std::list<Camera*>;

            /// <summary>
            /// The number of cameras in the current scene.
            /// </summary>
            /// <returns></returns>
            static auto get_all_camera_count() -> int;


            /// <summary>
            /// The camera we are currently rendering with.
            /// </summary>
            /// <returns></returns>
            static auto current()->Camera*;


            /// <summary>
            /// The first enabled camera tagged "MainCamera".
            /// </summary>
            /// <returns></returns>
            static auto main()->Camera*;

        // Properties
        public:
            auto ActiveTexture()->std::shared_ptr<RenderTexture>;

            auto AllowDynamicResolution() -> bool;

            auto AllowHDR() -> bool;

            auto AllowMSAA() -> bool;

            auto Aspect() -> float;

            auto GetBackgroundColor()->std::shared_ptr<Color>;

            void SetBackgroundColor(std::shared_ptr<Color> color);

            auto GetCameraToWorldMatrix()->glm::mat4;
       
            auto GetCameraType()->CameraType;

            auto GetClearFlags()->ClearFlags;

            auto GetCullingMask()->int;

            void SetCullingMask(const int& mask);

            auto GetCullingMatrix()->glm::mat4;

            void SetCullingMatrix(const glm::mat4& mat);

            auto Depth() -> float;

            auto FarClipPlane() -> float;

            auto FieldOfView() -> float;

            auto OrthoGraphic() -> bool;

            auto PixelHeight() -> int;

            auto Rect()->glm::vec2;

            auto Scene()->Scene*;

            auto GetTargetDisplay()->int;

            void SetTargetDisplay(const int& target);

            auto GetTargetTexture()->std::shared_ptr<RenderTexture>;

            void SetTargetTexture(std::shared_ptr<RenderTexture> texture);

            auto GetTransparencySortAxis()->glm::vec3;

            void SetTransparencySortAxis(const glm::vec3& axis);

            auto GetTransparencySortMode()->TransparencySortMode;

            void SetTransparencySortMode(const TransparencySortMode& mode);

            auto UseOcclusionCulling() -> bool;

            void SetUseOcclusionCulling(bool use);

            auto UsePhysicalProperties() -> bool;

            void SetUsePhysicalProperties(bool use);

            auto GetVelocity()->glm::vec3;

            void SetVelocity(const glm::vec3& velocity);

            auto WorldToCameraMatrix()->glm::mat4;

        // Methods
        public:
            void Render();

            void RenderWithShader(std::shared_ptr<Shader> shader);

            void Reset();

            auto ScreenPointToRay(const glm::vec3& pos) -> Ray;


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
            /// The pixel height
            /// </summary>
            int pixel_height_;

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
            /// The rect of camera
            /// </summary>
            glm::vec2 rect_;

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