#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "common/shader.h"

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

int main(int argc, char* argv[]){

    if(initialize() != 0){
        return -1;
    }



    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Pretty triangle --------------------------------------------------------

    // static const GLfloat g_vertex_buffer_data[] = {
    //     -1.0f, -1.0f, 0.0f,
    //     1.0f, -1.0f, 0.0f,
    //     0.0f,  1.0f, 0.0f,
    // };

    // Pretty Cube ------------------------------------------------------------
    static const GLfloat g_vertex_buffer_data[] = {
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
    static const GLfloat g_color_buffer_data[] = {
        // 0.583f,  0.771f,  0.014f,
        // 0.609f,  0.115f,  0.436f,
        // 0.327f,  0.483f,  0.844f,
        // 0.822f,  0.569f,  0.201f,
        // 0.435f,  0.602f,  0.223f,
        // 0.310f,  0.747f,  0.185f,
        // 0.597f,  0.770f,  0.761f,
        // 0.559f,  0.436f,  0.730f,
        // 0.359f,  0.583f,  0.152f,
        // 0.483f,  0.596f,  0.789f,
        // 0.559f,  0.861f,  0.639f,
        // 0.195f,  0.548f,  0.859f,
        // 0.014f,  0.184f,  0.576f,
        // 0.771f,  0.328f,  0.970f,
        // 0.406f,  0.615f,  0.116f,
        // 0.676f,  0.977f,  0.133f,
        // 0.971f,  0.572f,  0.833f,
        // 0.140f,  0.616f,  0.489f,
        // 0.997f,  0.513f,  0.064f,
        // 0.945f,  0.719f,  0.592f,
        // 0.543f,  0.021f,  0.978f,
        // 0.279f,  0.317f,  0.505f,
        // 0.167f,  0.620f,  0.077f,
        // 0.347f,  0.857f,  0.137f,
        // 0.055f,  0.953f,  0.042f,
        // 0.714f,  0.505f,  0.345f,
        // 0.783f,  0.290f,  0.734f,
        // 0.722f,  0.645f,  0.174f,
        // 0.302f,  0.455f,  0.848f,
        // 0.225f,  0.587f,  0.040f,
        // 0.517f,  0.713f,  0.338f,
        // 0.053f,  0.959f,  0.120f,
        // 0.393f,  0.621f,  0.362f,
        // 0.673f,  0.211f,  0.457f,
        // 0.820f,  0.883f,  0.371f,
        // 0.982f,  0.099f,  0.879f
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

    // Giving the triangle vertices to OpenGL
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);// Now vertexbuffer contains the buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    // ------------------------------------------------------------------------

	GLuint programID = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );

    // Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(4,3,3),
        glm::vec3(0,0,0),
        glm::vec3(0,0,1)
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 MVP = Projection * View * Model;

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Use our shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 36); // Starting from vertex 0; 3 vertices total -> 1 triangle

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    // Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

    return 0;
}
