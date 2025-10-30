#pragma once

#include <glad/glad.h>

#include <vector>

class VertexBuffer
{
private:
    GLuint m_id;

public:
    VertexBuffer(const std::vector<GLfloat>& data);
    ~VertexBuffer();

    void bind();
    void unbind();
};