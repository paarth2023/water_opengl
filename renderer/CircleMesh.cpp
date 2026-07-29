#include "CircleMesh.h"

/* TODO:
    1. Write Mesh::draw function
    2. Write the destructor for Mesh class
*/

Mesh::Mesh(std::vector<Particle> particles) 
{
    this->particles = particles;
    setupMesh();
}

void Mesh::draw(Shader &shader)
{
    return;
}

Mesh::~Mesh()
{
    // do something here.
}