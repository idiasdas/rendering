#pragma once

#include "GL/glew.h"

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

class OpenGLObject{
public:
    GLsizei m_vertex_count;
    GLsizei m_size_vertex_buffer;
    GLsizei m_size_color_buffer;

    GLuint m_vertexbuffer;
    GLuint m_colorbuffer;
    GLfloat* m_vertex_buffer_data;
    GLfloat* m_color_buffer_data;

    glm::mat4 m_MVP;
    GLuint m_programID;
    GLuint m_MatrixID;

    void passToOpenGL();
    void draw();
};
