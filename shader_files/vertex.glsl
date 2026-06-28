#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 projection;
uniform mat4 model;
out vec3 fin_color;

void main() {
    gl_Position = projection * model * vec4(aPos, 1.0);
    fin_color = aColor;
}