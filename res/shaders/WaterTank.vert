#version 410

layout(location = 0) in vec2 aPos;

uniform vec2 uResolution;

void main()
{
    gl_Position = vec4((aPos / uResolution) * 2.0 - 1.0, 0.0, 1.0);
}
