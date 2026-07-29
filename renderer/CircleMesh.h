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
    VertexArray* va;
    VertexBuffer* vb;
    Mesh(std::vector<Particle> particles);
    ~Mesh();
    void draw(Shader &shader);
private:
    void setupMesh()
    {
        vb = new VertexBuffer(particles.data(), sizeof(Particle));
        BufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(1);
        layout.Push<float>(3);
        va = new VertexArray();
        va->AddBuffer(*vb, layout);
    }
};