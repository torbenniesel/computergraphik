#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;

out vec3 v_Color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * position;
    v_Color = color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Color;

uniform vec4 u_Color;

void main() {
    color = vec4(v_Color, 1.0f);
}