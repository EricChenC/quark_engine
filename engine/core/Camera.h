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

            auto Scene()->std::shared_ptr<Scene>;

            auto TargetDisplay()->int;

            auto TargetTexture()->std::shared_ptr<RenderTexture>;

            auto TransparencySortAxis()->glm::vec3;

            auto GetTransparencySortMode()->TransparencySortMode;

            auto UseOcclusionCulling() -> bool;

            auto UsePhysicalProperties() -> bool;

            auto Velocity()->glm::vec3;

            auto WorldToCameraMatrix()->glm::mat4;

        // Methods
        public:
            void Render();

            void RenderWithShader(std::shared_ptr<Shader> shader);

            void Reset();

            auto ScreenPointToRay(const glm::vec3& pos) -> Ray;


        private:
            bool allow_dynamic_resolution_;
            bool allow_hdr_;
            bool allow_msaa_;
            bool ortho_graphic_;
            bool allow_dynamic_resolution_;
            bool allow_dynamic_resolution_;
            bool allow_dynamic_resolution_;
            bool allow_dynamic_resolution_;
            bool allow_dynamic_resolution_;


            float aspect_;

            float depth_;

            float far_clip_plane_;

            float field_of_view_;

            std::shared_ptr<Color> background_color_;

            CameraType camera_type_;

            ClearFlags clear_flags_;

            int culling_mask_;

            int pixel_height_;

            glm::mat4 culling_matrix_;

            glm::vec2 rect_;


        };
    }
}