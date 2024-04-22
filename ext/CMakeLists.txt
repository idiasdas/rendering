# Build static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Adding GLEW

add_subdirectory(glew-2.2.0/build/cmake)

# Adding GLFW

set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_BUILD_X11 ON)
set(GLFW_BUILD_WAYLAND OFF)

add_subdirectory(glfw)

# Adding GLM

add_subdirectory(glm)
