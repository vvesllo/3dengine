cmake_minimum_required(VERSION 4.1)

set(PROJECT_NAME 3dengine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/core/Application.cpp                include/core/Application.hpp
    src/core/VertexArray.cpp                include/core/VertexArray.hpp
    src/core/ElementBuffer.cpp              include/core/ElementBuffer.hpp
    src/core/VertexBuffer.cpp               include/core/VertexBuffer.hpp
    src/core/VertexBufferLayout.cpp         include/core/VertexBufferLayout.hpp
    src/core/Shader.cpp                     include/core/Shader.hpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)