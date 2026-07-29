#version 330 core
layout (location = 0) in vec3 aCenter;
layout (location = 1) in float aRadius;
layout (location = 2) in vec3 aColor;

out vec3 vColor;

void main() {
    vColor = aColor;
    gl_Position = vec4(aCenter, 1.0); // Pass straight to normalized device coordinates (-1 to 1)
    gl_PointSize = aRadius * 200.0;   // Hardcode a pixel scale multiplier for testing
}

