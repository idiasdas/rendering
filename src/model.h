#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include <fstream>
#include <vector>

enum class ModelReadAttr {
        VERTEX = 0,
        COLOR,
        TEXTURE,
        NOT_SPECIFIED
};

class OGLModel{
private:
    std::vector<float> m_vertices;
    std::vector<float> m_colors;
    std::vector<float> m_texture_UV;

    unsigned int m_vertex_buffer_ID;
    unsigned int m_color_buffer_ID;
    unsigned int m_texture_buffer_ID;

    glm::mat4 m_model_matrix = glm::mat4(1);
public:
    bool read_model_file(const char* model_path);
    void load_model_on_gpu();
    void draw_model(unsigned int program_ID, glm::mat4 view, glm::mat4 projection);

    void set_model_matrix(glm::mat4 model_matrix);
    glm::mat4 get_model_matrix();
};
