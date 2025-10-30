#pragma once

#include <glad/glad.h>

#include <vector>

class ElementBuffer
{
private:
    GLuint m_id;
    GLuint m_count;

public:
    ElementBuffer(const std::vector<GLuint>& data);
    ~ElementBuffer();

    void bind();
    void unbind();

    inline GLuint getCount() const;
};