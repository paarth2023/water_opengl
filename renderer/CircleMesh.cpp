#include "CircleMesh.h"

Mesh::Mesh(std::vector<Particle> particles) 
{
    this->particles = particles;
    setupMesh();
}
