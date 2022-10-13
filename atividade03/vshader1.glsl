#version 400

layout ( location = 0) in vec4 vPosition;
layout ( location = 1) in vec4 vColors;

out vec4 v2fcolor;

void main ()
{
    gl_Position = vPosition ;

    //gl_Position = vPosition*2;
    //gl_Position.w = 1;

    //gl_Position.x = vPosition.x*1.8;

    //gl_Position.y = gl_Position.y*1.8;

    //gl_Position.xy = gl_Position.yx;

    v2fcolor = vColors;
    //v2fcolor.grba = vColors.rgba;
}
