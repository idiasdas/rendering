#include "controls.h"

// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


glm::mat4 view_matrix;
glm::mat4 projection_matrix;

glm::mat4 get_view_matrix(){
	return view_matrix;
}
glm::mat4 get_projection_matrix(){
	return projection_matrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );
// Initial horizontal angle : toward -Z
float horizontal_angle = 3.14f;
// Initial vertical angle : none
float vertical_angle = 0.0f;
// Initial Field of View
float initial_FoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouse_speed = 0.005f;



void compute_matrices_from_inputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double last_time = glfwGetTime();

	// Compute time difference between current and last frame
	double current_time = glfwGetTime();
	float delta_time = float(current_time - last_time);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontal_angle += mouse_speed * float(1024/2 - xpos );
	vertical_angle   += mouse_speed * float( 768/2 - ypos );

	if(vertical_angle > 3.14f/2.0f) vertical_angle = 3.14f/2.0f; // pi/2
	if(vertical_angle < - 3.14f/2.0f) vertical_angle = - 3.14f/2.0f; // pi/2

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(vertical_angle) * sin(horizontal_angle),
		sin(vertical_angle),
		cos(vertical_angle) * cos(horizontal_angle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontal_angle - 3.14f/2.0f),
		0,
		cos(horizontal_angle - 3.14f/2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		position += direction * delta_time * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		position -= direction * delta_time * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		position += right * delta_time * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * delta_time * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS){
		position += up * delta_time * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_LEFT_CONTROL ) == GLFW_PRESS){
		position -= up * delta_time * speed;
	}

	float FoV = initial_FoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	view_matrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );

	// For the next frame, the "last time" will be "now"
	last_time = current_time;
}
