cmake_minimum_required(VERSION 3.16)

project(rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext)
add_executable(rendering src/main.cpp)

target_link_libraries(rendering PRIVATE
                    glew
                    glfw
                    glm::glm
)

target_include_directories(rendering PRIVATE ext/glfw/include)
target_include_directories(rendering PRIVATE ext/glew-2.2.0/include)
target_include_directories(rendering PRIVATE ext/glm)
