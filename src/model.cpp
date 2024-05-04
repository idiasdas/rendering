#include "model.h"

void OGLModel::load_model_on_gpu(){
    glGenBuffers(1, &m_vertex_buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), &m_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_color_buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size() * sizeof(float), &m_colors[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_texture_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_texture_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, m_texture_UV.size()*sizeof(float), &m_texture_UV[0], GL_STATIC_DRAW);

}

void OGLModel::draw_model(unsigned int program_ID, glm::mat4 view, glm::mat4 projection){

    glm::mat4 MVP = projection * view * m_model_matrix;
    unsigned int matrix_ID = glGetUniformLocation(program_ID, "MVP");
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_ID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, m_color_buffer_ID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, m_texture_buffer_ID);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glUseProgram(program_ID);
    glUniformMatrix4fv(matrix_ID, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size()/3);
}

bool OGLModel::read_model_file(const char* model_file_name){
    std::cout << "Reading model file: " << model_file_name << "\n";
    std::ifstream model_file;
    model_file.open(model_file_name);
    ModelReadAttr cur_attr = ModelReadAttr::NOT_SPECIFIED;
    std::string line;

    float cur_values[3];
    int count_values = 0;

    if (model_file.is_open()){
        while ( std::getline (model_file,line) ){
            if( line.empty()) continue;

            if(line.find("#vertices") == 0) {
                cur_attr = ModelReadAttr::VERTEX;
                continue;
            }
            else if(line.find("#colors") == 0){
                cur_attr = ModelReadAttr::COLOR;
                continue;
            }
            else if(line.find("#texture") == 0){
                cur_attr = ModelReadAttr::TEXTURE;
                continue;
            }

            if(cur_attr == ModelReadAttr::NOT_SPECIFIED){
                std::cout << "Failed to read model file \n";
                return false;
            }

            count_values = sscanf(line.c_str(), "%f %f %f", &cur_values[0], &cur_values[1], &cur_values[2]);

            if(cur_attr == ModelReadAttr::VERTEX){
                if(count_values != 3){
                    std::cout << "\t - Wrong vertex format (" << count_values << ")\n";
                    return false;
                }
                m_vertices.push_back(cur_values[0]);
                m_vertices.push_back(cur_values[1]);
                m_vertices.push_back(cur_values[2]);
            }
            else if(cur_attr == ModelReadAttr::COLOR){
                if(count_values != 3){
                    std::cout << "\t - Wrong color format (" << count_values << ")\n";
                    return false;
                }
                m_colors.push_back(cur_values[0]);
                m_colors.push_back(cur_values[1]);
                m_colors.push_back(cur_values[2]);
            }
            else if(cur_attr == ModelReadAttr::TEXTURE){
                if(count_values != 2){
                    std::cout << "\t - Wrong texture format (" << count_values << ")\n";
                    return false;
                }
                m_texture_UV.push_back(cur_values[0]);
                m_texture_UV.push_back(cur_values[1]);
            }
        }
        model_file.close();
    }
    else{
        std::cout << "Unable to open file: " << model_file_name <<"\n";
        return false;
    }

    model_file.close();

    return true;
}


void OGLModel::set_model_matrix(glm::mat4 model_matrix){
    m_model_matrix = model_matrix;
}

glm::mat4 OGLModel::get_model_matrix(){
    return m_model_matrix;
}
