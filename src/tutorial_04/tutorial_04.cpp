#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "common/shader.h"

GLFWwindow* window;
void draw(GLuint vertexbuffer, GLuint colorbuffer, GLuint programID, GLuint MatrixID, glm::mat4 MVP, GLuint triangle_vertexbuffer, GLuint triangle_colorbuffer, glm::mat4 triangle_MVP){
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

        // Draw!
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // triangle -----------------------------------------------------------
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, triangle_vertexbuffer);
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
        glBindBuffer(GL_ARRAY_BUFFER, triangle_colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &triangle_MVP[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ---------------------------------------------------------------------
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
}

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


    // Pretty triangle --------------------------------------------------------

    static const GLfloat triangle_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    static const GLfloat triangle_color_buffer_data[] = {
        0.982f, 0.1234f, 0.654f,
        0.931f, 0.1234f, 0.672f,
        0.0764f,  0.2456f, 0.1234f,
    };

    // ------------------------------------------------------------------------

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


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

    // Giving the cube vertices to OpenGL
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);// Now vertexbuffer contains the buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    std::cout << "sizeof(g_vertex_buffer_data): " << sizeof(g_vertex_buffer_data) << std::endl;
    std::cout << "sizeof(g_color_buffer_data): " << sizeof(g_color_buffer_data) << std::endl;

    std::cout << "sizeof(GLfloat): " << sizeof(GLfloat) << std::endl;


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
        glm::vec3(4,3,3), // camera position
        glm::vec3(0,0,0), // camera looks at the origin
        glm::vec3(0,1,0)  // up vector
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 ScaledModel = glm::scale(Model, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 MVP = Projection * View * ScaledModel;




    // ------------------------------------------------------------------------
    // Doing the triangle at the side

    // Giving the triangle vertices to OpenGL
    GLuint triangle_vertexbuffer;
    glGenBuffers(1, &triangle_vertexbuffer);// Now vertexbuffer contains the buffer ID
    glBindBuffer(GL_ARRAY_BUFFER, triangle_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex_buffer_data), triangle_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint triangle_colorbuffer;
    glGenBuffers(1, &triangle_colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_color_buffer_data), triangle_color_buffer_data, GL_STATIC_DRAW);


    // Get a handle for our "MVP" uniform
	// GLuint MatrixID_triangle = glGetUniformLocation(programID, "MVP");

    glm::mat4 triangle_Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 triangle_View = glm::lookAt(
        glm::vec3(4,3,3), // camera position
        glm::vec3(0,0,0), // camera looks at the origin
        glm::vec3(0,1,0)  // up vector
    );

    glm::mat4 triangle_Model = glm::mat4(1.0f);
    triangle_Model = glm::translate(triangle_Model, glm::vec3(1.5f, 0.0f, 0.0f));
    triangle_Model = glm::rotate(triangle_Model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // glm::mat4 triangle_ScaledModel = glm::scale(triangle_Model, glm::vec3(0.5f, 0.5f, 0.5f));

    glm::mat4 triangle_MVP = triangle_Projection * triangle_View * triangle_Model;
    //-------------------------------------------------------------------------

    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        draw(vertexbuffer, colorbuffer, programID, MatrixID, MVP, triangle_vertexbuffer, triangle_colorbuffer, triangle_MVP);

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
