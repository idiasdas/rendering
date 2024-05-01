#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "common/shader.h"

#include "common/opengl_object.h"

#include <iostream>


GLFWwindow* window;

int initialize(){
    // Initializing GLFW
    glewExperimental = true;
    if(!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);                                // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // No old OpenGL

    window = glfwCreateWindow(1920, 1080, "Tutorial 04", NULL, NULL);

    if(window == nullptr){
        std::cout << "Failed to open GLFW window" << std::endl;
        std::cout << "If you have an Intel GPU, they are not 3.3 compatible." << std::endl;
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

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    return 0;
}
// Pretty triangle --------------------------------------------------------

static const GLfloat triangle_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
};

static const GLfloat triangle_color_buffer_data[] = {
    0.982f,   0.1234f, 0.654f,
    0.931f,   0.1234f, 0.672f,
    0.0764f,  0.2456f, 0.1234f,
};

// Pretty Cube ------------------------------------------------------------
static const GLfloat cube_vertex_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat cube_color_buffer_data[] = {
    -1.0f, -1.0f, -1.0f,   // G,
    -1.0f, -1.0f,  1.0f,   // C,
    -1.0f,  1.0f,  1.0f,   // A,
    // ------------------------
     1.0f,  1.0f, -1.0f,   // F,
    -1.0f, -1.0f, -1.0f,   // G,
    -1.0f,  1.0f, -1.0f,   // E,
    // ------------------------
     1.0f, -1.0f,  1.0f,   // D,
    -1.0f, -1.0f, -1.0f,   // G,
     1.0f, -1.0f, -1.0f,   // H,
    // ------------------------
     1.0f,  1.0f, -1.0f,   // F,
     1.0f, -1.0f, -1.0f,   // H,
    -1.0f, -1.0f, -1.0f,   // G,
    // ------------------------
    -1.0f, -1.0f, -1.0f,   // G,
    -1.0f,  1.0f,  1.0f,   // A,
    -1.0f,  1.0f, -1.0f,   // E,
    // ------------------------
     1.0f, -1.0f,  1.0f,   // D,
    -1.0f, -1.0f,  1.0f,   // C,
    -1.0f, -1.0f, -1.0f,   // G,
    // ------------------------
     0.0f,  0.0f,  1.0f,   // A,
     0.0f,  0.0f,  1.0f,   // C,
     0.0f,  0.0f,  1.0f,   // D,
    // ------------------------
     1.0f,  1.0f,  1.0f,   // B,
     1.0f,  0.0f,  0.0f,   // H,
     1.0f,  0.0f,  0.0f,   // F,
    // ------------------------
     1.0f,  0.0f,  0.0f,   // H,
     1.0f,  1.0f,  1.0f,   // B,
     1.0f,  0.0f,  0.0f,   // D,
    // ------------------------
     1.0f,  1.0f,  1.0f,   // B,
     0.0f,  1.0f,  0.0f,   // F,
     0.0f,  1.0f,  0.0f,   // E,
    // ------------------------
     1.0f,  1.0f,  1.0f,   // B,
     0.0f,  1.0f,  0.0f,   // E,
     0.0f,  1.0f,  0.0f,   // A,
    // ------------------------
     1.0f,  1.0f,  1.0f,   // B,
     0.0f,  0.0f,  1.0f,   // A,
     0.0f,  0.0f,  1.0f    // D
};

// ------------------------------------------------------------------------
int main(int argc, char* argv[]){

    // Initialize and verify that everything is working
    if(initialize() != 0){
        return -1;
    }

    // Create Vertix Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

    // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,10), // camera position
        glm::vec3(0,0,0), // camera looks at the origin
        glm::vec3(0,1,0)  // up vector
    );
    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 ScaledModel = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));
    glm::mat4 cube_MVP = Projection * View * ScaledModel;

    OpenGLObject cube;
    cube.m_vertex_count = 36;
    cube.m_vertex_buffer_data = (GLfloat*)cube_vertex_buffer_data;
    cube.m_color_buffer_data = (GLfloat*)cube_color_buffer_data;
    cube.m_size_vertex_buffer = sizeof(cube_vertex_buffer_data);
    cube.m_size_color_buffer = sizeof(cube_color_buffer_data);
    cube.passToOpenGL();
    cube.m_programID = programID;
    cube.m_MatrixID = MatrixID;
    cube.m_MVP = cube_MVP;

    OpenGLObject triangle;
    triangle.m_vertex_count = 3;
    triangle.m_vertex_buffer_data = (GLfloat*)triangle_vertex_buffer_data;
    triangle.m_color_buffer_data = (GLfloat*)triangle_color_buffer_data;
    triangle.m_size_vertex_buffer = sizeof(triangle_vertex_buffer_data);
    triangle.m_size_color_buffer = sizeof(triangle_color_buffer_data);
    triangle.passToOpenGL();
    triangle.m_programID = programID;
    triangle.m_MatrixID = MatrixID;
    triangle.m_MVP = Projection * View * glm::translate(ScaledModel, glm::vec3(3.0f, 0.0f, 0.0f));

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        // -------------------------------------------------------
        cube.draw();
        triangle.draw();
        // -------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    // Cleanup VBO and shader
    glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
	glfwTerminate();

    return 0;
}
