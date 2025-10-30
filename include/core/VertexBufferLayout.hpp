#pragma once

#include <glad/glad.h>
#include <vector>

struct VertexBufferElement
{
    GLenum type;
    GLuint count;
    GLboolean normalized;
    GLuint size;
};

class VertexBufferLayout
{
private:
    GLuint m_stride;
    std::vector<VertexBufferElement> m_elements;

public:
    VertexBufferLayout();

    GLuint getStride() const;
    std::vector<VertexBufferElement> getElements() const;
    
    template<class T>
    void push(GLuint count);
};