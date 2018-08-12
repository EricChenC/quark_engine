/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric

#pragma once

#include "CoreObject.h"

#include <glm/glm.hpp>

namespace qe {
    namespace core {
        class DLL_EXPORT Texture : public CoreObject {
        public:
            enum class Type
            {
                T2D,
                T2DARRAY,
                TCUBEMAP
            };

        public:
            explicit Texture();
            ~Texture();

        // properties
        public:

            /// <summary>
            /// Gets the width.
            /// </summary>
            /// <returns></returns>
            inline auto get_width()const -> const uint32_t& { return width_; }

            /// <summary>
            /// Sets the width.
            /// </summary>
            /// <param name="width">The width.</param>
            inline void set_width(const uint32_t& width) { width_ = width; }

            /// <summary>
            /// Gets the height.
            /// </summary>
            /// <returns></returns>
            inline auto get_height()const -> const uint32_t& { return height_; }

            /// <summary>
            /// Sets the height.
            /// </summary>
            /// <param name="height">The height.</param>
            inline void set_height(const uint32_t& height) { height_ = height; }

            /// <summary>
            /// Gets the channel.
            /// </summary>
            /// <returns></returns>
            inline auto get_channel()const -> const int& { return channel_; }

            /// <summary>
            /// Sets the channel.
            /// </summary>
            /// <param name="channel">The channel.</param>
            inline void set_channel(const int& channel) { channel_ = channel; }

            /// <summary>
            /// Gets the data.
            /// </summary>
            /// <returns></returns>
            inline auto get_data()const -> const void* { return data_; }

            /// <summary>
            /// Sets the data.
            /// </summary>
            /// <param name="data">The data.</param>
            inline void set_data(void* data) { data_ = data; }

            /// <summary>
            /// Gets the mip level.
            /// </summary>
            /// <returns></returns>
            inline auto get_mip_level()const -> const uint32_t& { return mip_levels_; }

            /// <summary>
            /// Sets the mip level.
            /// </summary>
            /// <param name="mip_level">The mip level.</param>
            inline void set_mip_level(const uint32_t& mip_level) { mip_levels_ = mip_level; }
          
            /// <summary>
            /// Gets the layer count.
            /// </summary>
            /// <returns></returns>
            inline auto get_layer_count()const -> const uint32_t& { return layer_count_; }

            /// <summary>
            /// Sets the layer count.
            /// </summary>
            /// <param name="layer_count">The layer count.</param>
            inline void set_layer_count(const uint32_t& layer_count) { layer_count_ = layer_count; }
           
            /// <summary>
            /// Gets the size.
            /// </summary>
            /// <returns></returns>
            inline auto get_size()const -> const size_t& { return size_; }

            /// <summary>
            /// Sets the size.
            /// </summary>
            /// <param name="size">The size.</param>
            inline void set_size(const size_t& size) { size_ = size; }

            /// <summary>
            /// Gets the type.
            /// </summary>
            /// <returns></returns>
            inline auto get_type()const -> const Type& { return type_; }

            /// <summary>
            /// Sets the type.
            /// </summary>
            /// <param name="type">The type.</param>
            inline void set_type(Type type) { type_ = type; }
           

        private:
            uint32_t width_;
            uint32_t height_;
            int channel_;
            void* data_;
            uint32_t mip_levels_;
            uint32_t layer_count_;

            size_t size_;
            Type type_;

        };
    }
}

