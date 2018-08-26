#version 450


layout (location = 0) in vec2 uv;
layout (location = 1) in vec3 normal_world_space;
layout (location = 2) in vec3 light_direction_world_space;
layout (location = 3) in vec3 light_direction_camera_space;

layout(location = 0) out vec4 out_frag_cColor;


// main routine
void main()
{

    // Light emission properties
    vec3 light_color = vec3(1,1,1);
    float light_power = 1.0f;
    
    // Material properties
    vec3 material_diffuse_color = vec3(1.0, 1.0, 1.0);
    vec3 material_ambient_color = vec3(0.2, 0.2, 0.2) * material_diffuse_color;
    vec3 material_specular_color = vec3(0.2, 0.2, 0.2);

    // Distance to the light
    //float distance = length( LightPosition_worldspace - Position_worldspace );

    // Normal of the computed fragment, in camera space
    vec3 n = normalize( normal_world_space );

    // Direction of the light (from the fragment to the light)
    vec3 l = normalize( light_direction_world_space );
    // Cosine of the angle between the normal and the light direction, 
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendiular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cos_theta = clamp( dot( n,l ), 0,1 );
    
    // Eye vector (towards the camera)
    vec3 e = normalize(light_direction_camera_space);

    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cos_alpha = clamp( dot( -l, -e ), 0, 1 );
        
    float am = dot(vec3(0.4, 0.0, 0.0), normal_world_space);
    
    material_ambient_color *= am; // for fixed cube edge can't see problem


    vec3 color = 
        // Ambient : simulates indirect lighting
        material_ambient_color +
        // Diffuse : "color" of the object
        material_diffuse_color * light_color * light_power * cos_theta +
        // Specular : reflective highlight, like a mirror
        material_specular_color * light_color * light_power * pow(cos_alpha, 5);
    
    
    out_frag_cColor = vec4(color, 1.0f);
    
 }