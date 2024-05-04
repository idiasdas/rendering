#pragma  once
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#ifndef EXECUTABLE_SOURCE_PATH
#define EXECUTABLE_SOURCE_PATH ""
#endif

GLuint LoadShaders(std::string vertex_file_path, std::string fragment_file_path);
