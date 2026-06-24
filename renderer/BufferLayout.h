#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexAttribute
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_BYTE:
            return 1;
        }
        return 0;
    }
};

class BufferLayout
{
    std::vector<VertexAttribute> m_Attributes;
    unsigned int m_Stride = 0;

public:
    template <typename T>
    void Push(unsigned int count);

    const std::vector<VertexAttribute> &GetAttributes() const { return m_Attributes; }
    unsigned int getStride() const { return m_Stride; }
};

template <>
inline void BufferLayout::Push<float>(unsigned int count)
{
    m_Attributes.push_back({GL_FLOAT, count, GL_FALSE});
    m_Stride += count * VertexAttribute::GetSizeOfType(GL_FLOAT);
}

template <>
inline void BufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Attributes.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_Stride += count * VertexAttribute::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
inline void BufferLayout::Push<char>(unsigned int count)
{
    m_Attributes.push_back({GL_BYTE, count, GL_FALSE});
    m_Stride += count * VertexAttribute::GetSizeOfType(GL_BYTE);
}