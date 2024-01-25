#version 410

layout(location = 0) out mediump vec4 fragColor;

uniform mediump vec4 uColor;

void main()
{
    fragColor = uColor;
}
