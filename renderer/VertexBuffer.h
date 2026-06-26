#pragma once

#include <glad/glad.h>

class VertexBuffer
{
    unsigned int renderer_id;

public:
    VertexBuffer();
    ~VertexBuffer();

    void Init(const void *data, unsigned int size);
    void Bind() const;
    void Unbind() const;
};