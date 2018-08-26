/// Copyright 2018 Stone, Inc. All Rights Reserved.
/// create time: 6/8/2018 11:06:18 PM
/// author: eric
#pragma once

#include "Behaviour.h"

#include <list>

namespace qe {
    namespace core {

        struct Color;
        class Texture;

        class DLL_EXPORT Light : public Behaviour {
        public:
            enum class LightType
            {
                SPOT,
                DIRECTIONAL,
                POINT,
                AREA
            };

            enum class LightShadows
            {
                NONE,
                HARD,
                SOFT
            };

        public:
            explicit Light();
            ~Light();

            // properties
        public:
            inline auto get_area_size() const -> const glm::vec2& { return area_size_; }

            inline auto set_area_size(const glm::vec2& size) { area_size_ = size; }

            inline auto get_baking_output() const -> const LightBakingOutput& { return baking_output_; }

            inline auto set_baking_output(const LightBakingOutput& output) { baking_output_ = output; }

            inline auto get_bounce_intensity() const -> const float& { return bounce_intensity_; }

            inline auto set_bounce_intensity(const float& intensity) { bounce_intensity_ = intensity; }

            inline auto get_color() const -> const std::shared_ptr<Color>& { return color_; }

            inline auto set_color(const std::shared_ptr<Color>& color) { color_ = color; }

            inline auto get_color_temperature() const -> const float& { return color_temperature_; }

            inline auto set_color_temperature(const float& temperature) { color_temperature_ = temperature; }

            inline auto get_cookie() const -> const std::shared_ptr<Texture>& { return cookie_; }

            inline auto set_cookie(const std::shared_ptr<Texture>& cookie) { cookie_ = cookie; }

            inline auto get_cookie_size() const -> const float& { return cookie_size_; }

            inline auto set_cookie_size(const float& size) { cookie_size_ = size; }

            inline auto get_culling_mask() const -> const int& { return culling_mask_; }

            inline auto set_culling_mask(const int& mask) { culling_mask_ = mask; }

            inline auto get_intensity() const -> const float& { return intensity_; }

            inline auto set_intensity(const float& intensity) { intensity_ = intensity; }

            inline auto get_layer_shadow_cull_distances() const -> const std::list<float> { return layer_shadow_cull_distances_; }

            inline auto set_layer_shadow_cull_distances(const std::list<float> distances) { layer_shadow_cull_distances_ = distances; }

            inline auto get_lightmap_back_type() const -> const LightmapBakeType& { return lightmap_back_type_; }

            inline auto set_lightmap_back_type(const LightmapBakeType& type) { lightmap_back_type_ = type; }

            inline auto get_light_shadow_caster_mode() const -> const LightShadowCasterMode& { return light_shadow_caster_mode_; }

            inline auto set_light_shadow_caster_mode(const LightShadowCasterMode& mode) { light_shadow_caster_mode_ = mode; }

            inline auto get_range() const -> const float& { return range_; }

            inline auto set_range(const float& range) { range_ = range; }

            inline auto get_render_mode() const -> const LightRenderMode& { return render_mode_; }

            inline auto set_render_mode(const LightRenderMode& mode) { render_mode_ = mode; }

            inline auto get_shadow_angle() const -> const float& { return shadow_angle_; }

            inline auto set_shadow_angle(const float& angle) { shadow_angle_ = angle; }

            inline auto get_shadow_bias() const -> const float& { return shadow_bias_; }

            inline auto set_shadow_bias(const float& bias) { shadow_bias_ = bias; }

            inline auto get_shadow_custom_resolution() const -> const int& { return shadow_custom_resolution_; }

            inline auto set_shadow_custom_resolution(const int& resolution) { shadow_custom_resolution_ = resolution; }

            inline auto get_shadow_near_plane() const -> const float& { return shadow_near_plane_; }

            inline auto set_shadow_near_plane(const float& near) { shadow_near_plane_ = near; }

            inline auto get_shadow_normal_bias() const -> const float& { return shadow_normal_bias_; }

            inline auto set_shadow_normal_bias(const float& bias) { shadow_normal_bias_ = bias; }

            inline auto get_shadow_radius() const -> const float& { return shadow_radius_; }

            inline auto set_shadow_radius(const float& radius) { shadow_radius_ = radius; }

            inline auto get_shadow_resolution() const -> const LightShadowResolution& { return shadow_resolution_; }

            inline auto set_shadow_resolution(const LightShadowResolution& resolution) { shadow_resolution_ = resolution; }

            inline auto get_shadows() const -> const LightShadows& { return shadows_; }

            inline auto set_shadows(const LightShadows& shadows) { shadows_ = shadows; }

            inline auto get_shadow_strength() const -> const float& { return shadow_strength_; }

            inline auto set_shadow_strength(const float& strength) { shadow_strength_ = strength; }

            inline auto get_spot_angle() const -> const float& { return spot_angle_; }

            inline auto set_spot_angle(const float& angle) { spot_angle_ = angle; }

            inline auto get_type() const -> const LightType& { return type_; }

            inline auto set_type(const LightType& type) { type_ = type; }


        private:
            glm::vec2 area_size_;

            LightBakingOutput baking_output_;

            float bounce_intensity_;

            std::shared_ptr<Color> color_;

            float color_temperature_;

            std::shared_ptr<Texture> cookie_;

            float cookie_size_;

            int culling_mask_;

            float intensity_;

            std::list<float> layer_shadow_cull_distances_;

            LightmapBakeType lightmap_back_type_;

            LightShadowCasterMode light_shadow_caster_mode_;

            float range_;

            LightRenderMode render_mode_;

            float shadow_angle_;

            float shadow_bias_;

            int shadow_custom_resolution_;

            float shadow_near_plane_;

            float shadow_normal_bias_;

            float shadow_radius_;

            LightShadowResolution shadow_resolution_;

            LightShadows shadows_;

            float shadow_strength_;

            float spot_angle_;

            LightType type_;



        };
    }

}