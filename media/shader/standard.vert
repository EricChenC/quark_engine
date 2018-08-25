#version 450

// matrices
layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 1) uniform UniformLightDir{
    vec4 light_dir;
} uld;

layout(push_constant) uniform ModelMatrix {
    mat4 model;
} mt;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texcoord;


// Output data ; will be interpolated for each fragment.
layout (location = 0) out vec2 uv;
layout (location = 1) out vec3 normal_world_space;
layout (location = 2) out vec3 light_direction_world_space;
layout (location = 3) out vec3 light_direction_camera_space;


out gl_PerVertex {
    vec4 gl_Position;
};

// vertex shader
void main()
{
        // Output position of the vertex, in clip space : MVP * position
    gl_Position =  ubo.proj * ubo.view * mt.model * vec4(in_position,1);

    // Vector that goes from the vertex to the light, in camera space
    light_direction_world_space = (uld.light_dir).xyz;

    light_direction_camera_space = (ubo.view * mt.model * uld.light_dir).xyz;
    
    // Normal of the the vertex, in camera space
    normal_world_space = (mt.model * vec4(in_normal,0)).xyz; 
    
    // UV of the vertex. No special space for this one.
    uv = in_texcoord;
    
}