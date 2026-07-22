#pragma once

#include <glad/glad.h>

/*
This function is to create the send data to the vertex array. It holds skeleton.
*/

class VertexBuffer
{
    unsigned int renderer_id;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};