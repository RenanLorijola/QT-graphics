#version 400

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;

out vec4 v2fcolor;

uniform float scaling;
uniform vec4 translation;
uniform vec4 color;
uniform int solidColor;


void main ()
{
    if(solidColor==1)
        v2fcolor = color;
    else
        v2fcolor = vColors;
    gl_Position = vPosition * vec4(scaling, scaling, scaling, 1) + translation;
}
