#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader
{
private:
    GLuint m_id;

    std::unordered_map<std::string, GLint> m_uniform_location_cache;

    std::string readFile(const std::string& filepath); 

    GLuint getUniformLocation(const std::string& name);

    GLuint compileShader(const char* source, GLenum type);
    GLuint createShader(const std::string& vertex_shader, const std::string& fragment_shader);

public:
    Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    ~Shader();

    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
};