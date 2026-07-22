#pragma once
#include "Shader.h"
#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "BufferLayout.h"

struct Particle {
    glm::vec3 center;
    float radius;
    glm::vec3 color;
};

class Mesh {
public:
    std::vector<Particle> particles;
    Mesh(std::vector<Particle> particles);
    void draw(Shader &shader);
private:
    void setupMesh()
    {
        VertexBuffer vb(particles.data(), sizeof(Particle));
        BufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(1);
        layout.Push<float>(3);
        VertexArray va;
        va.AddBuffer(vb, layout);
    }
};