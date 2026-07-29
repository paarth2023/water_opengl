#version 330 core
out vec4 FragColor;
in vec3 vColor;

void main() {
    // Distance from the center of the point sprite (0.5, 0.5)
    float dist = length(gl_PointCoord - vec2(0.5));
    
    // Antialiasing transition boundary
    float alpha = 1.0 - smoothstep(0.48, 0.5, dist);
    
    // Discard outer square edges completely
    if (alpha < 0.01) {
        discard;
    }
    
    FragColor = vec4(vColor, alpha);
}
