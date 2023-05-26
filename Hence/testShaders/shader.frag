#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform sampler2D texSampler;

layout(binding = 1) uniform ShaderToy
{
    vec4 iResolution;
    vec4 iMouse;
    float iTime;
} shadertoy;

layout(location = 0) in vec2 inUV;

layout(location = 0) out vec4 outColor;

void main()
{
    //outColor = texture(texSampler, inUV);
    float x = shadertoy.iResolution.x / 3840.0;
    float y = shadertoy.iResolution.y / 2040.0;
    outColor = vec4(x, y, shadertoy.iTime, 1.0);
}