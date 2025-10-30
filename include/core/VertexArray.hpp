#pragma once

#include <glad/glad.h>
#include <memory>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
    GLuint m_id;

public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const std::unique_ptr<VertexBuffer>& vbo, const VertexBufferLayout& layout);
};