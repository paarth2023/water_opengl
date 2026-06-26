#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

VertexBuffer::~VertexBuffer() {}

void VertexBuffer::Init(const void *data, unsigned int size)
{
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}