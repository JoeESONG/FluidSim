#version 410

layout(location = 0) in vec2 aPos;

uniform vec2 uResolution;

uniform vec2 uPos;
uniform float uOuterRadius;
uniform float uBorder;
uniform float uAntialias;

void main()
{
    vec2 scale = vec2((uOuterRadius + uBorder + uAntialias) * 2.0) / uResolution;
    vec2 offset = (uPos / uResolution) * 2.0 - 1.0;

    gl_Position = vec4(aPos * scale + offset, 0.0, 1.0);
}
