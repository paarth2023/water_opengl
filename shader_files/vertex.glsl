#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 translation;

uniform mat4 projection;
uniform mat4 model;
out vec3 fin_color;

mat4 translationMatrix = mat4(
    vec4(1.0, 0.0, 0.0, 0.0),
    vec4(0.0, 1.0, 0.0, 0.0),
    vec4(0.0, 0.0, 1.0, 0.0),
    vec4(translation, 0.0)
);

void main() {
    gl_Position = translationMatrix * projection * model * vec4(aPos, 1.0);
    fin_color = aColor;
}