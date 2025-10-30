#include "include/core/Shader.hpp"

#include <print>
#include <fstream>
#include <string>



std::string Shader::readFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    const std::string content = {
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };
    file.close();

    return content;
}

GLuint Shader::getUniformLocation(const std::string& name)
{
    if (m_uniform_location_cache.find(name) == m_uniform_location_cache.cend())
    {
        GLint location = glGetUniformLocation(m_id, name.c_str());
        
        if (location == -1)
            std::println("Uniform `{}` doesn't exists!", name);
        
        m_uniform_location_cache[name] = location;
    }

    return m_uniform_location_cache[name];
}

Shader::Shader(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{
    m_id = createShader(
        readFile(vertex_shader_path).c_str(), 
        readFile(fragment_shader_path).c_str()
    );
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::bind() const
{
    glUseProgram(m_id);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    glUniform4f(
        getUniformLocation(name), 
        v0, v1, v2, v3
    );
}

GLuint Shader::createShader(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
    GLuint shader_program_id = glCreateProgram();
    
    GLuint vs = compileShader(
        vertex_shader_source.c_str(), 
        GL_VERTEX_SHADER
    );

    GLuint fs = compileShader(
        fragment_shader_source.c_str(), 
        GL_FRAGMENT_SHADER
    );

    glAttachShader(shader_program_id, vs);
    glAttachShader(shader_program_id, fs);
    
    glLinkProgram(shader_program_id);
    glValidateProgram(shader_program_id);

    
    GLint status;
    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &length);
        GLchar* message = (GLchar*)alloca(length);
        glGetProgramInfoLog(shader_program_id, length, &length, message);
    
        std::println("Failed to link shader program: {}", message);
        glDeleteProgram(shader_program_id);
    
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader_program_id;
}

GLuint Shader::compileShader(const char* source, GLenum type)
{
    GLuint shader_id = glCreateShader(type);

    glShaderSource(shader_id, 1, &source, nullptr);
    glCompileShader(shader_id);


    GLint status;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
        glGetShaderInfoLog(shader_id, length, &length, message);
    
        std::println(
            "Failed to compile {} shader: {}", 
            type == GL_VERTEX_SHADER ? "vertex" : "fragment",
            message
        );
    
        glDeleteShader(shader_id);

        return 0;
    }

    return shader_id;
}