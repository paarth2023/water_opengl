#version 330 core
out vec4 FragColor;
in vec3 fin_color;

void main() {
    FragColor = vec4(fin_color, 1.0);
}