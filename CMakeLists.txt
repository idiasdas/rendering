cmake_minimum_required(VERSION 3.17)

project(rendering)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext)

# add_executable(my_renderer src/my_renderer/main.cpp src/my_renderer/opengl_object.cpp)

# target_compile_definitions(my_renderer PRIVATE EXECUTABLE_SOURCE_PATH="../src/my_renderer/")

# target_link_libraries(my_renderer PRIVATE
#     glew
#     glfw
#     glm::glm
# )

# target_include_directories(my_renderer PUBLIC
#     ext/glfw/include
#     ext/glew-2.2.0/include
#     ext/glm
#     src/
# )

# Add each executable to the list executables_list

list(APPEND executables_list src/main.cpp)
list(APPEND executables_list src/tutorial_01/tutorial_01.cpp)
list(APPEND executables_list src/tutorial_02/tutorial_02.cpp)
list(APPEND executables_list src/tutorial_03/tutorial_03.cpp)
list(APPEND executables_list src/tutorial_04/tutorial_04.cpp)
list(APPEND executables_list src/tutorial_05/tutorial_05.cpp)
list(APPEND executables_list src/my_renderer/my_renderer.cpp)

# For each executable in the list, create an executable target and link the necessary libraries

foreach(executable IN LISTS executables_list)

    get_filename_component(executable_name ${executable} NAME_WE)

    file(GLOB COMMON_EXECUTABLE_SOURCES src/common/*.cpp)

    add_executable(${executable_name} ${executable} ${COMMON_EXECUTABLE_SOURCES})

    target_link_libraries(${executable_name} PRIVATE
        glew
        glfw
        glm::glm
    )

    file(RELATIVE_PATH relative ${CMAKE_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src/${executable_name}")
    message(" *** The relative path is ${relative}")
    target_compile_definitions(${executable_name} PRIVATE EXECUTABLE_SOURCE_PATH="${relative}/")


    target_include_directories(${executable_name} PUBLIC
                                ext/glfw/include
                                ext/glew-2.2.0/include
                                ext/glm
                                src/
    )

endforeach()
