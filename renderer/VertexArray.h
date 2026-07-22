#pragma once
#include "VertexBuffer.h"
#include "BufferLayout.h"
/* 
This is a header file for the class that tells the gpu about the memory layout it has been sent.
particularly the AddBuffer function, does this.
basically binding the vertex array and later unbinding it at deconstruction.
*/
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