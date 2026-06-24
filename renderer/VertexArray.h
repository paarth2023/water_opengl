#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"

class VertexArray
{
    unsigned int render_id;

public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer &vb, const BufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};