cmake_minimum_required(VERSION 3.17)

project(rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME rendering_exec)

add_subdirectory(ext)

file(GLOB EXECUTABLE_SOURCES src/*.cpp)

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    glew
    glfw
    glm::glm
)

file(RELATIVE_PATH relative ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src/")

message(" *** The relative path between build and source is:\n\t - ${relative}")

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE EXECUTABLE_SOURCE_PATH="${relative}/")


target_include_directories(${EXECUTABLE_NAME} PUBLIC
                            ext/glfw/include
                            ext/glew-2.2.0/include
                            ext/glm
                            src/
)
