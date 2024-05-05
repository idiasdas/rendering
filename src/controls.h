#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void compute_matrices_from_inputs();
glm::mat4 get_view_matrix();
glm::mat4 get_projection_matrix();
