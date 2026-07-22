#include "VertexArray.h"

/*
This file implements all the functions in the included header file.
*/

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &render_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &render_id);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const BufferLayout &layout)
{
    Bind();
    vb.Bind();

    unsigned int offset = 0;

    const auto &attributes = layout.GetAttributes();

    for (unsigned int i = 0; i < attributes.size(); i++) // this for loop is what tells the gpu about the layout of the memory allocated on the gpu
    {
        const auto &attr = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attr.count, attr.type, attr.normalized, layout.getStride(), (const void *)(uintptr_t)offset);
        offset += attr.count * VertexAttribute::GetSizeOfType(attr.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(render_id);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}