#include "include/core/VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::addBuffer(const std::unique_ptr<VertexBuffer>& vbo, const VertexBufferLayout& layout)
{
    this->bind();
    vbo->bind();

    GLuint offset = 0; 
    GLuint i = 0; 

    for (const auto& element : layout.getElements())
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * element.size;
        ++i;
    }
}

void VertexArray::bind() const
{
	glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
