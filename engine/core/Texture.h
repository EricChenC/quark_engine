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

            void set_width(const uint32_t& width);
            void set_height(const uint32_t& height);
            void set_channel(const int& channel);
            void set_data(void* data);
            void set_mip_level(const uint32_t& mip_level);
            void set_layer_count(const uint32_t& layer_count);
            void set_size(const size_t& size);
            void set_type(Type type);

            uint32_t get_width();
            uint32_t get_height();
            int get_channel();
            void* get_data();
            uint32_t get_mip_level();
            uint32_t get_layer_count();
            size_t get_size();
            Type get_type();

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

