/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 8/26/2018 9:08:21 AM
/// author: eric
/// class description ....

#pragma once

#include <string>

namespace qe {
    namespace edit
    {
        /// <summary>
        /// build platform
        /// </summary>
        enum class BuildPlatform {
            NONE,
            WINDOWS,
            MAC,
            LINUX,
            IPHONE,
            ANDROID
        };

        class Platform
        {
            //properties
        public:
            /// <summary>
            /// Gets the platform path.
            /// </summary>
            /// <returns></returns>
            static auto get_platform_path() -> std::string {
                switch (build_platform_)
                {
                case qe::edit::BuildPlatform::NONE:
                    return "./../../media/";
                    break;
                case qe::edit::BuildPlatform::WINDOWS:
                    return "D:/project/quark_engine/media/";
                    break;
                case qe::edit::BuildPlatform::MAC:
                    return "D:/project/quark_engine/media/";
                    break;
                case qe::edit::BuildPlatform::LINUX:
                    return "D:/project/quark_engine/media/";
                    break;
                case qe::edit::BuildPlatform::IPHONE:
                    return "D:/project/quark_engine/media/";
                    break;
                case qe::edit::BuildPlatform::ANDROID:
                    return "D:/project/quark_engine/media/";
                    break;
                }
            }

            /// <summary>
            /// Gets the platform.
            /// </summary>
            /// <returns></returns>
            inline static auto get_platform() -> const BuildPlatform& { return build_platform_; }

            /// <summary>
            /// Sets the platform.
            /// </summary>
            /// <param name="platform">The platform.</param>
            inline static auto set_platform(const BuildPlatform& platform) { build_platform_ = platform; }

        private:
            static BuildPlatform build_platform_;

        }; 
    }
}



