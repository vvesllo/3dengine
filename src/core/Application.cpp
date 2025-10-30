#include "include/core/Application.hpp"

#include <print>

GLuint Application::compileShader(const std::string& source, GLenum type)
{
    GLuint id = glCreateShader(type);

    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
        glGetShaderInfoLog(id, length, &length, message);
    
        std::println(
            "Failed to compile {} shader: {}", 
            type == GL_VERTEX_SHADER ? "vertex" : "fragment",
            message
        );
    
        glDeleteShader(id);

        return 0;
    }

    return id;
}

GLuint Application::createShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    GLuint id = glCreateProgram();
    GLuint vs = compileShader(vertex_shader, GL_VERTEX_SHADER);
    GLuint fs = compileShader(fragment_shader, GL_FRAGMENT_SHADER);

    glAttachShader(id, vs);
    glAttachShader(id, fs);
    
    glLinkProgram(id);
    glValidateProgram(id);

    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLint length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar* message = (GLchar*)alloca(length);
        glGetProgramInfoLog(id, length, &length, message);
    
        std::println("Failed to link shader program: {}", message);
        glDeleteProgram(id);
    
        return 0;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return id;
}


int Application::initGLFW()
{
    if (!glfwInit())
    {
        std::println("Failed to initialize GLFW!");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

int Application::initGLAD()
{

    if (!gladLoadGL())
    {
        std::println("Failed to initialize GLAD!");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    return 0;
}

int Application::createWindow(uint16_t width, uint16_t height, const char* title)
{
    m_window = glfwCreateWindow(
        width, height, 
        title, 
        nullptr, nullptr
    );
    
    if (!m_window)
    {
        std::println("Failed to create GLFW window!");
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); 

    return 0;
}

Application::Application(uint16_t width, uint16_t height, const char* title)
    : m_width{width}, m_height{height}
{
    initGLFW();
    createWindow(width, height, title);
    initGLAD();
    
    glfwSetFramebufferSizeCallback(
        m_window,
        [](GLFWwindow* window, int width, int height) 
        {
            glViewport(0, 0, width, height);
        }
    );


    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    std::vector<GLfloat> vertices = {
		-0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
    };

    std::vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0
    };

    m_vao = std::make_unique<VertexArray>();
    m_vbo = std::make_unique<VertexBuffer>(vertices);
    m_ebo = std::make_unique<ElementBuffer>(indices);

    VertexBufferLayout layout;
    layout.push<GLfloat>(3);
	m_vao->addBuffer(m_vbo, layout);
    

    m_shader = std::make_unique<Shader>(
        "shaders/default.vert",
        "shaders/default.frag"
    );


    m_vao->unbind();
    m_vbo->unbind();
    m_ebo->unbind();
    m_shader->unbind();
    
}

Application::~Application()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::run()
{
    GLuint color_red = 0;
    short k = 1;
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        if (color_red <= 0)
            k = 1;
        else if (color_red >= 100)
            k = -1;

        color_red += k;

        m_shader->bind();
        m_shader->setUniform4f(
            "u_color", (GLfloat)(color_red / 100.f), 0.0f, 1.0f, 1.0f
        );

        m_vao->bind();
        m_ebo->bind();
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}