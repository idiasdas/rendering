#include "opengl_object.h"

void OpenGLObject::passToOpenGL(){
    // Giving vertices and color to OpenGL
    glGenBuffers(1, &m_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, m_size_vertex_buffer, m_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &m_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, m_size_color_buffer, m_color_buffer_data, GL_STATIC_DRAW);
}

void OpenGLObject::draw(){

    // Draw the object
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorbuffer);
    glVertexAttribPointer(
        1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glUseProgram(m_programID);
    glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &m_MVP[0][0]);

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
