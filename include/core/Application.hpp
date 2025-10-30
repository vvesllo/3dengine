#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <memory>

#include "include/core/VertexArray.hpp"
#include "include/core/VertexBuffer.hpp"
#include "include/core/ElementBuffer.hpp"
#include "include/core/Shader.hpp"


class Application
{
private:
    uint16_t m_width, m_height;
    GLFWwindow* m_window;
    
    std::unique_ptr<VertexArray> m_vao;
    std::unique_ptr<VertexBuffer> m_vbo;
    std::unique_ptr<ElementBuffer> m_ebo;
    std::unique_ptr<Shader> m_shader;

    GLuint createShader(const std::string& vertex_shader, const std::string& fragment_shader);
    GLuint compileShader(const std::string& source, GLenum type);

    int initGLFW();
    int initGLAD();
    int createWindow(uint16_t width, uint16_t height, const char* title);

public:
    Application(uint16_t width, uint16_t height, const char* title);
    ~Application();

    void run();
};