#version 450

layout (set = 0, binding = 1) uniform samplerCube env_cube;

layout(location = 0) in vec3 inUVW;
layout(location = 0) out vec4 outColor;

void main()
{
    vec3 env_color = texture(env_cube, inUVW).rgb;
    outColor = vec4(env_color, 1.0);
}