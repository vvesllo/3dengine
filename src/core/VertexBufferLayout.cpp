#include "include/core/VertexBufferLayout.hpp"


VertexBufferLayout::VertexBufferLayout()
    : m_stride(0)
{

}

GLuint VertexBufferLayout::getStride() const
{
    return m_stride;
}

std::vector<VertexBufferElement> VertexBufferLayout::getElements() const
{
    return m_elements;
}

template<class T> void VertexBufferLayout::push(GLuint count)
{
    static_assert(false);
}

template<> void VertexBufferLayout::push<GLfloat>(GLuint count)
{
    m_elements.emplace_back(
        VertexBufferElement{
            .type = GL_FLOAT,
            .count = count,
            .normalized = GL_FALSE,
            .size = sizeof(GLfloat)
        }
    );
    
    m_stride += count * m_elements.back().size;
}

template<> void VertexBufferLayout::push<GLuint>(GLuint count)
{
    m_elements.emplace_back(
        VertexBufferElement{
            .type = GL_UNSIGNED_INT,
            .count = count,
            .normalized = GL_FALSE,
            .size = sizeof(GLuint)
        }
    );
    
    m_stride += count * m_elements.back().size;
}

template<> void VertexBufferLayout::push<GLubyte>(GLuint count)
{
    m_elements.emplace_back(
        VertexBufferElement{
            .type = GL_UNSIGNED_BYTE,
            .count = count,
            .normalized = GL_TRUE,
            .size = sizeof(GLubyte)
        }
    );
    
    m_stride += count * m_elements.back().size;
}
