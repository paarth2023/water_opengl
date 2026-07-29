#version 330 core
layout (location = 0) in vec3 aCenter;
layout (location = 1) in float aRadius;
layout (location = 2) in vec3 aColor;

out vec3 vColor;

uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    vColor = aColor;
    
    // Transform center into clip space
    gl_Position = u_projection * u_view * vec4(aCenter, 1.0);
    
    // Project the radius from world space units to screen pixels
    // This keeps the circle size accurate as it moves away from the camera
    float d = length(gl_Position.xyz);
    gl_PointSize = (aRadius * 2.0 * u_projection[1][1]) / d;
}
