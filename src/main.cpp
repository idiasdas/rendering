#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"
#include "shader.h"
#include "texture.h"
#include "controls.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

GLFWwindow* window;

static int initialize(){
    // Initializing GLFW
    glewExperimental = true;
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create OpenGL window and context
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "Rendering", NULL, NULL);

    if(window == nullptr){
        std::cout << "Failed to open GLFW window" << std::endl;
        std::cout << "If you have an Intel GPU, they are not 4.6 compatible." << std::endl;
        std::cout << "Try the 2.1 version of the tutorials." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if(glewInit() != GLEW_OK){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Hide the mouse and enable unlimited movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS);

    unsigned int vertex_array_ID;
    glGenVertexArrays(1, &vertex_array_ID);
    glBindVertexArray(vertex_array_ID);

    return vertex_array_ID;
}

int main(int argc, char* argv[]){

    unsigned int vertex_array_ID = initialize();
    if(vertex_array_ID == -1) exit(1);

    OGLModel triangle, cube;

    if(!triangle.read_model_file("../utils/models/triangle.model")) exit(1);
    triangle.load_model_on_gpu();

    if(!cube.read_model_file("../utils/models/cube.model")) exit(1);
    cube.load_model_on_gpu();

    unsigned int texture_shaders = LoadShaders("../utils/shaders/texture.vertexshader", "../utils/shaders/texture.fragmentshader");
    unsigned int projection_shaders = LoadShaders("../utils/shaders/projection.vertexshader", "../utils/shaders/simple.fragmentshader");

    // unsigned int texture = loadDDS("../utils/textures/uvtemplate.DDS");
    unsigned int texture = loadBMP_custom("../utils/textures/fire.bmp");

	unsigned int texture_ID  = glGetUniformLocation(texture_shaders, "my_texture_sampler");
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texture_ID, 0);

    cube.set_model_matrix(glm::translate(cube.get_model_matrix(), glm::vec3(2.0f, 0.0f, 0.0f)));

    glm::mat4 projection_matrix ;
    glm::mat4 view_matrix;


    do{

        computeMatricesFromInputs();
		projection_matrix = getProjectionMatrix();
		view_matrix = getViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle.draw_model(projection_shaders, view_matrix, projection_matrix);
        cube.draw_model(texture_shaders, view_matrix, projection_matrix);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glDeleteVertexArrays(1, &vertex_array_ID);
    return 0;
}
